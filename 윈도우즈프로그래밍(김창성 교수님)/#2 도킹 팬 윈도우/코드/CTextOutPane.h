#pragma once
#include "CHobbyCtrl.h"

// CTextOutPane

class CTextOutPane : public CDockablePane
{
	DECLARE_DYNAMIC(CTextOutPane)

public:
	CTextOutPane();
	virtual ~CTextOutPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CHobbyCtrl m_ctrlTextOut;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


