
// STOPWATCHView.h: CSTOPWATCHView 클래스의 인터페이스
//

#pragma once


class CSTOPWATCHView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSTOPWATCHView();
	DECLARE_DYNCREATE(CSTOPWATCHView)

// 특성입니다.
public:
	CSTOPWATCHDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSTOPWATCHView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	CString STOPWATCH;
	CString rec[40];

	int count;
	int sec;
	int ms;
	int minute;
	bool STOPWATCHRUN;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // STOPWATCHView.cpp의 디버그 버전
inline CSTOPWATCHDoc* CSTOPWATCHView::GetDocument() const
   { return reinterpret_cast<CSTOPWATCHDoc*>(m_pDocument); }
#endif

