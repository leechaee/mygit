// seDlg.h : header file
//

#pragma once


// CseDlg dialog
class CseDlg : public CDialog
{
// Construction
public:
	CseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
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
public:
	afx_msg void OnBnClickedButton1();
public:
	CString mInput1;
public:
	CString mInput2;
public:
	CString mInput3;
public:
	CString mInput4;
public:
	CString mOutput1;
public:
	CString mOutput2;
public:
	CString mOutput3;
public:
	CString mOutput4;
public:
	BOOL mCaption;
public:
	BOOL mPercentage;


public:
	afx_msg void OnStnClickedColor1();
public:
	afx_msg void OnStnClickedColor2();
public:
	afx_msg void OnStnClickedColor3();
public:
	afx_msg void OnStnClickedColor4();
};
