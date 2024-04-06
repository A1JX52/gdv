
// ChildView.cpp: Implementierung der CChildView-Klasse

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include "Vector2.h"
#include "Vector3.h"

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