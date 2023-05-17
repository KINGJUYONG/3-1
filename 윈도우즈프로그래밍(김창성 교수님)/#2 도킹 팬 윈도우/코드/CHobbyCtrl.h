#pragma once
#include "afxdialogex.h"


// CHobbyCtrl 대화 상자

class CHobbyCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CHobbyCtrl)

public:
	CHobbyCtrl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHobbyCtrl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEXTOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listHobby; // 선언된 변수들과 여러 함수들입니다.
	CComboBox m_cbSex;
	CString m_strName;
	virtual BOOL OnInitDialog();
	bool m_bSex = true;
	bool m_bChecked[3] = {false, false, false};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCbnSelchangeComboSex();
	afx_msg void OnLbnSelchangeListHobby();
	afx_msg void OnBnClickedCheckReading();
	afx_msg void OnBnClickedCheckFishing();
	afx_msg void OnBnClickedCheckSports();
	afx_msg void OnBnClickedRadioMale();
	afx_msg void OnBnClickedRadioFemale();
	afx_msg void OnBnClickedButtonResult();
};
