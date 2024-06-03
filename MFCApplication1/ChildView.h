#pragma once

// CChildView-Fenster
class CChildView : public CWnd
{
// Konstruktion
public:
	CChildView();

// Attribute
public:
	double minX;
	double deltaX;
	double minY;
	double deltaY;
	int currentMode;
	CDC m_DC;
	int m_height;
	int m_width;

// Vorgänge
public:
	void Julia();
	void Mandelbrot();
	void MandelbrotBitBlt();
	void MandelArray();
	void GLInit(int Breite, int Hoehe, int Modus);
	void Bunter_Einheitswuerfel();
	void Achsenkreuz(float l);
	void drawCube();
	void myMaterial(float r, float g, float b, int s);

// Überschreibungen
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CChildView();

	// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnComputergrafikDiagonale();
	afx_msg void OnComputergrafikJulia();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnComputergrafikMandelbrot();
	afx_msg void OnVektorenQuadrat();
	afx_msg void OnComputergrafikMandelbrotbitblt();
	afx_msg void OnComputergrafikMandelarray();
	afx_msg void OnVektorenWuerfel();
	afx_msg void OnVektorenDebug();
	afx_msg void OnVektorenWuerfelpersp();
	afx_msg void OnOpenglErster();
	afx_msg void OnOpenglGlu1();
	afx_msg void OnOpenglKugel();
	afx_msg void OnOpenglKugel32783();
};