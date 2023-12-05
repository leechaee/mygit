
// CashBook2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CashBook2.h"
#include "CashBook2Dlg.h"
#include "afxdialogex.h"
#include <cstring>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCashBook2Dlg 대화 상자



CCashBook2Dlg::CCashBook2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CASHBOOK2_DIALOG, pParent)
	, m_memo(_T(""))
	, m_com(_T(""))
	, m_amo(_T(""))
	, m_income(0)
	//, m_com(_T(""))
	//, m_com(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCashBook2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CASHBOOK, m_cashbook);
	DDX_Text(pDX, IDC_EDIT_MEMO, m_memo);
	DDX_Text(pDX, IDC_EDIT_COM, m_com);
	//  DDX_Control(pDX, IDC_EDIT_AMO, m_amo);
	DDX_Text(pDX, IDC_EDIT_AMO, m_amo);
	DDX_Radio(pDX, IDC_RADIO_INCOME, m_income);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);
	//DDX_Text(pDX, IDC_EDIT_CONT, m_com);
	//  DDX_Control(pDX, IDC_COMBO, m_ctlcombo);
	DDX_Control(pDX, IDC_COMBO, m_cate);
	DDX_Text(pDX, IDC_EDIT_CONT, m_com);
}

BEGIN_MESSAGE_MAP(CCashBook2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCashBook2Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CCashBook2Dlg::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CCashBook2Dlg 메시지 처리기

BOOL CCashBook2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CRect r;
	::GetClientRect(m_cashbook.m_hWnd, r);
	int cx = r.right - r.left;
	m_cashbook.InsertColumn(1, _T("날짜"), LVCFMT_CENTER, int (cx * 0.2));
	m_cashbook.InsertColumn(2, _T("분류"), LVCFMT_CENTER, int(cx * 0.1));
	m_cashbook.InsertColumn(3, _T("내역"), LVCFMT_CENTER, int(cx * 0.15));
	m_cashbook.InsertColumn(4, _T("수입"), LVCFMT_CENTER, int(cx * 0.15));
	m_cashbook.InsertColumn(5, _T("지출"), LVCFMT_CENTER, int(cx * 0.15));
	m_cashbook.InsertColumn(6, _T("메모"), LVCFMT_CENTER, int(cx * 0.3));

	//분류 콤보박스에 추가되는 리스트
	m_cate.AddString(_T("식비"));
	m_cate.AddString(_T("통신비"));
	m_cate.AddString(_T("주거비"));
	m_cate.AddString(_T("교통비"));
	m_cate.AddString(_T("생필품"));
	m_cate.AddString(_T("월급"));
	m_cate.AddString(_T("용돈"));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCashBook2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCashBook2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCashBook2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCashBook2Dlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int nItemNum = m_cashbook.GetItemCount();
	CString com = m_com; //
	CString str;
	CString curSelName;
	m_cate.GetWindowTextW(curSelName);
	CString amo = m_amo;
	CString memo = m_memo;
	CString date;
	CTime time;
	int iIndex = 0; 
	CString strItemText = _T("");
	m_date.GetTime(time);
	date = time.Format("%Y %m %d");

	
	m_cashbook.InsertItem(nItemNum, date); //날짜
	m_cashbook.SetItemText(nItemNum, 1, curSelName); //분류
	m_cashbook.SetItemText(nItemNum, 2, com); //내역

	if (m_income == 0) {
		m_cashbook.SetItemText(nItemNum, 3, amo); //수입
	}
	else {
		m_cashbook.SetItemText(nItemNum, 4, amo); //지출
	}
	m_cashbook.SetItemText(nItemNum, 5, memo); //메모

	m_com = _T(" ");
	m_amo = _T(" ");
	m_memo = _T(" ");
	UpdateData(FALSE);

}


void CCashBook2Dlg::OnBnClickedButtonDel(){
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
/*	if (m_nSelectedIndex != -1) {
		m_lstStudent.DeleteItem(m_nSelectedIndex);//해당 열번호를 삭제함    
		for (int i = m_nSelectedIndex - 1; i < m_lstStudent.GetItemCount(); i++);//삭제된 이후 남은 데이터들의 순번을 변경해줌 
			CString strIndex;
			strIndex.Format(_T("%d"), i + 1);
			m_lstStudent.SetItemText(i,0,strIndex);
			m_CdeleteBt.EnableWindow(FALSE);
			m_CModifybt.EnableWindow(FALSE);
			m_strDept.Empty();
			m_strID.Empty();
			m_strName.Empty();
		}
	}else{
		AfxMessageBox(_T("삭제할 아이템을 선택하세요 ")); 
	}*/
	int nMark = m_cashbook.GetSelectionMark();

	if (nMark >= 0)
		m_cashbook.DeleteItem(nMark);
	else
		AfxMessageBox(_T("삭제할 아이템을 선택하세요 "));

	/*int count = m_cashbook.GetItemCount(); 

	for (int i = count; i >= 0; i--) {

		if (m_cashbook.GetItemState(i, LVIS_SELECTED) != 0) {

			m_cashbook.DeleteItem(i);

		}
	}*/

}

