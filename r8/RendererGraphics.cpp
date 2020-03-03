#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "RendererGraphics.h"

namespace r8 {

RendererGraphics::RendererGraphics(Gdiplus::Graphics& graphics)
	: m_graphics(graphics)
	, pen(Gdiplus::Color::White)
{
	
}

RendererGraphics::~RendererGraphics(void)
{
}

void RendererGraphics::drawPoint(int x, int y, Colour& colour)
{
}

void RendererGraphics::drawLine(int x, int y, int x2, int y2, Colour& colour)
{
}

void RendererGraphics::drawPolygon(Point* pts, int n, Colour& colour)
{
	m_graphics.DrawLine(&pen, pts[0].x(), pts[0].y(), pts[1].x(), pts[1].y());
	m_graphics.DrawLine(&pen, pts[1].x(), pts[1].y(), pts[2].x(), pts[2].y());
	m_graphics.DrawLine(&pen, pts[2].x(), pts[2].y(), pts[0].x(), pts[0].y());
}

}