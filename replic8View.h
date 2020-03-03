// replic8View.h : interface of the Creplic8View class
//


#pragma once

#include <gdiplus.h>

class Creplic8View : public CView
{
protected: // create from serialization only
	Creplic8View();
	DECLARE_DYNCREATE(Creplic8View)

// Attributes
public:
	Creplic8Doc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Creplic8View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CBitmap* m_pBitmap;
	Gdiplus::Bitmap* m_gdiplusBitmap;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnUser1(WPARAM wParam, LPARAM lParam);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in replic8View.cpp
inline Creplic8Doc* Creplic8View::GetDocument() const
   { return reinterpret_cast<Creplic8Doc*>(m_pDocument); }
#endif

