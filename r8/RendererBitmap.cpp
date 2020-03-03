#include <afxwin.h>
#include "RendererBitmap.h"

namespace r8 {

RendererBitmap::RendererBitmap(void)
{
}

RendererBitmap::~RendererBitmap(void)
{
}

void RendererBitmap::drawPoint(int x, int y, Colour& colour)
{
	if (y >= 0 && y < m_height && x >= 0 && x < m_width) {
		m_bitmap[y * m_pitch + x] = colour.m_col.c;
	}
}

void RendererBitmap::drawLine(int x, int y, int x2, int y2, Colour& colour)
{
	int dx, dy, long_d, short_d;
	int d, add_dh, add_dl;
	int inc_xh, inc_yh, inc_xl, inc_yl;
	int i;
	// TODO: Why haven't I introduced colour now instead of waiting until later?!
	DWORD pixel = colour.m_col.c;

	dx = x2 - x;
	dy = y2 - y;

	if (dx < 0) {
		dx = -dx;
		inc_xh = -1;
		inc_xl = -1;
	} else {
		inc_xh = 1;
		inc_xl = 1;
	}

	if (dy < 0) {
		dy = -dy;
		inc_yh = -1;
		inc_yl = -1;
	} else {
		inc_yh = 1;
		inc_yl = 1;
	}

	if (dx > dy) {
		long_d = dx;
		short_d = dy;
		inc_yl = 0;
	} else {
		long_d = dy;
		short_d = dx;
		inc_xl = 0;
	}

	d = 2 * short_d - long_d;
	add_dl = 2 * short_d;
	add_dh = 2 * short_d - 2 * long_d;

	for (i = 0; i <= long_d; i++) {
		if (y >= 0 && y < m_height && x >= 0 && x < m_width) {
			m_bitmap[y * m_pitch + x] = pixel;
		}

		if (d >= 0) {
			x += inc_xh;
			y += inc_yh;
			d += add_dh;
		} else {
			x += inc_xl;
			y += inc_yl;
			d += add_dl;
		}
	}
}

void RendererBitmap::drawPolygon(Point* pts, int n, Colour& colour)
{
	if (m_renderMode == Wireframe) {
		for (int i = 0; i < n; i++) {
			drawLine(pts[i].x(), pts[i].y(), pts[(i + 1) % n].x(), pts[(i + 1) % n].y(), colour);
		}
	}
}

}