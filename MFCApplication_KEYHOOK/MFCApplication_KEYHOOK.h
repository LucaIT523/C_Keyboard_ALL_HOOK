
// MFCApplication_KEYHOOK.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplicationKEYHOOKApp:
// See MFCApplication_KEYHOOK.cpp for the implementation of this class
//

class CMFCApplicationKEYHOOKApp : public CWinApp
{
public:
	CMFCApplicationKEYHOOKApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationKEYHOOKApp theApp;
