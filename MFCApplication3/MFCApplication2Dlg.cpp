﻿
// MFCApplication2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"

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


// CMFCApplication2Dlg 대화 상자



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, m_nx1(500)
	, m_ny1(500)
	, m_nx2(800)
	, m_ny2(800)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_nx1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_ny1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nx2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_ny2);
	DDX_Control(pDX, IDC_PICTURE, m_pictureControl);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_X1, &CMFCApplication2Dlg::OnEnChangeEditX1)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMFCApplication2Dlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CMFCApplication2Dlg::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCApplication2Dlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 메시지 처리기

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu *pSysMenu = GetSystemMenu(FALSE);
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
	EnsureImageFolder();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
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
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnEnChangeEditX1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication2Dlg::OnBnClickedButtonDraw()
{
	// 화면 초기화
	m_pictureControl.Invalidate();
	m_pictureControl.UpdateWindow();

	// 픽처 컨트롤 클라이언트 영역 가져오기
	CRect rect;
	m_pictureControl.GetClientRect(&rect);

	// 중심 좌표 계산
	int centerX = rect.Width() / 2;
	int centerY = rect.Height() / 2;

	// 랜덤 반지름 생성
	int radius = rand() % 91 + 10;

	// DC 설정 및 원 그리기
	CClientDC dc(&m_pictureControl);
	CBrush brush(RGB(125, 125, 125));
	CBrush *pOldBrush = dc.SelectObject(&brush);
	dc.Ellipse(centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	dc.SelectObject(pOldBrush);
}

void CMFCApplication2Dlg::OnBnClickedButtonOpen()
{
	CFileDialog dlg(TRUE, _T("jpg"), NULL, OFN_FILEMUSTEXIST, _T("Image Files|*.bmp;*.jpg;*.jpeg;*.png|All Files|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		CImage image;
		if (FAILED(image.Load(filePath)))
		{
			AfxMessageBox(_T("이미지 로드 실패!"));
			return;
		}

		CRect rect;
		m_pictureControl.GetClientRect(&rect);

		CClientDC dc(&m_pictureControl);
		image.Draw(dc.m_hDC, 0, 0, rect.Width(), rect.Height());
	}
}

void CMFCApplication2Dlg::OnBnClickedButtonAction()
{
	AfxBeginThread(CMFCApplication2Dlg::MoveCircleThread, this);
}

UINT CMFCApplication2Dlg::MoveCircleThread(LPVOID pParam)
{
	CMFCApplication2Dlg *pDlg = static_cast<CMFCApplication2Dlg *>(pParam);

	CRect rect;
	pDlg->m_pictureControl.GetClientRect(&rect);
	int centerX = rect.Width() / 2;
	int centerY = rect.Height() / 2;

	CClientDC dc(&pDlg->m_pictureControl);
	CBrush brush(RGB(255, 0, 0));
	CBrush *pOldBrush = dc.SelectObject(&brush);

	for (int i = 0; i < 10; ++i)
	{
		dc.Ellipse(centerX - i * 5, centerY - i * 5, centerX + i * 5, centerY + i * 5);
		Sleep(100);
	}
	dc.SelectObject(pOldBrush);
	return 0;
}

void CMFCApplication2Dlg::EnsureImageFolder()
{
	CString folderPath = _T("image");
	if (!PathIsDirectory(folderPath))
	{
		CreateDirectory(folderPath, NULL);
	}
}