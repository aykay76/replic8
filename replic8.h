// replic8.h : main header file for the replic8 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// Creplic8App:
// See replic8.cpp for the implementation of this class
//

class Creplic8App : public CWinApp
{
public:
	Creplic8App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL PumpMessage();
};

extern Creplic8App theApp;