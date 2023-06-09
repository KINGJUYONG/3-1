
// CSTOPWATCHView.cpp: CSTOPWATCHView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "STOPWATCH.h"
#endif

#include "STOPWATCHDoc.h"
#include "STOPWATCHView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// STOPWATCHView

IMPLEMENT_DYNCREATE(CSTOPWATCHView, CView)

BEGIN_MESSAGE_MAP(CSTOPWATCHView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CSTOPWATCHView 생성/소멸

CSTOPWATCHView::CSTOPWATCHView()
	: STOPWATCH(_T("00: 00. 00"))
	, STOPWATCHRUN(false)
	, count(0)
	, minute(0)
	, sec(0)
	, ms(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSTOPWATCHView::~CSTOPWATCHView()
{
}

BOOL CSTOPWATCHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSTOPWATCHView 그리기

void CSTOPWATCHView::OnDraw(CDC* pDC)
{
	CSTOPWATCHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CRect rect;
	GetClientRect(&rect);
	
	CClientDC dc(this);

	CFont Time;

	Time.CreateFont(80, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("휴먼엑스포"));

	dc.SelectObject(Time);
	dc.DrawText(STOPWATCH, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	int i = 0;
	for (int k = 0; k < 40; k++)
	{
		pDC->TextOut(100, 100 + i,rec[k]);
		i += 15;
		if (i > 300) {
			i = 0;
		}
	}
}


// CSTOPWATCHView 인쇄

BOOL CSTOPWATCHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSTOPWATCHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSTOPWATCHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSTOPWATCHView 진단

#ifdef _DEBUG
void CSTOPWATCHView::AssertValid() const
{
	CView::AssertValid();
}

void CSTOPWATCHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSTOPWATCHDoc* CSTOPWATCHView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSTOPWATCHDoc)));
	return (CSTOPWATCHDoc*)m_pDocument;
}
#endif //_DEBUG


// CSTOPWATCHView 메시지 처리기


void CSTOPWATCHView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	ms += 1;
	if (ms > 99) {
		sec += 1;
		ms = 0;
	}
	if (sec > 59) {
		minute += 1;
		sec = 0;
	}

	STOPWATCH.Format(_T("%02d: %02d. %02d"), minute, sec, ms);
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CSTOPWATCHView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (STOPWATCHRUN == 0)
	{
		SetTimer(0, 10, NULL);
		STOPWATCHRUN = 1;
	} 
	else if (STOPWATCHRUN == 1)
	{
		KillTimer(0);
		STOPWATCHRUN = 0;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CSTOPWATCHView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SPACE && STOPWATCHRUN == 1)
	{
		if (count >= 30)
		{
			count = 0;
			for (int i = 0; i < 30; i++)
			{
				rec[i].Empty();
			}
		}
		rec[count] = STOPWATCH;
		count += 1;
	}


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSTOPWATCHView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (STOPWATCHRUN == 0)
	{
		if (AfxMessageBox(_T("스톱워치를 초기화 하시겠습니까 ?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			KillTimer(0);
			for (int i = 0; i < 30; i++)
			{
				rec[i].Empty();
			}
			count = 0;
			minute = 0;
			sec = 0;
			ms = 0;
			STOPWATCH.Format(_T("%02d: %02d. %02d"), minute, sec, ms);
			Invalidate();
		}
	}
	if (STOPWATCHRUN == 1)
	{
		if (AfxMessageBox(_T("작동 중에는 스톱워치를 초기화 시킬 수 없습니다."), MB_OK | MB_ICONWARNING) == IDYES)
		{

		}
	}
	

	CView::OnRButtonDown(nFlags, point);
}