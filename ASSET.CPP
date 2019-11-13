// Asset.cpp: implementation of the CAsset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MathcoDep.h"
#include "Asset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

short g_ClassLife[] = {3,5,7,10,15,20};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CAsset, CObject, VERSIONABLE_SCHEMA | 2)

CAsset::CAsset()
{
	m_strName = CString(TEXT(""));
	m_strDesc = CString(TEXT(""));
	m_tmPurch = CTime::GetCurrentTime();
	m_tmDisp = NULL;

	//GAAP Variables
	m_iGMethod = 0;
	m_iGLife = 0;
	m_fGBasis = 0;
	m_fGResidual = 0;
	m_fGReduction = 0;

	//Tax Variables
	m_iTMethod = 0;
	m_iTLife = 0;
	m_fTBasis = 0;
	m_fTResidual = 0;
	m_fTReduction = 0;
}

CAsset::CAsset(CAsset &strCopy)
{
	m_strName = strCopy.m_strName;
	m_strDesc = strCopy.m_strDesc;
	m_tmPurch = strCopy.m_tmPurch;
	m_tmDisp = strCopy.m_tmDisp;

	//GAAP Variables
	m_iGMethod = strCopy.m_iGMethod;
	m_iGLife = strCopy.m_iGLife;
	m_fGBasis = strCopy.m_fGBasis;
	m_fGResidual = strCopy.m_fGResidual;
	m_fGReduction = strCopy.m_fGReduction;

	//Tax Variables
	m_iTMethod = strCopy.m_iTMethod;
	m_iTLife = strCopy.m_iTLife;
	m_fTBasis = strCopy.m_fTBasis;
	m_fTResidual = strCopy.m_fTResidual;
	m_fTReduction = strCopy.m_fTReduction;
}

CAsset::~CAsset()
{
	if(m_pGADArray)
		free(m_pGADArray);
	if(m_pGExpArray)
		free(m_pGExpArray);
	if(m_pTADArray)
		free(m_pTADArray);
	if(m_pTExpArray)
		free(m_pTExpArray);

}

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepDoc serialization

void CAsset::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strName;
		ar << m_strDesc;
		ar << m_tmPurch;
		ar << m_tmDisp;

		//GAAP Variables
		ar << m_iGMethod;
		ar << m_iGLife;
		ar << m_fGBasis;
		ar << m_fGResidual;
		ar << m_fGReduction;

		//Tax Variables
		ar << m_iTMethod;
		ar << m_iTLife;
		ar << m_fTBasis;
		ar << m_fTResidual;
		ar << m_fTReduction;
	}
	else
	{
		ar >> m_strName;
		ar >> m_strDesc;
		ar >> m_tmPurch;
		ar >> m_tmDisp;

		//GAAP Variables
		ar >> m_iGMethod;
		ar >> m_iGLife;
		ar >> m_fGBasis;
		ar >> m_fGResidual;
		ar >> m_fGReduction;

		//Tax Variables
		ar >> m_iTMethod;
		ar >> m_iTLife;
		ar >> m_fTBasis;
		ar >> m_fTResidual;
		ar >> m_fTReduction;
	}
}

BOOL CAsset::OnNewDocument()
{

	m_strName = CString(TEXT(""));
	m_strDesc = CString(TEXT(""));
	m_tmPurch = CTime::GetCurrentTime();
	m_tmDisp = NULL;

	//GAAP Variables
	m_iGMethod = 0;
	m_iGLife = 0;
	m_fGBasis = 0;
	m_fGResidual = 0;
	m_fGReduction = 0;

	//Tax Variables
	m_iTMethod = 0;
	m_iTLife = 0;
	m_fTBasis = 0;
	m_fTResidual = 0;
	m_fTReduction = 0;

	return TRUE;
}

/*==============================
Straight Line Formula
---------------------
Stores the expense in 
expArray[]
==============================*/

void CAsset::SLine (double *expArray, double *adArray, BOOL IsGAAP)
{
	short iYear = 0;
	double fAD = 0;

	if(IsGAAP)
	{
		while (iYear < m_iGLife)
		{
			expArray[iYear]=((m_fGBasis - m_fGReduction - m_fGResidual) / m_iGLife);
			if (iYear == 0)
				expArray[iYear] += m_fGReduction;
			fAD += expArray[iYear];
			adArray[iYear]= fAD;



			iYear++;
		}
	}
	else //For Tax Purposes
	{
		while (iYear < m_iTLife)
		{
			expArray[iYear]=((m_fTBasis - m_fTReduction - m_fTResidual) / m_iTLife);
			if (iYear == 0)
				expArray[iYear] += m_fTReduction;
			fAD += expArray[iYear];
			adArray[iYear]= fAD;

			iYear++;
		}
	}
	return;
}


/*=================================
Double Declining Balance Formula
---------------------
Stores the expense in 
expArray[]
==================================*/

void CAsset::DB200 (double *expArray, double *adArray, BOOL IsGAAP)
{
	short iYear;
	short iLife;
	double fBalance;
	double fMultiplier;
	double fSS179;
	double fAD = 0;


	if(IsGAAP)
	{
		fBalance = m_fGBasis - m_fGReduction;
		fMultiplier = 2/(double)m_iGLife;
		fSS179 = m_fGReduction;
		iLife = m_iGLife;
	}
	else
	{
		fBalance = m_fTBasis - m_fTReduction;
		fMultiplier = 2/(double)m_iTLife;
		fSS179 = m_fTReduction;
		iLife = m_iTLife;

	}

	for(iYear=0;iYear<iLife;iYear++)
	{
		expArray[iYear] = fBalance * fMultiplier;
		if (iYear == 0)
			expArray[iYear] += fSS179;
		fBalance -= expArray[iYear];
		fAD += expArray[iYear];
		adArray[iYear]= fAD;

	}

	return;
}

/*=================================
150% Declining Balance Formula
---------------------
Stores the expense in 
expArray[]
==================================*/

void CAsset::DB150 (double *expArray, double *adArray, BOOL IsGAAP)
{
	short iYear;
	double fBalance=0;
	double fMultiplier;
	double fAD=0;
	double fSS179;
	short iLife;


	if(IsGAAP)
	{
		fBalance = m_fGBasis - m_fGReduction;
		fMultiplier = 1.5/(double)m_iGLife;
		fSS179 = m_fGReduction;
		iLife = m_iGLife;
	}
	else
	{
		fBalance = m_fTBasis - m_fTReduction;
		fMultiplier = 1.5/(double)m_iTLife;
		fSS179 = m_fTReduction;
		iLife = m_iTLife;
	}

	for(iYear=0;iYear<iLife;iYear++)
	{
		expArray[iYear] = fBalance * fMultiplier;
		if (iYear == 0)
			expArray[iYear] += fSS179;
		fBalance -= expArray[iYear];
		fAD += expArray[iYear];
		adArray[iYear]= fAD;
	}

	return;
}
/*==============================
Sum of the Years Digits Formula
---------------------
Stores the expense in 
expArray[]
===============================*/

void CAsset::SumYrsDigs (double *expArray, double *adArray, BOOL IsGAAP)
{
	short iLife;
	short iYears_left;
	short iYear;
	short iSigma;
	double fBasis;
	double fAD=0;

	if(IsGAAP)
	{
		iLife = m_iGLife;
		fBasis = m_fGBasis - m_fGReduction;
	}
	else
	{
		iLife = m_iTLife;
		fBasis = m_fTBasis - m_fTReduction;
	}
	
	iYears_left = iLife;

	//total up the years
	iSigma = (short)(iLife * (((double)iLife+(double)1)/(double)2));

	for (iYear=0;iYear<iLife;iYear++)
	{
		expArray[iYear] = fBasis * ((double)iYears_left/(double)iSigma);
		iYears_left -= 1;
		fAD += expArray[iYear];
		adArray[iYear]= fAD;

	}
	return;
}

/*==============================
Macrs Half Year (tables)
---------------------
Stores the expense in 
expArray[]
===============================*/

void CAsset::MacrsHY(double *expArray, double *adArray, BOOL IsGAAP)
{
	double fDepr_exp;
	double fAD = 0;
	short iYear;
	double fBasis;
	double fSS179;

	if(IsGAAP)
	{
		fBasis = m_fGBasis - m_fGReduction;
		fSS179 = m_fGReduction;
	}
	else
	{
		fBasis = m_fTBasis - m_fTReduction;
		fSS179 = m_fTReduction;
	}
   
	static double HYtable3[4]={33.33, 44.45, 14.81,  7.41};

	static double HYtable5[6]={20.00, 32.00, 19.20, 11.52, 11.52, 5.76};

	static double HYtable7[8]={14.29, 24.49, 17.49, 12.49,  8.93, 8.92,
							   8.93,  4.46};

	static double HYtable10[11]={10.00, 18.00, 14.40, 11.52,  9.22, 7.37,
							   6.55,  6.55,  6.56,  6.55,  3.28};

	static double HYtable15[16]={ 5.00,  9.50,  8.55,  7.70,  6.93, 6.23,
							   5.90,  5.90,  5.91,  5.90,  5.91, 5.90,
							   5.91,  5.90,  5.91,  2.95};

	static double HYtable20[21]={3.750, 7.219, 6.677, 6.177, 5.713, 5.285,
							  4.888, 4.522, 4.462, 4.461, 4.462, 4.461,
							  4.462, 4.461, 4.462, 4.461, 4.462, 4.461,
							  4.462, 4.461, 2.231};

	for (iYear=0;iYear<=g_ClassLife[m_iTLife];iYear++)
	{
		switch(m_iTLife)
		{
		case 0: //Three
			fDepr_exp = fBasis * (HYtable3[iYear]/100);
			break;
		case 1: //Five
			fDepr_exp = fBasis * (HYtable5[iYear]/100);
			break;
		case 2: //Seven
			fDepr_exp = fBasis * (HYtable7[iYear]/100);
			break;
		case 3: //Ten
			fDepr_exp = fBasis * (HYtable10[iYear]/100);
			break;
		case 4: //Fifteen
			fDepr_exp = fBasis * (HYtable15[iYear]/100);
			break;
		case 5: //Twenty
			fDepr_exp = fBasis * (HYtable20[iYear]/100);
			break;
		default:
			fDepr_exp = 0;
			break;
		}
		if (iYear == 0)
			fDepr_exp += fSS179;

		//ensure we don't go over the original cost.
		if ((fAD + fDepr_exp) > fBasis)
			fDepr_exp = fBasis-fAD;

		expArray[iYear]=fDepr_exp;

		//calculate A/D
		fAD += expArray[iYear];
		adArray[iYear]= fAD;


	}

	return;
}

/*==============================
Macrs Mid Quarter (tables)
---------------------
Stores the expense in 
expArray[]
===============================*/

void CAsset::MacrsMQ(double *expArray, double *adArray, BOOL IsGAAP)
{
	double fDepr_exp;
	double fAD = 0;
	short  iYear;
	double fBasis;
   	double fSS179;
	short iQtr;

	if(IsGAAP)
	{
		fBasis = m_fGBasis - m_fGReduction;
		fSS179 = m_fGReduction;
	}
	else
	{
		fBasis = m_fTBasis - m_fTReduction;
		fSS179 = m_fTReduction;
	}


	static double MQtable3[4][4] = {{58.33, 27.78, 12.35},
									{41.67, 38.89, 14.14, 5.30},
									{25.00, 50.00, 16.67, 8.33},
									{8.33, 61.11, 20.37, 10.19}};

	static double MQtable5[4][6] = {{35.00, 26.00, 15.60, 11.01, 11.01, 1.38},
									{25.00, 30.00, 18.00, 11.37, 11.37, 4.26},
									{15.00, 34.00, 20.40, 12.24, 11.30, 7.06},
									{5.00, 38.00, 22.80, 13.68, 10.94, 9.58}};

	static double MQtable7[4][8] = {{25.00, 21.43, 15.31, 10.93, 8.75, 8.74, 8.75, 1.09},
									{17.85, 23.47, 16.76, 11.97, 8.87, 8.87, 8.87, 3.33},
									{10.71, 25.51, 18.22, 13.02, 9.30, 8.85, 8.86, 5.53},
									{3.57, 27.55, 19.68, 14.06, 10.04, 8.73, 8.73, 7.64}};

	static double MQtable10[4][11] =   {{17.50, 16.50, 13.20, 10.56, 8.45, 6.76, 6.55, 6.55, 6.56, 6.55, 0.82},
										{12.50, 17.50, 14.00, 11.20, 8.96, 7.17, 6.55, 6.55, 6.56, 6.55, 2.46},
										{7.50, 18.50, 14.80, 11.84, 9.47, 7.58, 6.55, 6.55, 6.56, 6.55, 4.10},
										{2.50, 19.50, 15.60, 12.48, 9.98, 7.99, 6.55, 6.55, 6.56, 6.55, 5.74}};

	static double MQtable15[4][16] =   {{8.75, 9.13, 8.21, 7.39, 6.65, 5.99, 5.90, 5.91, 5.90, 5.91, 5.90, 5.91, 5.90, 5.91, 5.90, 0.74},
										{6.25, 9.38, 8.44, 7.59, 6.83, 6.15, 5.91, 5.90, 5.91, 5.90, 5.91, 5.90, 5.91, 5.90, 5.91, 2.21},
										{3.75, 9.63, 8.66, 7.80, 7.02, 6.31, 5.90, 5.90, 5.91, 5.90, 5.91, 5.90, 5.91, 5.90, 5.91, 3.69},
										{1.25, 9.88, 8.89, 8.00, 7.20, 6.48, 5.90, 5.90, 5.90, 5.91, 5.90, 5.91, 5.90, 5.91, 5.90, 5.17}};
	
	static double MQtable20[4][21] =   {{6.563, 7.000, 6.482, 5.996, 5.546, 5.130, 4.746, 4.459, 4.459, 4.459, 4.459, 4.460, 4.459, 4.460, 4.459, 4.460, 4.459, 4.460, 4.459, 4.460, 0.557},
										{4.688, 7.148, 6.612, 6.116, 5.658, 5.233, 4.841, 4.478, 4.463, 4.463, 4.463, 4.463, 4.463, 4.463, 4.462, 4.463, 4.462, 4.463, 4.462, 4.463, 1.673},
										{2.813, 7.289, 6.742, 6.237, 5.769, 5.336, 4.936, 4.566, 4.460, 4.460, 4.460, 4.460, 4.461, 4.460, 4.461, 4.460, 4.461, 4.460, 4.461, 4.460, 2.788},
										{0.938, 7.430, 6.872, 5.880, 5.439, 5.031, 4.654, 4.458, 4.458, 4.458, 4.458, 4.458, 4.458, 4.458, 4.458, 4.458, 4.458, 4.459, 4.458, 4.459, 3.901}};
	
	//figure out the quarter
	iQtr = (short)(m_tmPurch.GetMonth()/12);

	for (iYear=0;iYear<=g_ClassLife[m_iTLife];iYear++)
	{
		switch(m_iTLife)
		{
		case 0: //three
			fDepr_exp = fBasis * (MQtable3[iQtr][iYear]/100);
			break;
		case 1: //five
			fDepr_exp = fBasis * (MQtable5[iQtr][iYear]/100);
			break;
		case 2: //seven
			fDepr_exp = fBasis * (MQtable7[iQtr][iYear]/100);
			break;
		case 3: //ten
			fDepr_exp = fBasis * (MQtable10[iQtr][iYear]/100);
			break;
		case 4: //fifteen
			fDepr_exp = fBasis * (MQtable15[iQtr][iYear]/100);
			break;
		case 5: //twenty
			fDepr_exp = fBasis * (MQtable20[iQtr][iYear]/100);
			break;
		default:
			fDepr_exp = 0;
			break;
		}

		if (iYear == 0)
			fDepr_exp += fSS179;

		//ensure we don't go over the original cost.
		if ((fAD + fDepr_exp) > fBasis)
			fDepr_exp = fBasis - fAD;

		expArray[iYear]=fDepr_exp;

		//calculate A/D
		fAD += expArray[iYear];
		adArray[iYear]= fAD;

	}

   return;
}

void CAsset::Calculate()
{
	//Free the old memory
	if(m_pGADArray)
		free(m_pGADArray);
	if(m_pGExpArray)
		free(m_pGExpArray);
	if(m_pTADArray)
		free(m_pTADArray);
	if(m_pTExpArray)
		free(m_pTExpArray);

	//Allocate memory for the arrays
	m_pGADArray = (double*) malloc(sizeof(double)*m_iGLife);
	m_pGExpArray = (double*) malloc(sizeof(double)*m_iGLife);
	m_pTADArray = (double*) malloc(sizeof(double)*m_iTLife);
	m_pTExpArray = (double*) malloc(sizeof(double)*m_iTLife);

	//Call the appropriate GAAP Depreciation Calculation
	switch(m_iGMethod)
	{
	case 0: //SL
		SLine(m_pGExpArray, m_pGADArray, TRUE);
		break;
	case 1: //DDB
		DB200(m_pGExpArray, m_pGADArray, TRUE);
		break;
	case 2: //150% DB
		DB150(m_pGExpArray, m_pGADArray, TRUE);
		break;
	case 3: //SYD
		SumYrsDigs(m_pGExpArray, m_pGADArray, TRUE);
		break;
	case 4: //MACRS
		MacrsHY(m_pGExpArray, m_pGADArray, TRUE);
		break;
	case 5:
		MacrsMQ(m_pGExpArray, m_pGADArray, TRUE);
		break;
	}

	//Call the right Tax Depreciation Calcuation
	switch(m_iTMethod)
	{
	case 0: //MACRS HY
		MacrsHY(m_pTExpArray, m_pTADArray, FALSE);
		break;
	case 1: //MACRS MQ
		MacrsMQ(m_pTExpArray, m_pTADArray, FALSE);
		break;
	case 2: //SL
		SLine(m_pTExpArray, m_pTADArray, FALSE);
		break;
	}

}
