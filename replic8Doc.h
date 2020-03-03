// replic8Doc.h : interface of the Creplic8Doc class
//


#pragma once

class Creplic8Doc : public CDocument
{
protected: // create from serialization only
	Creplic8Doc();
	DECLARE_DYNCREATE(Creplic8Doc)

// Attributes
public:
	r8::Scene& getScene() { return m_scene; }
	bool running() { return m_running; }
	void start() { m_running = true; m_dwLastStep = GetTickCount(); }
	void stop() { m_running = false; }
	void step();

protected:
	r8::Scene m_scene;
	bool m_running;
	DWORD m_dwLastStep;

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Creplic8Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


