
// CashBook2Dlg.h: 헤더 파일
//

#pragma once


// CCashBook2Dlg 대화 상자
class CCashBook2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CCashBook2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CseDlg(CWnd* pParent = NULL);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CASHBOOK2_DIALOG };
	enum { IDD = IDD_SE_DIALOG };
#endif
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_cashbook;
	CDateTimeCtrl m_date;
	CComboBox m_cate;
	CString m_com;
	CString m_amo;
	CString m_memo;
	int m_income;

	float avr[4];
	CRect rectView;
	CRect rectColor1, rectColor2, rectColor3, rectColor4;
	int InputValue[4];
	int x[4], y[4];
	int text_x[4], text_y[4];
	int init_x, init_y;
	double width, height;
	bool PiDraw;
	COLORREF pieColor[4];
	CString percent, temp;

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();

	afx_msg void OnBnClickedButton1();
	CString mInput1;
	CString mInput2;
	CString mInput3;
	CString mInput4;
	CString mOutput1;:
	CString mOutput2;
	CString mOutput3;
	CString mOutput4;
	BOOL mCaption;
	BOOL mPercentage;

	afx_msg void OnStnClickedColor1();
	afx_msg void OnStnClickedColor2();:
	afx_msg void OnStnClickedColor3();
	afx_msg void OnStnClickedColor4();

};
