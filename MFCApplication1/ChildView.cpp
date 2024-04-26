
// ChildView.cpp: Implementierung der CChildView-Klasse

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include "Vector2.h"
#include "Vector3.h"
#include <algorithm>
#include <gl/GL.h>
#include <gl/GLU.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView
CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_COMPUTERGRAFIK_DIAGONALE, &CChildView::OnComputergrafikDiagonale)
	ON_COMMAND(ID_COMPUTERGRAFIK_JULIA, &CChildView::OnComputergrafikJulia)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_COMPUTERGRAFIK_MANDELBROT, &CChildView::OnComputergrafikMandelbrot)
	ON_COMMAND(ID_VEKTOREN_QUADRAT, &CChildView::OnVektorenQuadrat)
	ON_COMMAND(ID_COMPUTERGRAFIK_MANDELBROTBITBLT, &CChildView::OnComputergrafikMandelbrotbitblt)
	ON_COMMAND(ID_COMPUTERGRAFIK_MANDELARRAY, &CChildView::OnComputergrafikMandelarray)
	ON_COMMAND(ID_VEKTOREN_WUERFEL, &CChildView::OnVektorenWuerfel)
	ON_COMMAND(ID_VEKTOREN_DEBUG, &CChildView::OnVektorenDebug)
	ON_COMMAND(ID_VEKTOREN_WUERFELPERSP, &CChildView::OnVektorenWuerfelpersp)
	ON_COMMAND(ID_OPENGL_ERSTER, &CChildView::OnOpenglErster)
END_MESSAGE_MAP()



// CChildView-Meldungshandler

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen
	
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein.
	
	// Rufen Sie nicht CWnd::OnPaint() zum Zeichnen von Nachrichten auf
}

void CChildView::OnComputergrafikDiagonale()
{
	currentMode = 0;

	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	CRect r1, r2;

	GetWindowRect(&r1);

	GetParent()->GetWindowRect(&r2);

	//Wir holen uns die größe der ChildView (unseres Zeichenfensters) und des MAinframes(Hauptfenster)

	int diffX = r2.Width() - r1.Width();

	int diffY = r2.Height() - r1.Height();

	//Wir bilden die Differenz der Höhe und Breite der Beiden Fenster 

	GetParent()->SetWindowPos(NULL, 100, 100, 600 + diffX, 600 + diffY, SWP_SHOWWINDOW);

	//Wir rechnen die Differenzen mit drauf damit Unser Zeichenfenster Quadratisch ist NICHT mehr de Mainframe

	UpdateWindow();

	//UpdateWindow(), weil sonst zuerst die Linie gezogen wird und dann erst das fenster angepasst wird

	CRect rect;
	GetClientRect(&rect);

	CDC* pDc = GetDC();
	pDc->FillSolidRect(rect, RGB(255, 255, 255));

	for (int i = 0; i < 600; i++) {
		pDc->SetPixel(i, i, RGB(255, 0, 0));
	}
}

void CChildView::OnComputergrafikJulia()
{
	currentMode = 2;

	CRect r1, r2;

	GetWindowRect(&r1);

	GetParent()->GetWindowRect(&r2);

	//Wir holen uns die größe der ChildView (unseres Zeichenfensters) und des MAinframes(Hauptfenster)

	int diffX = r2.Width() - r1.Width();

	int diffY = r2.Height() - r1.Height();

	//Wir bilden die Differenz der Höhe und Breite der Beiden Fenster 

	GetParent()->SetWindowPos(NULL, 100, 100, 600 + diffX, 600 + diffY, SWP_SHOWWINDOW);

	//Wir rechnen die Differenzen mit drauf damit Unser Zeichenfenster Quadratisch ist NICHT mehr de Mainframe

	UpdateWindow();

	minX = -1.6;
	deltaX = 3.2;

	minY = -1.6;
	deltaY = 3.2;

	//UpdateWindow(), weil sonst zuerst die Linie gezogen wird und dann erst das fenster angepasst wird

	Julia();
}

void CChildView::Julia()
{
	CDC* pDc = GetDC();

	for (int xp = 0; xp < 600; xp++) {
		for (int yp = 0; yp < 600; yp++) {
			double xd = minX + xp * deltaX / 600.0;  //.0 damit keine Integerdivision
			double yd = minY + yp * deltaY / 600.0;  //.0 damit keine Integerdivision

			double a_alt = xd;
			double b_alt = yd;

			double a_neu, b_neu;

			int k;
			for (k = 0; k < 255; k++) {
				a_neu = a_alt * a_alt - b_alt * b_alt - 0.75;
				b_neu = 2 * a_alt * b_alt + 0.06;

				if (a_neu * a_neu + b_neu * b_neu > 4) {
					break;
				}
				a_alt = a_neu;
				b_alt = b_neu;
			}
			if (k < 255) {
				//schleife wurde unterbrochen, da der maximalwert erreicht wurde, die folge divergiert also
				//je groesser k ist, desto schneller konvergiert die folge, desto dunkler muss der pixel sein

				if (0) {
					pDc->SetPixel(xp, yp, RGB(255 - k, 0, 0));
				}
				else {
					pDc->SetPixel(xp, yp, RGB(255, 0, 0));
				}
			}
			else {
				//hier konvergiert die folge
				pDc->SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);
	double xd = minX + point.x * deltaX / 600.;
	double yd = minY + point.y * deltaY / 600.;

	deltaX = deltaX / 2;
	deltaY = deltaY / 2;

	minX = xd - deltaX / 2;
	minY = yd - deltaY / 2;

	if (currentMode == 2) {
		Julia();
	}
	else if (currentMode == 1) {
		Mandelbrot();
	}
}

void CChildView::Mandelbrot()
{
	currentMode = 1;

	CDC* pDc = GetDC();

	long t1 = clock();

	for (int xp = 0; xp < 600; xp++) {
		for (int yp = 0; yp < 600; yp++) {
			double xd = minX + xp * deltaX / 600.0;  //.0 damit keine Integerdivision
			double yd = minY + yp * deltaY / 600.0;  //.0 damit keine Integerdivision

			double a_alt = xd;
			double b_alt = yd;

			double a_neu, b_neu;

			int k;
			for (k = 0; k < 255; k++) {
				//im vergleich zu julia abgeaendert
				a_neu = a_alt * a_alt - b_alt * b_alt + xd;
				b_neu = 2 * a_alt * b_alt + yd;

				if (a_neu * a_neu + b_neu * b_neu > 4) {
					break;
				}
				a_alt = a_neu;
				b_alt = b_neu;
			}
			if (k < 255) {
				//sichtbarkeit wird um den faktor 10 verstaerkt
				//je groesser k ist, desto schneller konvergiert die folge, desto dunkler muss der pixel sein

				if (1) {
					int h = 255 - k * 10;
					pDc->SetPixel(xp, yp, RGB(h, h, h < 0 ? 255 : 0));
				}
				else {
					pDc->SetPixel(xp, yp, RGB(255, 0, 0));
				}
			}
			else {
				//hier konvergiert die folge
				pDc->SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
	float time = (float) (clock() - t1) / CLOCKS_PER_SEC;
	CString txt;
	txt.Format(_T("dauer: %7.4f"), time);
	GetParent()->SetWindowTextW(txt);
}

void CChildView::MandelbrotBitBlt()
{
	currentMode = 0;

	CDC* pDc = GetDC();

	m_DC.DeleteDC();
	m_DC.CreateCompatibleDC(pDc);
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDc, 600, 600);
	m_DC.SelectObject(&bm);

	long t1 = clock();

	for (int xp = 0; xp < 600; xp++) {
		for (int yp = 0; yp < 600; yp++) {
			double xd = minX + xp * deltaX / 600.0;  //.0 damit keine Integerdivision
			double yd = minY + yp * deltaY / 600.0;  //.0 damit keine Integerdivision

			double a_alt = xd;
			double b_alt = yd;

			double a_neu, b_neu;

			int k;
			for (k = 0; k < 255; k++) {
				//im vergleich zu julia abgeaendert
				a_neu = a_alt * a_alt - b_alt * b_alt + xd;
				b_neu = 2 * a_alt * b_alt + yd;

				if (a_neu * a_neu + b_neu * b_neu > 4) {
					break;
				}
				a_alt = a_neu;
				b_alt = b_neu;
			}
			if (k < 255) {
				//sichtbarkeit wird um den faktor 10 verstaerkt
				//je groesser k ist, desto schneller konvergiert die folge, desto dunkler muss der pixel sein

				if (1) {
					int h = 255 - k * 10;
					m_DC.SetPixel(xp, yp, RGB(h, h, h < 0 ? 255 : 0));
				}
				else {
					m_DC.SetPixel(xp, yp, RGB(255, 0, 0));
				}
			}
			else {
				//hier konvergiert die folge
				m_DC.SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
	pDc->BitBlt(0, 0, 600, 600, &m_DC, 0, 0, SRCCOPY);

	float time = (float)(clock() - t1) / CLOCKS_PER_SEC;
	CString txt;
	txt.Format(_T("dauer: %7.4f"), time);
	GetParent()->SetWindowTextW(txt);
}

void CChildView::MandelArray()
{
	currentMode = 0;

	CDC* pDc = GetDC();

	m_DC.DeleteDC();
	m_DC.CreateCompatibleDC(pDc);

	COLORREF* pixel = (COLORREF*) calloc(600 * 600, sizeof(COLORREF));
	COLORREF* ptr;

	long t1 = clock();

	for (int xp = 0; xp < 600; xp++) {
		for (int yp = 0; yp < 600; yp++) {
			double xd = minX + xp * deltaX / 600.0;  //.0 damit keine Integerdivision
			double yd = minY + yp * deltaY / 600.0;  //.0 damit keine Integerdivision

			double a_alt = xd;
			double b_alt = yd;

			double a_neu, b_neu;

			int k;
			for (k = 0; k < 255; k++) {
				//im vergleich zu julia abgeaendert
				a_neu = a_alt * a_alt - b_alt * b_alt + xd;
				b_neu = 2 * a_alt * b_alt + yd;

				if (a_neu * a_neu + b_neu * b_neu > 4) {
					break;
				}
				a_alt = a_neu;
				b_alt = b_neu;
			}
			ptr = pixel + yp * 600 + xp;

			if (k < 255) {
				// sichtbarkeit wird um den faktor 10 verstaerkt
				// je groesser k ist, desto schneller konvergiert die folge, desto dunkler muss der pixel sein

				if (1) {
					int h = 255 - k * 10;
					*ptr = RGB(h, h, h < 0 ? 255 : 0);
				}
				else {
					*ptr = RGB(255, 0, 0);
				}
			}
			else {
				//hier konvergiert die folge
				*ptr = RGB(0, 0, 0);
			}
		}
	}
	CBitmap bm;
	bm.CreateBitmap(600, 600, 1, 32, pixel);
	m_DC.SelectObject(&bm);

	pDc->BitBlt(0, 0, 600, 600, &m_DC, 0, 0, SRCCOPY);

	float time = (float)(clock() - t1) / CLOCKS_PER_SEC;
	CString txt;
	txt.Format(_T("dauer: %7.4f"), time);
	GetParent()->SetWindowTextW(txt);
}

void CChildView::OnComputergrafikMandelbrot()
{
	CRect r1, r2;

	GetWindowRect(&r1);

	GetParent()->GetWindowRect(&r2);

	//Wir holen uns die größe der ChildView (unseres Zeichenfensters) und des MAinframes(Hauptfenster)

	int diffX = r2.Width() - r1.Width();

	int diffY = r2.Height() - r1.Height();

	//Wir bilden die Differenz der Höhe und Breite der Beiden Fenster 

	GetParent()->SetWindowPos(NULL, 100, 100, 600 + diffX, 600 + diffY, SWP_SHOWWINDOW);

	//Wir rechnen die Differenzen mit drauf damit Unser Zeichenfenster Quadratisch ist NICHT mehr de Mainframe

	UpdateWindow();

	minX = -2.0;
	deltaX = 2.5;

	minY = -1.25;
	deltaY = 2.5;

	//UpdateWindow(), weil sonst zuerst die Linie gezogen wird und dann erst das fenster angepasst wird

	Mandelbrot();
}

void CChildView::OnVektorenQuadrat()
{
	currentMode = 0;

	Vector2 quadrat[4];
	quadrat[0] = Vector2(50, 50);
	quadrat[1] = Vector2(100, 50);
	quadrat[2] = Vector2(100, 100);
	quadrat[3] = Vector2(50, 100);

	CDC* pDc = GetDC();

	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();

	m_DC.DeleteDC();
	m_DC.CreateCompatibleDC(pDc);
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDc, width, height);
	m_DC.SelectObject(&bm);

	CPen myPen(PS_SOLID, 2, RGB(255, 0, 0));
	m_DC.SelectObject(&myPen);

	Matrix2 matT, matRot, matScale;
	Vector2 center = (quadrat[0] + quadrat[2]) * 0.5;

	double* v = center.getCoordinates();

	matT.setTrans(width / 2 - v[0], height / 2 - v[1]);
	matRot.setRotate(5);
	matScale.setScale(1.1);

	for (int i = 0; i < 4; i++) {
		quadrat[i] = matT * quadrat[i];
		quadrat[i] = matScale * quadrat[i];
	}
	
	for (int anim = 0; anim < 160; anim++) {
		m_DC.FillSolidRect(rect, RGB(255, 255, 255));
		center = (quadrat[0] + quadrat[2]) * 0.5;

		for (int i = 0; i < 4; i++) {
			quadrat[i] = quadrat[i] - center;
			quadrat[i] = (1 ? matRot : matScale) * quadrat[i];
			quadrat[i] = quadrat[i] + center;
		}
		//Quadrat malen
		m_DC.MoveTo(quadrat[3].toPoint());

		for (int i = 0; i < 4; i++) {
			m_DC.LineTo(quadrat[i].toPoint());
		}
		pDc->BitBlt(0, 0, width, height, &m_DC, 0, 0, SRCCOPY);
		Sleep(70);

		if (GetAsyncKeyState(VK_ESCAPE) & 0x01) {
			m_DC.FillSolidRect(rect, RGB(255, 255, 255));
			return;
		}
	}
	bm.DeleteObject();
	ReleaseDC(pDc);
}

void CChildView::OnComputergrafikMandelbrotbitblt()
{
	CRect r1, r2;

	GetWindowRect(&r1);

	GetParent()->GetWindowRect(&r2);

	//Wir holen uns die größe der ChildView (unseres Zeichenfensters) und des MAinframes(Hauptfenster)

	int diffX = r2.Width() - r1.Width();

	int diffY = r2.Height() - r1.Height();

	//Wir bilden die Differenz der Höhe und Breite der Beiden Fenster 

	GetParent()->SetWindowPos(NULL, 100, 100, 600 + diffX, 600 + diffY, SWP_SHOWWINDOW);

	//Wir rechnen die Differenzen mit drauf damit Unser Zeichenfenster Quadratisch ist NICHT mehr de Mainframe

	UpdateWindow();

	minX = -2.0;
	deltaX = 2.5;

	minY = -1.25;
	deltaY = 2.5;

	//UpdateWindow(), weil sonst zuerst die Linie gezogen wird und dann erst das fenster angepasst wird

	MandelbrotBitBlt();
}


void CChildView::OnComputergrafikMandelarray()
{
	CRect r1, r2;

	GetWindowRect(&r1);

	GetParent()->GetWindowRect(&r2);

	//Wir holen uns die größe der ChildView (unseres Zeichenfensters) und des MAinframes(Hauptfenster)

	int diffX = r2.Width() - r1.Width();

	int diffY = r2.Height() - r1.Height();

	//Wir bilden die Differenz der Höhe und Breite der Beiden Fenster 

	GetParent()->SetWindowPos(NULL, 100, 100, 600 + diffX, 600 + diffY, SWP_SHOWWINDOW);

	//Wir rechnen die Differenzen mit drauf damit Unser Zeichenfenster Quadratisch ist NICHT mehr de Mainframe

	UpdateWindow();

	minX = -2.0;
	deltaX = 2.5;

	minY = -1.25;
	deltaY = 2.5;

	//UpdateWindow(), weil sonst zuerst die Linie gezogen wird und dann erst das fenster angepasst wird

	MandelArray();
}

void CChildView::OnVektorenWuerfel()
{
	currentMode = 0;

	Vector3 cube[8];
	cube[0] = Vector3(50, 50, 0);
	cube[1] = Vector3(100, 50, 0);
	cube[2] = Vector3(100, 100, 0);
	cube[3] = Vector3(50, 100, 0);

	cube[4] = Vector3(50, 50, 50);
	cube[5] = Vector3(100, 50, 50);
	cube[6] = Vector3(100, 100, 50);
	cube[7] = Vector3(50, 100, 50);

	// (75, 75, 25)
	CDC* pDc = GetDC();

	CRect rect;
	GetClientRect(&rect);
	CPen myPen(PS_SOLID, 2, RGB(255, 0, 0));
	pDc->SelectObject(&myPen);

	Matrix3 matT, matTInv, rotZ, rotX;
	rotX.setRotate(45, 0);
	rotZ.setRotate(45, 2);

	//for (int anim = 0; anim < 80; anim++) {
		pDc->FillSolidRect(rect, RGB(255, 255, 255));

		matT.setTrans(-75., -75., -25.);
		matTInv.setTrans(75., 75., 25.);

		for (int i = 0; i < 8; i++) {
			cube[i] = matT * cube[i];

			//nicht kommutativ, bei perspektivischer Bertrachtung irrelevant, kommt durch die parallelbetrachtung
			cube[i] = rotZ * cube[i];
			cube[i] = rotX * cube[i];

			cube[i] = matTInv * cube[i];
		}

		//Quadrat hinten malen
		pDc->MoveTo(cube[3].toPoint());

		for (int i = 0; i < 4; i++) {
			pDc->LineTo(cube[i].toPoint());
		}

		//Quadrat vorne malen
		pDc->MoveTo(cube[7].toPoint());

		for (int i = 4; i < 8; i++) {
			pDc->LineTo(cube[i].toPoint());
		}

		//Senkrechten malen
		for (int i = 0; i < 4; i++) {
			pDc->MoveTo(cube[i].toPoint());
			pDc->LineTo(cube[i + 4].toPoint());
		}
		//Sleep(100);
	//}
}

void CChildView::OnVektorenDebug()
{
	currentMode = 0;

	Matrix2 test = Matrix2();
	test.m[0][1] = 5.;
	test.m[0][2] = 10.;
	test.m[1][2] = 15.;

	test.transpose();

	Matrix2 mat1 = Matrix2();
	mat1.m[0][0] = 1.;
	mat1.m[0][1] = -3.;
	mat1.m[1][1] = -2.;

	Matrix2 mat2 = Matrix2();
	mat2.m[0][0] = -1.;
	mat2.m[0][1] = 4.;
	mat2.m[1][0] = 7.;
	mat2.m[1][1] = 1.;

	Matrix2 res = mat1 * mat2;

	CString txt;
	txt.Format(_T("hello world!"));
	GetParent()->SetWindowTextW(txt);
}

void CChildView::OnVektorenWuerfelpersp()
{
	currentMode = 0;

	Vector3 cpyCube[8];
	cpyCube[0] = Vector3(50, 50, 0);
	cpyCube[1] = Vector3(100, 50, 0);
	cpyCube[2] = Vector3(100, 100, 0);
	cpyCube[3] = Vector3(50, 100, 0);

	cpyCube[4] = Vector3(50, 50, 50);
	cpyCube[5] = Vector3(100, 50, 50);
	cpyCube[6] = Vector3(100, 100, 50);
	cpyCube[7] = Vector3(50, 100, 50);

	CDC* pDc = GetDC();

	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();

	m_DC.DeleteDC();
	m_DC.CreateCompatibleDC(pDc);
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDc, width, height);
	m_DC.SelectObject(&bm);

	CPen myPen(PS_SOLID, 2, RGB(255, 0, 0));
	m_DC.SelectObject(&myPen);

	Matrix3 matT, matTInv, rotY, rotX, rotZ, matP;
	Vector3 center = (cpyCube[0] + cpyCube[6]) * 0.5;
	double* cord = center.getCoordinates();

	matT.setTrans(-cord[0], -cord[1], -cord[2]);
	matTInv.setTrans(cord[0], cord[1], cord[2]);

	//perspektivische Betrachtung lässt würfel ohne rotation sichtbar werden
	//legt entfernung der kamera fest
	//je größer, desto weiter weg
	matP.setPersp(100);

	Vector3 cube[8];

	for (int anim = 0; anim < 160; anim++) {
		std::copy(std::begin(cpyCube), std::end(cpyCube), std::begin(cube));

		m_DC.FillSolidRect(rect, RGB(255, 255, 255));

		for (int i = 0; i < 8; i++) {
			cube[i] = matT * cube[i];
			if (1) {
				//nicht kommutativ, bei perspektivischer Bertrachtung irrelevant, kommt durch die parallelbetrachtung
				rotX.setRotate(anim * 0.1, 0);
				cube[i] = rotX * cube[i];
			}

			if (1) {
				rotY.setRotate(anim * 0.1, 1);
				cube[i] = rotY * cube[i];
			}

			if (1) {
				rotZ.setRotate(anim * 0.1, 1);
				cube[i] = rotZ * cube[i];
			}
			//perspektivische betrachtung anwenden
			cube[i] = matP * cube[i];
			//homogene Koordiante ermitteln; homogene Koordinate zurückrechnen, damit Translation wieder funktioniert
			double scal = 1 / cube[i].getCoordinates()[3];
			cube[i] = cube[i] * scal;

			cube[i] = matTInv * cube[i];
		}

		//Quadrat hinten malen
		m_DC.MoveTo(cube[3].toPoint());

		for (int i = 0; i < 4; i++) {
			m_DC.LineTo(cube[i].toPoint());
		}

		//Quadrat vorne malen
		m_DC.MoveTo(cube[7].toPoint());

		for (int i = 4; i < 8; i++) {
			m_DC.LineTo(cube[i].toPoint());
		}

		//Senkrechten malen
		for (int i = 0; i < 4; i++) {
			m_DC.MoveTo(cube[i].toPoint());
			m_DC.LineTo(cube[i + 4].toPoint());
		}
		pDc->BitBlt(0, 0, width, height, &m_DC, 0, 0, SRCCOPY);
		Sleep(70);

		if (GetAsyncKeyState(VK_ESCAPE) & 0x01) {
			return;
		}
	}
	bm.DeleteObject();
	ReleaseDC(pDc);
}

void CChildView::GLInit(int Breite, int Hoehe, int Modus)
{
	static HDC hdc;
	static HGLRC hglrc;
	int iPixelFormat;
	HWND hwnd = GetSafeHwnd();

	static PIXELFORMATDESCRIPTOR pfd = //pfd legt das Aussehen der Szene fest
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,						//Versionsnummer
		PFD_DRAW_TO_WINDOW |	//pfd muss Windows unterstützen
		PFD_SUPPORT_OPENGL |	//pfd muss OpenGL unterstützen
		PFD_DOUBLEBUFFER,		//Doppelpuffer wird unterstützt
		PFD_TYPE_RGBA,			//RGBA-Farbformat auswählen
		32,						//Bit-Farbtiefe
		0, 0, 0, 0, 0, 0,		//Farbbits werden ignoriert
		0,						//kein Alphapuffer
		0,						//Schiebebit ignoriert
		0,						//kein Ansammlungspuffer
		0, 0, 0, 0,				//Ansammlungsbits werden ignoriert
		16,						//16bit Z-Puffer (Tiefenpuffer)
		16,						//Masken-Puffer
		0,						//keinen Hilfs-Puffer
		PFD_MAIN_PLANE,			//Festlegung der Zeichenebene (Hauptebene)
		0,						//reserviert
		0, 0, 0					//Ebenenmasken werden ignoriert
	};
	CDC* pDC = GetDC();
	CRect gesamt, client;
	GetWindowRect(&gesamt);
	GetClientRect(&client);
	int diff_x = gesamt.Width() - client.Width();
	int diff_y = gesamt.Height() - client.Height();
	m_height = Hoehe;
	m_width = Breite;

	switch (Modus) {
	case 1:  // Modus 1 -> Initialisierung

		// ---------- Fenstergröße
		GetParent()->SetWindowPos(&wndTop, 50, 50, m_height + diff_x, m_width + diff_y, 0);
		//		GetParent()->ShowWindow(SW_NORMAL);
		GetParent()->RedrawWindow();
		// ------ Device Context
		hdc = pDC->GetSafeHdc();

		// ------ Pixelformat einstellen (OpenGL-fähig)
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);

		// ---- Rendering-Context erstellen und zuweisen
		hglrc = wglCreateContext(hdc);
		if (hglrc == NULL) {
			SetWindowText(CString("Fehler beim RC !"));
			Sleep(2000);
		}
		wglMakeCurrent(hdc, hglrc);
		break;
	case 0:  // Modus 0 -> Beenden
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);

		ReleaseDC(pDC);
		break;
	}
	return;
}

void CChildView::Bunter_Einheitswuerfel()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);			//grün bei z = -0.5
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(1, 0, 0);			//rot bei z = 0.5
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(1, 0.75, 0.25);	//orange bei y = -0.5
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glColor3f(0, 0, 1);			//blau bei y = 0.5
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);

	glColor3f(1, 0, 1);			//lila bei x =  0.5
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	glColor3f(1, 1, 0);			//gelb bei x = -0.5
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
}

void CChildView::Achsenkreuz(float l)
{
	GLfloat Pfeil = (float) 0.05;

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	
	//achsen
	glVertex3f(-l, 0, 0);
	glVertex3f(l, 0, 0);

	glVertex3f(0, -l, 0);
	glVertex3f(0, l, 0);

	glVertex3f(0, 0, -l);
	glVertex3f(0, 0, l);

	//pfeile
	glVertex3f(l, 0, 0);
	glVertex3f(l - Pfeil, Pfeil, 0);

	glVertex3f(l, 0, 0);
	glVertex3f(l - Pfeil, -Pfeil, 0);

	glVertex3f(0, l, 0);
	glVertex3f(0, l - Pfeil, Pfeil);

	glVertex3f(0, l, 0);
	glVertex3f(0, l - Pfeil, -Pfeil);

	glVertex3f(0, 0, l);
	glVertex3f(Pfeil, 0, l - Pfeil);

	glVertex3f(0, 0, l);
	glVertex3f(-Pfeil, 0, l - Pfeil);
	glEnd();
}

void CChildView::OnOpenglErster()
{
	GLInit(1200, 1200, 1);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	for (int anim = 0; anim < 160; anim++) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		Achsenkreuz(1.5);

		//großer würfel
		Bunter_Einheitswuerfel();

		//würfelkäfig
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glScaled(1.05, 1.05, 1.05);
		Bunter_Einheitswuerfel();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//kleiner würfel
		glRotated(anim, 1, 0, 0);
		glTranslated(0.75, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		Bunter_Einheitswuerfel();

		glLoadIdentity();

		//kleiner würfel
		glRotated(anim, 0, 1, 0);
		glTranslated(0, 0.75, 0);
		glScaled(0.5, 0.5, 0.5);
		Bunter_Einheitswuerfel();

		glLoadIdentity();

		//kleiner würfel
		glRotated(anim, 0, 0, 1);
		glTranslated(0, 0, 0.75);
		glScaled(0.5, 0.5, 0.5);
		Bunter_Einheitswuerfel();

		//double buffering
		SwapBuffers(wglGetCurrentDC());
		Sleep(100);
	}
	GLInit(0, 0, 0);
}