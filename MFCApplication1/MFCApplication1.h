
// MFCApplication1.h: Hauptheaderdatei für die MFCApplication1-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CMFCApplication1App:
// Siehe MFCApplication1.cpp für die Implementierung dieser Klasse
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App() noexcept;


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;
