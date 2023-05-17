// DDView.h: CDDView 클래스의 인터페이스
#include "DDDoc.h"
#pragma once


class CDDView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDDView() noexcept;
	DECLARE_DYNCREATE(CDDView)

// 특성입니다.
public:
	CDDDoc* GetDocument() const;

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
	virtual ~CDDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strSex;
	CString m_strHobby[3] = {0, 0, 0};
	CString m_strOutput;
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int x;
	int y;
};

#ifndef _DEBUG  // DDView.cpp의 디버그 버전
inline CDDDoc* CDDView::GetDocument() const
   { return reinterpret_cast<CDDDoc*>(m_pDocument); }
#endif

