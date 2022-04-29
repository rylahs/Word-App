// WordApp.h : main header file for the WORDAPP application
//

#if !defined(AFX_WORDAPP_H__ED75A024_2B4C_4682_A036_41F5B3EB5D2A__INCLUDED_)
#define AFX_WORDAPP_H__ED75A024_2B4C_4682_A036_41F5B3EB5D2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWordAppApp:
// See WordApp.cpp for the implementation of this class
//

class CWordAppApp : public CWinApp
{
public:
	CWordAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWordAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDAPP_H__ED75A024_2B4C_4682_A036_41F5B3EB5D2A__INCLUDED_)
