
// DDView.cpp: CDDView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DD.h"
#endif

#include "DDDoc.h"
#include "DDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDDView

IMPLEMENT_DYNCREATE(CDDView, CView)

BEGIN_MESSAGE_MAP(CDDView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDDView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CDDView 생성/소멸

CDDView::CDDView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	//  m_strName = _T("");
	//  m_strSex = _T("");
	//  m_strHobby = _T("");
	m_strName = _T("");
	m_strSex = _T("");
	m_strHobby[3] = _T("");
	m_strOutput = _T("");
	x = 0;
	y = 0;
}

CDDView::~CDDView()
{
}

BOOL CDDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDDView 그리기

void CDDView::OnDraw(CDC* pDC)
{
	CDDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString Namesc = _T("이름 : "); // 이름과 성별, 취미를 표시하기 위한 문자열들입니다. 아래에서 문자열 join으로 사용됩니다.
	CString Sexsc = _T("성별 : ");
	CString Hobbysc = _T("내가 선택한 취미 : ");
	x = 20; y = 20; // 기본 텍스트 출력 위치 20, 20을 설정합니다.
	pDC->TextOut(x, y, (Namesc + m_strName)); // 이름을 출력합니다.
	y += 30; // 밑으로 30만큼 띄워서 다음 요소를 출력하기 위해 사용하였습니다.
	pDC->TextOut(x, y, (Sexsc + m_strSex)); // 성별을 출력합니다.
	y += 30;
	pDC->TextOut(x, y, (Hobbysc)); // 성별을 출력합니다.
	x += 135;
	for (int i = 0; i < 3; i++) {
		if (m_strHobby[i] == "낚시" || m_strHobby[i] == "독서" || m_strHobby[i] == "운동") { // 선택된 항목만 저장되어있는 m_strHobby의 요소들(해당되는 요소들)을 출력합니다.
			pDC->TextOut(x, y, m_strHobby[i]);
			x += 40; // 한 번 출력할 때마다 40씩 띄워줍니다.
		}
	}
}


// CDDView 인쇄


void CDDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CDDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDDView 진단

#ifdef _DEBUG
void CDDView::AssertValid() const
{
	CView::AssertValid();
}

void CDDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDDDoc* CDDView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDDDoc)));
	return (CDDDoc*)m_pDocument;
}
#endif //_DEBUG


// CDDView 메시지 처리기