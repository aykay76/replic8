// replic8Doc.cpp : implementation of the Creplic8Doc class
//

#include "stdafx.h"
#include "replic8.h"

#include "r8/r8_base.h"
#include "replic8Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Creplic8Doc

IMPLEMENT_DYNCREATE(Creplic8Doc, CDocument)

BEGIN_MESSAGE_MAP(Creplic8Doc, CDocument)
END_MESSAGE_MAP()


// Creplic8Doc construction/destruction

Creplic8Doc::Creplic8Doc()
	: m_running(true)
{
	// TODO: add one-time construction code here
	m_dwLastStep = GetTickCount();
}

Creplic8Doc::~Creplic8Doc()
{
}

BOOL Creplic8Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Creplic8Doc serialization

void Creplic8Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Creplic8Doc diagnostics

#ifdef _DEBUG
void Creplic8Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Creplic8Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Creplic8Doc commands

void Creplic8Doc::step()
{
	if (m_running == false) return;

	DWORD dwNow = GetTickCount();
	double timestep = (dwNow - m_dwLastStep) / 1000.0;

	if (timestep > 0)
	{
		m_scene.update(0.01);
		m_dwLastStep = dwNow;
	}

	UpdateAllViews(NULL, 1);
}