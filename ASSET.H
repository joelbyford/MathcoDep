// Asset.h: interface for the CAsset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSET_H__42B56473_2D57_4790_9F5C_6B81830349C1__INCLUDED_)
#define AFX_ASSET_H__42B56473_2D57_4790_9F5C_6B81830349C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum GAAP_Methods
{
	SL		=0,
	DB200	=0,
	DB150	=1,
	SYD		=2
};

enum TAX_Methods
{
	ACRS		=0,
	MACRS_HY	=1,
	MACRS_MQ	=2,
	MACRS_MM	=3
};

enum TAX_Lifes
{
	NONE	=0,
	THREE	=3,
	FIVE	=5,
	SEVEN	=7,
	TEN		=10,
	FIFTEEN	=15,
	TWENTY	=20
};


enum ClassLife
{
	None,    //0
	Three,   //1
	Five,    //2
	Seven,   //3
	Ten,     //4
	Fifteen, //5
	Twenty	 //6
};

enum Quarter
{
	Q1,		//0
	Q2,		//1
	Q3,		//2
	Q4		//3
};
class CAsset : public CObject  
{
//Methods
public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	void SLine (double *expArray, double *adArray, BOOL IsGAAP);
	void DB200 (double *expArray, double *adArray, BOOL IsGAAP);
	void DB150 (double *expArray, double *adArray, BOOL IsGAAP);
	void SumYrsDigs (double *expArray, double *adArray, BOOL IsGAAP);
	void MacrsHY(double *expArray, double *adArray, BOOL IsGAAP);
	void MacrsMQ(double *expArray, double *adArray, BOOL IsGAAP);

//Attributes
public:
	//Common Variables
	CString m_strName;
	CString m_strDesc;
	CTime m_tmPurch;
	CTime m_tmDisp;

	//GAAP Variables
	int m_iGMethod;
	int m_iGLife;
	double m_fGBasis;
	double m_fGResidual;
	double m_fGReduction;

	//Tax Variables
	int m_iTMethod;
	int m_iTLife;
	double m_fTBasis;
	double m_fTResidual;
	double m_fTReduction;

	//Temporary Calculation Values
	//DO NOT PERSIST/SERIALIZE
	double *m_pGADArray;
	double *m_pGExpArray;
	double *m_pTExpArray;
	double *m_pTADArray;

//Constructor Deconstructor
public:
	void Calculate(void);
	CAsset();
	CAsset(CAsset &strCopy);
	virtual ~CAsset();

protected:
	DECLARE_SERIAL(CAsset)


};

#endif // !defined(AFX_ASSET_H__42B56473_2D57_4790_9F5C_6B81830349C1__INCLUDED_)
