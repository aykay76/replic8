// replic8View.cpp : implementation of the Creplic8View class
//

#include "stdafx.h"
#include "replic8.h"

#include "r8/r8_base.h"
#include "r8/rendererbitmap.h"
#include "r8/renderergraphics.h"

#include "replic8Doc.h"
#include "replic8View.h"

#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

#include <gdiplus.h>
#include ".\replic8view.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BITMAPINFO bmi;
DWORD* pbb = NULL;
int g_height = 600;
int g_pitch = 800;
int g_width = 800;

// Creplic8View

IMPLEMENT_DYNCREATE(Creplic8View, CView)

BEGIN_MESSAGE_MAP(Creplic8View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_MESSAGE(WM_USER+1, OnUser1)
END_MESSAGE_MAP()

// Creplic8View construction/destruction

Creplic8View::Creplic8View()
{
	m_pBitmap = NULL;
	m_gdiplusBitmap = NULL;
}

Creplic8View::~Creplic8View()
{
}

BOOL Creplic8View::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = 640;
	cs.cy = 480;

	return CView::PreCreateWindow(cs);
}

// Creplic8View drawing
DWORD dwLastSecond = GetTickCount();
int nFrame = 0;
int nFramesPerSecond = 0;
bool gdiplus = false;

void Creplic8View::OnDraw(CDC* pDC)
{
	Creplic8Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	

	CRect rc;
	GetClientRect(rc);

	if (gdiplus)
	{
		Gdiplus::Graphics graphics(pDC->GetSafeHdc());

		graphics.DrawImage(m_gdiplusBitmap, 0, 0);
	}
	else
	{
		CRgn rgn;
		CBrush *black = CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH));

		SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, g_width, g_height, 0, 0, 0, g_height, (CONST VOID *)pbb, &bmi, DIB_RGB_COLORS);

		CString str;
		str.Format("%f, %f, %f", GetDocument()->getScene().activeCamera()->position().x(), GetDocument()->getScene().activeCamera()->position().y(), GetDocument()->getScene().activeCamera()->position().z());
		pDC->TextOut(0, 600, str);

		nFrame++;
		if (GetTickCount() - dwLastSecond > 1000) {
			dwLastSecond = GetTickCount();
			nFramesPerSecond = nFrame;
			nFrame = 0;
		}

		str.Format("%d", nFramesPerSecond);
		pDC->TextOut(800, 0, str);
		str.Format("%d", GetDocument()->getScene().m_particles.size());
		pDC->TextOut(800, 20, str);
	}

	PostMessage(WM_TIMER, 0, 0);
}


// Creplic8View printing

BOOL Creplic8View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Creplic8View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Creplic8View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Creplic8View diagnostics

#ifdef _DEBUG
void Creplic8View::AssertValid() const
{
	CView::AssertValid();
}

void Creplic8View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Creplic8Doc* Creplic8View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Creplic8Doc)));
	return (Creplic8Doc*)m_pDocument;
}
#endif //_DEBUG

r8::Vector vectorFromLatLongHeight(float lat, float lon, float height)
{
	double h = 6378.145 + height;
	double cosLat = cos(lat);

	double x = h * cosLat * sin(lon);
	double y = -h * cosLat * cos(lon);
	double z = h * sin(lat);

	return r8::Vector(x, y, z);
}

// Creplic8View message handlers
r8::Camera *pCamera;

int Creplic8View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a camera at the origin of world space looking directly down the z-axis - easiest scenario  :)
	GetDocument()->getScene().createCamera(r8::Vector(5.0, 5.0, -55.0), r8::Vector(5.0F, 5.0F, 5.0F), r8::Vector(0.0, 1.0, 0.0));

	for (int i = 0; i < 1000; i++)
	{
		GetDocument()->getScene().createCube(r8::Vector(
			(float)rand() / ((float)RAND_MAX * 2.0F) * 50.0, 
			(float)rand() / ((float)RAND_MAX * 2.0F) * 50.0, 
			(float)rand() / ((float)RAND_MAX * 2.0F) * 100.0),
			(float)rand() / ((float)RAND_MAX * 4.0F));
	}
/*	GetDocument()->getScene().createCube(r8::Vector(0.0, 0.0, 10.0), 1.0);
	GetDocument()->getScene().createCube(r8::Vector(0.0, 10.0, 0.0), 1.0);
	GetDocument()->getScene().createCube(r8::Vector(10.0, 0.0, 0.0), 1.0);
	GetDocument()->getScene().createCube(r8::Vector(0.0, 10.0, 10.0), 1.0);
	GetDocument()->getScene().createCube(r8::Vector(10.0, 0.0, 10.0), 1.0);
	GetDocument()->getScene().createCube(r8::Vector(10.0, 10.0, 0.0), 1.0);
	GetDocument()->getScene().createCube(r8::Vector(10.0, 10.0, 10.0), 1.0);
	GetDocument()->getScene().createCube(r8::Vector(0.0, 0.0, 0.0), 1.0);
*/
	// intitialise the bitmap info
	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biHeight = -g_height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biSizeImage = g_width * 4 * g_height;
	bmi.bmiHeader.biWidth = g_width;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	pbb = new DWORD[g_height * g_width];

	return 0;
}

BOOL Creplic8View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void Creplic8View::OnLButtonDown(UINT nFlags, CPoint point)
{
	RedrawWindow();

	CView::OnLButtonDown(nFlags, point);
}

BYTE keys[256];
void Creplic8View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (GetDocument()->running() == true) return;

	switch (nChar) {
		case VK_SPACE:
			GetDocument()->getScene().activeCamera()->rePoint();
			GetDocument()->start();
			PostMessage(WM_TIMER);
			break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

DWORD lastUpdate = 0;

void Creplic8View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (cx && cy) {
		CDC* pDC = GetDC();
		if (m_pBitmap) {
			delete m_pBitmap;
		}
		if (m_gdiplusBitmap)
		{
			delete m_gdiplusBitmap;
		}

		m_pBitmap = new CBitmap;
		m_pBitmap->CreateCompatibleBitmap(pDC, cx, cy);

		Gdiplus::Graphics graphics(pDC->GetSafeHdc());
		m_gdiplusBitmap = new Bitmap(cx, cy, &graphics);

		ReleaseDC(pDC);
	}
}

LRESULT Creplic8View::OnUser1(WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			GetDocument()->getScene().activeCamera()->moveLeft(0.1);
		} else {
			GetDocument()->getScene().activeCamera()->yaw(1.0 * 3.141592653 / 180.0);
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			GetDocument()->getScene().activeCamera()->moveRight(0.1);
		} else {
			GetDocument()->getScene().activeCamera()->yaw(-1.0 * 3.141592653 / 180.0);
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			GetDocument()->getScene().activeCamera()->moveUp(0.1);
		} else {
			GetDocument()->getScene().activeCamera()->pitch(-1.0 * 3.141592653 / 180.0);
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			GetDocument()->getScene().activeCamera()->moveDown(0.1);
		} else {
			GetDocument()->getScene().activeCamera()->pitch(1.0 * 3.141592653 / 180.0);
		}
	}
	if (GetAsyncKeyState(VK_HOME) & 0x8000) {
		GetDocument()->getScene().activeCamera()->roll(-1.0 * 3.141592653 / 180.0);
	}
	if (GetAsyncKeyState(VK_END) & 0x8000) {
		GetDocument()->getScene().activeCamera()->roll(1.0 * 3.141592653 / 180.0);
	}
	if (GetAsyncKeyState('I') & 0x8000) {
		GetDocument()->getScene().activeCamera()->moveForward(0.1);
	}	
	if (GetAsyncKeyState('O') & 0x8000) {
		GetDocument()->getScene().activeCamera()->moveBackward(0.1);
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		GetDocument()->stop();
	}

	// update all particle systems
	GetDocument()->step();
	lastUpdate = GetTickCount();

	return 0;
}

void Creplic8View::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/)
{
	if (lHint == 1)
	{
		if (gdiplus)
		{
			Gdiplus::Graphics graphics(m_gdiplusBitmap);
			r8::Rect rc2(0.0, 0.0, (float)g_width, (float)g_height);
			Gdiplus::SolidBrush brush(Color::Black);
			graphics.FillRectangle(&brush, 0, 0, g_width, g_height);
			r8::RendererGraphics renderer(graphics);
			GetDocument()->getScene().render(renderer, rc2);

			RedrawWindow();
		}
		else
		{
			r8::RendererBitmap renderer(pbb, g_width, g_height);
			r8::Rect rc2(0.0, 0.0, (float)g_width, (float)g_height);
			memset(pbb, 0, g_height * g_width * sizeof(DWORD));
			GetDocument()->getScene().render(renderer, rc2);

			RedrawWindow();
		}
	}
}
