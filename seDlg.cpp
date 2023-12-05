// seDlg.cpp : implementation file
//

#include "stdafx.h"
#include "se.h"
#include "seDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const double pi = 3.1415926535;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CseDlg dialog




CseDlg::CseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CseDlg::IDD, pParent)
	, mInput1(_T(""))
	, mInput2(_T(""))
	, mInput3(_T(""))
	, mInput4(_T(""))
	, mOutput1(_T(""))
	, mOutput2(_T(""))
	, mOutput3(_T(""))
	, mOutput4(_T(""))
	, mCaption(FALSE)
	, mPercentage(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mInput1);
	DDX_Text(pDX, IDC_EDIT2, mInput2);
	DDX_Text(pDX, IDC_EDIT3, mInput3);
	DDX_Text(pDX, IDC_EDIT4, mInput4);
	DDX_Text(pDX, IDC_OUTPUT1, mOutput1);
	DDX_Text(pDX, IDC_OUTPUT2, mOutput2);
	DDX_Text(pDX, IDC_OUTPUT3, mOutput3);
	DDX_Text(pDX, IDC_OUTPUT4, mOutput4);
	DDX_Check(pDX, IDC_CAPTION, mCaption);
	DDX_Check(pDX, IDC_PERCENTAGE, mPercentage);
}

BEGIN_MESSAGE_MAP(CseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CseDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_COLOR1, &CseDlg::OnStnClickedColor1)
	ON_STN_CLICKED(IDC_COLOR2, &CseDlg::OnStnClickedColor2)
	ON_STN_CLICKED(IDC_COLOR3, &CseDlg::OnStnClickedColor3)
	ON_STN_CLICKED(IDC_COLOR4, &CseDlg::OnStnClickedColor4)
END_MESSAGE_MAP()


// CseDlg message handlers

BOOL CseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	//pie Æ²
	GetDlgItem(IDC_VIEW)->GetWindowRect(&rectView);
		ScreenToClient(&rectView);
	
	//RGB ¼±ÅÃ
	GetDlgItem(IDC_COLOR1)->GetWindowRect(&rectColor1);
		ScreenToClient(&rectColor1);
	GetDlgItem(IDC_COLOR2)->GetWindowRect(&rectColor2);
		ScreenToClient(&rectColor2);
	GetDlgItem(IDC_COLOR3)->GetWindowRect(&rectColor3);
		ScreenToClient(&rectColor3);
	GetDlgItem(IDC_COLOR4)->GetWindowRect(&rectColor4);
		ScreenToClient(&rectColor4);

	x[0] = rectView.CenterPoint().x;
	y[0] = rectView.CenterPoint().y;
	init_x = rectView.CenterPoint().x;
	init_y = rectView.CenterPoint().y;
	width = rectView.Width() / 2.0;
	height = rectView.Height() / 2.0;
	InputValue[0] = 0;
	InputValue[1] = 0;
	InputValue[2] = 0;
	InputValue[3] = 0;
	PiDraw=false;
	percent =_T("%");
	pieColor[0] = RGB(255, 0, 0);
	pieColor[1] = RGB(0, 255, 0);
	pieColor[2] = RGB(0, 0, 255);
	pieColor[3] = RGB(200, 50,200);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}



	CClientDC dc(this);
	CPen pen2, pen1;
	pen1.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	pen2.CreatePen(PS_SOLID, 2,RGB(0,0,0));


	CBrush brush[4];
	brush[0].CreateSolidBrush(pieColor[0]);
	brush[1].CreateSolidBrush(pieColor[1]);
	brush[2].CreateSolidBrush(pieColor[2]);
	brush[3].CreateSolidBrush(pieColor[3]);

	dc.SelectObject(&brush[0]);
	dc.SetBkMode(TRANSPARENT);

	dc.SelectObject(&pen1);
	//intit color select
	dc.SelectObject(&brush[0]);		
	dc.Rectangle(&rectColor1);
	dc.SelectObject(&brush[1]);
	dc.Rectangle(&rectColor2);
	dc.SelectObject(&brush[2]);	
	dc.Rectangle(&rectColor3);
	dc.SelectObject(&brush[3]);
	dc.Rectangle(&rectColor4);
	
	dc.SelectObject(&pen2);
	if (PiDraw)
	{	
		if(InputValue[0])
		{
			dc.SelectObject(&brush[0]);
			dc.Ellipse(&rectView);
		}

		if(InputValue[1])
		{
			dc.SelectObject(&brush[1]);
			dc.Pie(rectView.TopLeft().x,rectView.TopLeft().y,rectView.BottomRight().x,rectView.BottomRight().y,init_x,init_y,x[0], y[0]);
		}

		if(InputValue[2])
		{
			dc.SelectObject(&brush[2]);
			dc.Pie(rectView.TopLeft().x,rectView.TopLeft().y,rectView.BottomRight().x,rectView.BottomRight().y,init_x,init_y,x[1], y[1]);
		}

		if(InputValue[3])
		{
			dc.SelectObject(&brush[3]);
			dc.Pie(rectView.TopLeft().x,rectView.TopLeft().y,rectView.BottomRight().x,rectView.BottomRight().y,init_x,init_y,x[2], y[2]);
		}

		//Ä¸¼Ç
		if(InputValue[0] && mCaption)
		{
			dc.TextOut(text_x[0],text_y[0], _T("¸¶¶óÅÁ")); // 
		}

		if(InputValue[1] && mCaption)
		{
			dc.TextOut(text_x[1],text_y[1], _T("ÁöÇÏÃ¶")); //
		}
		
		if(InputValue[2] && mCaption)
		{
			dc.TextOut(text_x[2],text_y[2], _T("°¡½ººñ")); //
		}

		if(InputValue[3] && mCaption)
		{
			dc.TextOut(text_x[3],text_y[3], _T("º´¿ø")); //
		}
		
		//°ª
		if (mCaption)
		{
			if (InputValue[0] && mPercentage)
			{	
				temp.Format(_T("%.1f"),avr[0]);
				dc.TextOutW(text_x[0], text_y[0]+15, temp + percent);
			}
			
			if (InputValue[1] && mPercentage)
			{
				temp.Format(_T("%.1f"),avr[1]);
				dc.TextOutW(text_x[1],text_y[1]+15, temp + percent);
			}

			if (InputValue[2] && mPercentage)
			{
				temp.Format(_T("%.1f"),avr[2]);
				dc.TextOutW(text_x[2],text_y[2]+15, temp + percent);
			}

			if (InputValue[3] && mPercentage)
			{
				temp.Format(_T("%.1f"),avr[3]);
				dc.TextOutW(text_x[3],text_y[3]+15, temp + percent);
			}
		}
		else
		{
			if (InputValue[0] && mPercentage)
			{	
				temp.Format(_T("%.1f"),avr[0]);
				dc.TextOutW(text_x[0], text_y[0], temp + percent);
			}
			
			if (InputValue[1] && mPercentage)
			{
				temp.Format(_T("%.1f"),avr[1]);
				dc.TextOutW(text_x[1],text_y[1], temp + percent);
			}

			if (InputValue[2] && mPercentage)
			{
				temp.Format(_T("%.1f"),avr[2]);
				dc.TextOutW(text_x[2],text_y[2], temp + percent);
			}

			if (InputValue[3] && mPercentage)
			{
				temp.Format(_T("%.1f"),avr[3]);
				dc.TextOutW(text_x[3],text_y[3], temp + percent);
			}
		}

		PiDraw=false;
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CseDlg::OnBnClickedButton1()
{
	int TotalSum;
	int i;
	UpdateData(1);
	InputValue[0] = _ttoi(mInput1);
	InputValue[1] = _ttoi(mInput2);
	InputValue[2] = _ttoi(mInput3);
	InputValue[3] = _ttoi(mInput4);

	TotalSum = InputValue[0] + InputValue[1] + InputValue[2] + InputValue[3];
	if (TotalSum)
	{	
		for (i = 0 ; i < 4;i++)
		{
			avr[i] = (static_cast<float>(InputValue[i]) / TotalSum) * 100;
		}
		
		temp.Format(_T("%.1f"),avr[0]);
		mOutput1 = temp + percent;
		temp.Format(_T("%.1f"),avr[1]);
		mOutput2 = temp + percent;
		temp.Format(_T("%.1f"),avr[2]);
		mOutput3 = temp + percent;
		temp.Format(_T("%.1f"),avr[3]);
		mOutput4 = temp + percent;
		UpdateData(0);

		//pi ÁÂÇ¥
		x[0] = static_cast<int>(width * cos((360 * avr[0] / 100)*pi/180)) + rectView.CenterPoint().x; //»ï°¢ÇÔ¼ö Â¯³ª.. ¤Ð¤Ð
		y[0] = static_cast<int>(height * sin((360 * avr[0] / 100)*pi/180)) + rectView.CenterPoint().y;

		x[1] = static_cast<int>(width * cos((360 * (avr[0]+avr[1]) / 100)*pi/180)) + rectView.CenterPoint().x;
		y[1] = static_cast<int>(height * sin((360 * (avr[0]+avr[1]) / 100)*pi/180)) + rectView.CenterPoint().y;

		x[2] = static_cast<int>(width * cos((360 * (avr[0]+avr[1]+avr[2]) / 100)*pi/180)) + rectView.CenterPoint().x;
		y[2] = static_cast<int>(height * sin((360 * (avr[0]+avr[1]+avr[2]) / 100)*pi/180)) + rectView.CenterPoint().y;

		x[3] = static_cast<int>(width * cos((360 * (avr[0]+avr[1]+avr[2]+avr[3]) / 100)*pi/180)) + rectView.CenterPoint().x;
		y[3] = static_cast<int>(height * sin((360 * (avr[0]+avr[1]+avr[2]+avr[3]) / 100)*pi/180)) + rectView.CenterPoint().y;

		init_x = rectView.CenterPoint().x + rectView.Width() / 2;

		PiDraw=true;
		
		if (mPercentage || mCaption)
		{
			//text ÁÂÇ¥
			text_x[0] = static_cast<int>(width/2 * cos((360 * avr[0]/2 / 100)*pi/180)) + rectView.CenterPoint().x;
			text_y[0] = static_cast<int>(height/2 * sin((360 * avr[0]/2 / 100)*pi/180)) + rectView.CenterPoint().y;
			
			text_x[1] = static_cast<int>(width/2 * cos((360 * (avr[0]+avr[1]/2) / 100)*pi/180)) + rectView.CenterPoint().x;
			text_y[1] = static_cast<int>(height/2 * sin((360 * (avr[0]+avr[1]/2) / 100)*pi/180)) + rectView.CenterPoint().y;
			
			text_x[2] = static_cast<int>(width/2 * cos((360 * (avr[0]+avr[1]+avr[2]/2) / 100)*pi/180)) + rectView.CenterPoint().x;
			text_y[2] = static_cast<int>(height/2 * sin((360 * (avr[0]+avr[1]+avr[2]/2) / 100)*pi/180)) + rectView.CenterPoint().y;
			
			text_x[3] = static_cast<int>(width/2 * cos((360 * (avr[0]+avr[1]+avr[2]+avr[3]/2) / 100)*pi/180)) + rectView.CenterPoint().x;
			text_y[3] = static_cast<int>(height/2 * sin((360 * (avr[0]+avr[1]+avr[2]+avr[3]/2) / 100)*pi/180)) + rectView.CenterPoint().y;
		}
	}

	OnPaint();
}


void CseDlg::OnStnClickedColor1()
{
	CColorDialog dlg(pieColor[0]);
	if(dlg.DoModal() == IDOK)
	{
		pieColor[0] = dlg.GetColor();
		PiDraw=true;
		Invalidate();
	}		
}

void CseDlg::OnStnClickedColor2()
{
	CColorDialog dlg(pieColor[1]);
	if(dlg.DoModal() == IDOK)
	{
		pieColor[1] = dlg.GetColor();
		PiDraw=true;
		Invalidate();
	}
}

void CseDlg::OnStnClickedColor3()
{
	CColorDialog dlg(pieColor[2]);
	if(dlg.DoModal() == IDOK)
	{
		pieColor[2] = dlg.GetColor();
		PiDraw=true;
		Invalidate();
	}	
}

void CseDlg::OnStnClickedColor4()
{
	CColorDialog dlg(pieColor[3]);
	if(dlg.DoModal() == IDOK)
	{
		pieColor[3] = dlg.GetColor();
		PiDraw=true;
		Invalidate();
	}
}