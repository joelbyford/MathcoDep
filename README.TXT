========================================================================
     Microsoft Foundation Class Library for Windows CE: MathcoDep
========================================================================


AppWizard has created this MathcoDep application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your MathcoDep application.

MathcoDep.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CMathcoDepApp application class.

MathcoDep.cpp
    This is the main application source file that contains the application
    class CMathcoDepApp.

MathcoDep.rc
    This is a listing of all of the Microsoft Windows CE resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	eMbedded Visual C++.

res\MathcoDep.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file MathcoDep.rc.

res\MathcoDep.rc2
    This file contains resources that are not edited by Microsoft 
	eMbedded Visual C++.  You should place all resources not
	editable by the resource editor in this file.

MathcoDep.vcc
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

res\Cmdbar.bmp
    This bitmap file is used to create tiled images for the command bar.
    The initial command bar is constructed in the CMainFrame class. 
    Edit this cmdbar bitmap along with the array in MainFrm.cpp 
    to add more command bar buttons.


/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

MathcoDepDoc.h, MathcoDepDoc.cpp - the document
    These files contain your CMathcoDepDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CMathcoDepDoc::Serialize).

MathcoDepView.h, MathcoDepView.cpp - the view of the document
    These files contain your CMathcoDepView class.
    CMathcoDepView objects are used to view CMathcoDepDoc objects.



/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named MathcoDep.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft eMbedded Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
