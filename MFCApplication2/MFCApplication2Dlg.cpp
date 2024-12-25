
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
	// Action 스레드 중지
	m_eventStopThread.SetEvent();

	// 새로운 작업 시작
	int x1 = GetDlgItemInt(IDC_EDIT_X1);
	int y1 = GetDlgItemInt(IDC_EDIT_Y1);

	int radius = rand() % 91 + 10;

	CClientDC dc(this);
	CBrush brush(RGB(255, 0, 0));
	dc.SelectObject(&brush);
	dc.Ellipse(x1 - radius, y1 - radius, x1 + radius, y1 + radius);
}

void CMFCApplication2Dlg::OnBnClickedButtonOpen()
{
	// Action 스레드 중지
	m_eventStopThread.SetEvent();

	// Open 로직은 기존대로 유지
	CFileDialog dlg(TRUE, _T("jpg"), NULL, OFN_FILEMUSTEXIST, _T("Image Files|*.bmp;*.jpg;*.jpeg;*.png|All Files|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		CImage image;
		HRESULT hr = image.Load(filePath);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("이미지 로드 실패!"));
			return;
		}

		CClientDC dc(this);

		int x = 10, y = 10;
		image.Draw(dc.m_hDC, x, y);

		int centerX = x + image.GetWidth() / 2;
		int centerY = y + image.GetHeight() / 2;

		dc.MoveTo(centerX - 10, centerY);
		dc.LineTo(centerX + 10, centerY);
		dc.MoveTo(centerX, centerY - 10);
		dc.LineTo(centerX, centerY + 10);

		CString coordinates;
		coordinates.Format(_T("(%d, %d)"), centerX, centerY);
		dc.TextOutW(centerX + 15, centerY, coordinates);
	}
}



void CMFCApplication2Dlg::OnBnClickedButtonAction()
{
	AfxBeginThread(CMFCApplication2Dlg::MoveCircleThread, this); // 정적 함수 호출
}

UINT CMFCApplication2Dlg::MoveCircleThread(LPVOID pParam)
{
	CMFCApplication2Dlg *pDlg = static_cast<CMFCApplication2Dlg *>(pParam);

	int x1 = pDlg->GetDlgItemInt(IDC_EDIT_X1);
	int y1 = pDlg->GetDlgItemInt(IDC_EDIT_Y1);
	int x2 = pDlg->GetDlgItemInt(IDC_EDIT_X2);
	int y2 = pDlg->GetDlgItemInt(IDC_EDIT_Y2);

	CClientDC dc(pDlg);

	int steps = 10;
	for (int i = 0; i <= steps; ++i)
	{
		// 중지 이벤트 확인
		if (WaitForSingleObject(pDlg->m_eventStopThread.m_hObject, 0) == WAIT_OBJECT_0)
		{
			break; // 중지 신호를 받으면 루프 탈출
		}

		int cx = x1 + (x2 - x1) * i / steps;
		int cy = y1 + (y2 - y1) * i / steps;

		pDlg->Invalidate();
		pDlg->UpdateWindow();

		CBrush brush(RGB(255, 0, 0));
		dc.SelectObject(&brush);
		dc.Ellipse(cx - 20, cy - 20, cx + 20, cy + 20);

		CString fileName;
		fileName.Format(_T("image/frame_%d.jpg"), i);

		CImage image;
		image.Create(800, 600, 32);
		CDC *pImageDC = CDC::FromHandle(image.GetDC());
		pImageDC->BitBlt(0, 0, 800, 600, &dc, 0, 0, SRCCOPY);
		image.ReleaseDC();
		image.Save(fileName);

		Sleep(100);
	}

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



