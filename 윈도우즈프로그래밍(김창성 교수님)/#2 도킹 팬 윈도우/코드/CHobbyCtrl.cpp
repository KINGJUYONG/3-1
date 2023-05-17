// CHobbyCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "DD.h"
#include "afxdialogex.h"
#include "CHobbyCtrl.h"
#include "MainFrm.h"
#include "DDView.h" // DDView의 변수를 사용하기 위해 가져왔습니다.

// CHobbyCtrl 대화 상자

IMPLEMENT_DYNAMIC(CHobbyCtrl, CDialogEx)

CHobbyCtrl::CHobbyCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEXTOUT, pParent)
	, m_strName(_T(""))
{

}

CHobbyCtrl::~CHobbyCtrl()
{
}

void CHobbyCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOBBY, m_listHobby);
	DDX_Control(pDX, IDC_COMBO_SEX, m_cbSex);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CHobbyCtrl, CDialogEx)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CHobbyCtrl::OnCbnSelchangeComboSex)
	ON_LBN_SELCHANGE(IDC_LIST_HOBBY, &CHobbyCtrl::OnLbnSelchangeListHobby)
	ON_BN_CLICKED(IDC_CHECK_READING, &CHobbyCtrl::OnBnClickedCheckReading)
	ON_BN_CLICKED(IDC_CHECK_FISHING, &CHobbyCtrl::OnBnClickedCheckFishing)
	ON_BN_CLICKED(IDC_CHECK_SPORTS, &CHobbyCtrl::OnBnClickedCheckSports)
	ON_BN_CLICKED(IDC_RADIO_MALE, &CHobbyCtrl::OnBnClickedRadioMale)
	ON_BN_CLICKED(IDC_RADIO_FEMALE, &CHobbyCtrl::OnBnClickedRadioFemale)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CHobbyCtrl::OnBnClickedButtonResult)
END_MESSAGE_MAP()


// CHobbyCtrl 메시지 처리기


BOOL CHobbyCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_listHobby.AddString(L"독서"); // 리스트박스에 3개의 요소를 설정해줍니다.
	m_listHobby.AddString(L"낚시");
	m_listHobby.AddString(L"운동");
	m_cbSex.SetCurSel(0); // 콤보박스에서 남자를 default값으로 설정해주고
	m_listHobby.SetSel(0, 1); // 리스트박스 내의 3개 요소들을 모두 선택됨으로 설정합니다.
	m_listHobby.SetSel(1, 1);
	m_listHobby.SetSel(2, 1);


	((CButton*)GetDlgItem(IDC_RADIO_MALE))->SetCheck(1); // 라디오버튼을 남자로
	((CButton*)GetDlgItem(IDC_CHECK_READING))->SetCheck(1); // 체크박스를 모두 선택됨으로 설정해줍니다.
	((CButton*)GetDlgItem(IDC_CHECK_FISHING))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_SPORTS))->SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


int CHobbyCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CHobbyCtrl::OnCbnSelchangeComboSex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (CBN_SELCHANGE) { // 콤보박스에 변동사항이 있을시
		if (m_cbSex.GetCurSel() == TRUE) { // GetCurSel의 값이 1일때, 즉 여자일때
			((CButton*)GetDlgItem(IDC_RADIO_MALE))->SetCheck(!m_bSex); // 남자의 선택을 해제하고
			((CButton*)GetDlgItem(IDC_RADIO_FEMALE))->SetCheck(m_bSex); // 여자로 선택합니다.
		}
		else if (m_cbSex.GetCurSel() == FALSE) { // GetCurSel의 값이 0일때, 즉 남자일때
			((CButton*)GetDlgItem(IDC_RADIO_FEMALE))->SetCheck(!m_bSex); // 여자를 해제하고 남자를 설정합니다.
			((CButton*)GetDlgItem(IDC_RADIO_MALE))->SetCheck(m_bSex);
		}
	}
}

void CHobbyCtrl::OnBnClickedRadioMale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (BN_CLICKED == 0) { // 남성을 표시할 라디오버튼입니다. 클릭시 cbSex, 콤보박스의 성별을 남성으로 바꿉니다.
		m_cbSex.SetCurSel(0);
	}
}


void CHobbyCtrl::OnBnClickedRadioFemale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (BN_CLICKED == 0) {
		m_cbSex.SetCurSel(1); // 여성을 표시할 라디오버튼입니다.클릭시 cbSex, 콤보박스의 성별을 여성으로 바꿉니다.
	}
}



void CHobbyCtrl::OnLbnSelchangeListHobby()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (LBN_SELCHANGE) { // 리스트박스에 이벤트 발생시
		if (m_listHobby.GetCurSel() == 0) { // 첫번째 요소인 독서를 선택시
			if (m_bChecked[0] == 0) { // m_bChecked의 0번째가 0이라면
				((CButton*)GetDlgItem(IDC_CHECK_READING))->SetCheck(m_bChecked[0]); // 독서 체크박스를 반대의 경우로 전환합니다.(초기 수행시 true에서 false로)
				m_bChecked[0] = 1; // 이후 m_bChecked[0]을 1로 바꿔주어 다시 수행시 반대의 경우를 표시하도록 합니다.
			}
			else if(m_bChecked[0] == 1) { // m_bChecked[0]이 1이라면, 즉 한 번 수행되어 체크박스가 꺼져있다면
				((CButton*)GetDlgItem(IDC_CHECK_READING))->SetCheck(m_bChecked[0]); // 체크박스를 다시 켜고
				m_bChecked[0] = 0; // m_bChecked[0]는 다시 0으로 설정됩니다.
			}
		}
		else if (m_listHobby.GetCurSel() == 1) { // 아래의 두 경우도 동일한 로직을 사용합니다.
			if (m_bChecked[1] == 0) {
				((CButton*)GetDlgItem(IDC_CHECK_FISHING))->SetCheck(m_bChecked[1]);
				m_bChecked[1] = 1;
			}
			else if (m_bChecked[1] == 1) {
				((CButton*)GetDlgItem(IDC_CHECK_FISHING))->SetCheck(m_bChecked[1]);
				m_bChecked[1] = 0;
			}
		}
		else if (m_listHobby.GetCurSel() == 2) {
			if (m_bChecked[2] == 0) {
				((CButton*)GetDlgItem(IDC_CHECK_SPORTS))->SetCheck(m_bChecked[2]);
				m_bChecked[2] = 1;
			}
			else if (m_bChecked[2] == 1) {
				((CButton*)GetDlgItem(IDC_CHECK_SPORTS))->SetCheck(m_bChecked[2]);
				m_bChecked[2] = 0;
			}
		}
	}
}


void CHobbyCtrl::OnBnClickedCheckReading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(BN_CLICKED == 0) { // 독서 체크박스를 선택시
		m_bChecked[0] = !(m_bChecked[0]); // m_bChecked[0]를 반대의 경우로 전환하고
		m_listHobby.SetSel(0, !m_bChecked[0]); // 리스트박스의 0번째 요소, 즉 독서를 m_bChecked[0](0 or 1)로 설정합니다(위에서 설정한대로)
	}
}


void CHobbyCtrl::OnBnClickedCheckFishing() // 아래의 두 체크박스도 동일한 로직을 사용합니다.
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (BN_CLICKED == 0) {
		m_bChecked[1] = !(m_bChecked[1]);
		m_listHobby.SetSel(1, !m_bChecked[1]);
	}
}


void CHobbyCtrl::OnBnClickedCheckSports()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (BN_CLICKED == 0) {
		m_bChecked[2] = !(m_bChecked[2]);
		m_listHobby.SetSel(2, !m_bChecked[2]);
	}
}


void CHobbyCtrl::OnBnClickedButtonResult() // 결과 출력 버튼입니다.
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd(); // MainFrame과 DDView의 포인터를 설정합니다.
	CDDView* pView = (CDDView*)pFrame->GetActiveView();

	GetDlgItemText(IDC_EDIT_NAME, pView->m_strName); // GetDlgItemText를 사용하여 이름과 성별의 텍스트를 전달하고
	GetDlgItemText(IDC_COMBO_SEX, pView->m_strSex);

	//GetDlgItemText(IDC_LIST_HOBBY, pView->m_strHobby);
	for (int i = 0; i < 3; i++) { // for문 내에서 
		if (m_bChecked[i] == false) { // m_bChecked[i], 리스트박스의 i번째 요소가 false(기본으로 설정된 값이 false고, 기본값으로 선택되어있음)라면, 즉 선택되어있다면
			m_listHobby.GetText(i, pView->m_strHobby[i]); // 해당 요소를 GetText를 사용하여 View클래스의 m_strHobby[i]로 전달해줍니다.
		}
	}

	pView->Invalidate();
}
