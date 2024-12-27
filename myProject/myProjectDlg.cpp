
// myProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "myProject.h"
#include "myProjectDlg.h"
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


// CmyProjectDlg 대화 상자

CmyProjectDlg::CmyProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYPROJECT_DIALOG, pParent)
	, m_nEditX1(300) // 좌표값들
	, m_nEditY1(300)
	, m_nEditX2(500)
	, m_nEditY2(300)
	, m_nGray(80)
	, m_nRadius(10)
	, m_currentX(0)     // 현재 X 좌표 초기화
	, m_currentY(0)     // 현재 Y 좌표 초기화
	, m_isActionActive(false)
	, m_nMoveSpeed(5)
	, m_nSaveFrequency(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_nEditX1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nEditY1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nEditX2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_nEditY2);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_nMoveSpeed);
	DDX_Text(pDX, IDC_EDIT_SAVEFREQUENCY, m_nSaveFrequency);
}

BEGIN_MESSAGE_MAP(CmyProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CmyProjectDlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CmyProjectDlg::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CmyProjectDlg::OnBnClickedButtonOpen)
	ON_MESSAGE(WM_USER + 100, &CmyProjectDlg::OnActionComplete)
END_MESSAGE_MAP()


// CmyProjectDlg 메시지 처리기

BOOL CmyProjectDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmyProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmyProjectDlg::OnPaint()
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
HCURSOR CmyProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///
///
/// 내가 작성한 함수들
///
/// 

#include <thread>

// 화면 업데이트 함수
void CmyProjectDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

// 그리기 버튼
void CmyProjectDlg::OnBnClickedButtonDraw()
{
	UpdateData(TRUE);

	// 에딧 컨트롤에서 중심 좌표 받아오기
	int centerX = m_nEditX1;
	int centerY = m_nEditY1;

	// 반지름과 색상 값을 변경
	m_nRadius = (rand() % 41) + 10; // 랜덤 반지름 10~50
	m_nGray = 80;                  // 회색 값

	InitDisplay(); // 화면 초기화
	DrawCircle(centerX, centerY, m_nRadius); // 받은 좌표로 원 그리기
}

// 초기화 후 하얀 캔버스를 그려주는 함수
void CmyProjectDlg::InitDisplay()
{
	int nWidth = 640; // 이미지 너비
	int nHeight = 640; // 이미지 높이
	int nBpp = 8; // 픽셀 깊이 (8비트 흑백 이미지)

	// 이전 리소스 해제
	if (m_image.IsDIBSection()) {
		m_image.Destroy(); // 기존 이미지를 제거
	}
	// 이미지 생성
	if (!m_image.Create(nWidth, -nHeight, nBpp)) {
		AfxMessageBox(_T("이미지 생성에 실패했습니다."));
		return;
	}

	// 흑백만 쓰기 위한 색상 팔레트
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb); // 팔레트 설정
	}

	int nPitch = m_image.GetPitch(); // 이미지 한 줄의 바이트 수
	unsigned char *fm = (unsigned char *)m_image.GetBits(); // 이미지 데이터 포인터
	memset(fm, 0xff, nPitch * nHeight); // 픽셀을 흰색으로 초기화

	UpdateDisplay(); // 초기화된 이미지를 화면에 표시
}

// 원을 그려주는 함수
void CmyProjectDlg::DrawCircle(int centerX, int centerY, int radius)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch(); // 이미지 한 줄의 바이트 수
	unsigned char *fm = (unsigned char *)m_image.GetBits(); // 이미지에 대한 포인터

	// 원을 그리는 루프
	for (int y = -m_nRadius; y <= m_nRadius; y++) {
		for (int x = -m_nRadius; x <= m_nRadius; x++) {
			if (x * x + y * y <= m_nRadius * m_nRadius) { // 원 방정식 사용
				int px = centerX + x;
				int py = centerY + y;

				// m_image 내의 좌표인지 확인
				if (px >= 0 && px < nWidth && py >= 0 && py < nHeight) {
					fm[py * nPitch + px] = m_nGray; // 픽셀을 회색으로 설정
				}
			}
		}
	}

	UpdateDisplay(); // 변경된 이미지를 화면에 표시
}

// 원을 움직이는 함수
bool CmyProjectDlg::moveCircle(int &currentX, int &currentY, int targetX, int targetY)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char *fm = (unsigned char *)m_image.GetBits();

	// 이미지를 흰색으로 초기화
	memset(fm, 0xff, nPitch * nHeight);

	// 현재 위치에 원 그리기 (반지름과 색상은 멤버 변수 사용)
	DrawCircle(currentX, currentY, m_nRadius);

	// X 방향 이동
	if (currentX != targetX) { // 목표에 도달하지 않았다면
		int deltaX = (targetX > currentX) ? m_nMoveSpeed : -m_nMoveSpeed; // 이동할 방향( + | - )과 속도를 계산
		if (abs(targetX - currentX) < abs(deltaX)) { // 만약 속도가 빨라서 목표 위치를 넘어갈 것 같다면
			currentX = targetX; // 그냥 목표 좌표에 바로 도착
		}
		else {
			currentX += deltaX;
		}
	}

	// Y 방향 이동
	if (currentY != targetY) {
		int deltaY = (targetY > currentY) ? m_nMoveSpeed : -m_nMoveSpeed;
		if (abs(targetY - currentY) < abs(deltaY)) {
			currentY = targetY;
		}
		else {
			currentY += deltaY;
		}
	}

	// 목표 좌표에 도달했음을 알림
	return (currentX == targetX && currentY == targetY);
}

// 이미지를 저장하는 함수
void CmyProjectDlg::SaveImage(int stepCount)
{
	// 저장 경로 설정 (프로젝트 폴더의 "saved_images" 디렉터리)
	CString savePath;
	savePath.Format(_T(".\\images\\%03d_step.bmp"), stepCount);

	// 폴더가 없으면 생성
	CreateDirectory(_T(".\\images"), nullptr);

	// 이미지 저장
	if (!m_image.IsNull()) {
		HRESULT hr = m_image.Save(savePath);
		if (FAILED(hr)) {
			AfxMessageBox(_T("이미지 저장 실패!"));
		}
	}
}

// 액션 버튼
void CmyProjectDlg::OnBnClickedButtonAction()
{
	// 중복 실행 방지 플래그
	if (m_isActionActive) return;

	// 플래그 1
	m_isActionActive = true;

	// 에디트 컨트롤로부터 좌표, 속도, 저장 빈도 읽기
	UpdateData(TRUE); // 컨트롤 값을 멤버 변수에 반영
	int currentX = m_nEditX1;
	int currentY = m_nEditY1;
	int targetX = m_nEditX2;
	int targetY = m_nEditY2;
	int saveFrequency = m_nSaveFrequency; // 저장 빈도
	int stepCount = 0;                    // 이동 단계 카운터

	// 스레드 실행. 모든 외부 값 변수를 복사하여 스레드에 전달하는 람다[]가 있음. 이 람다는 값들을 const로 전달함
	// this는 스레드가 CmyProjectDlg 밖에서 실행되기 때문에 포인터로 넘겨주기 위해 필요
	// mutable을 붙이면 const가 아니게 되어 수정 가능해짐. =와 x에만 영향을 미침.
	std::thread actionThread([=, this]() mutable {
		// 이동 애니메이션 실행
		while (true) {
			if (moveCircle(currentX, currentY, targetX, targetY)) {
				break; // 목표 좌표에 도달하면 반복 종료
			}

			// 저장 빈도에 따라 이미지 저장
			if (saveFrequency > 0 && stepCount % saveFrequency == 0) {
				SaveImage(stepCount);
			}

			stepCount++;
			std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 더 정밀
		}

		// 작업 완료 메시지 전송 (비동기)
		PostMessage(WM_ACTION_COMPLETE); // 이를 통해 OnActionComplate를 실행
		});

	actionThread.detach(); // 스레드가 진행되도록 냅두고(detach) 이후의 코드를 실행
}

// 메세지에 대한 답변을 LRESULT로 반환함. bool임
// WPARAM, LPARAM는 메세지와 함께 전달되는 변수. 여기서는 사용 안함.(그러나 없앨 순 업승ㅁ. mfc가 강제함)
LRESULT CmyProjectDlg::OnActionComplete(WPARAM wParam, LPARAM lParam)
{
	m_isActionActive = false; // 작업 상태 플래그를 종료 상태로 변경
	// 필요한 UI 업데이트
	UpdateData(FALSE);
	return 0;
}

// Open 버튼
void CmyProjectDlg::OnBnClickedButtonOpen()
{
	// 파일 탐색창 초기화
	CFileDialog fileDlg(TRUE, _T("bmp"), nullptr,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("BMP Files (*.bmp)|*.bmp||"),
		this);

	// 파일 탐색창에서 이미지를 선택했다면
	if (fileDlg.DoModal() == IDOK) {
		CString filePath = fileDlg.GetPathName(); // 선택한 이미지의 경로

		// Dlg창의 기존 이미지를 해제 (교체해야 하니까)
		if (!m_image.IsNull()) {
			m_image.Destroy();
		}

		// 이미지 로드
		HRESULT hr = m_image.Load(filePath);
		if (FAILED(hr)) {
			AfxMessageBox(_T("이미지 로드 실패!"));
			return;
		}

		// 다이얼로그 크기에 맞게 이미지를 중앙에 표시하기 위해 좌표 계산
		CClientDC dc(this);
		CRect rect;
		GetClientRect(&rect);

		int imgWidth = m_image.GetWidth();
		int imgHeight = m_image.GetHeight();

		// 이미지 출력
		m_image.Draw(dc, 0, 0);

		// 원의 중심 찾기. 흰색이 아닌 픽셀들의 중심값을 계산.
		int nPitch = m_image.GetPitch();
		unsigned char *fm = (unsigned char *)m_image.GetBits();

		int sumX = 0, sumY = 0, count = 0;
		for (int y = 0; y < imgHeight; y++) {
			for (int x = 0; x < imgWidth; x++) {
				if (fm[y * nPitch + x] < 255) { // 흰색이 아닌 픽셀
					sumX += x;
					sumY += y;
					count++;
				}
			}
		}

		if (count > 0) {
			int centerX = sumX / count;
			int centerY = sumY / count;

			// X 모양 그리기
			CPen pen(PS_SOLID, 2, RGB(255, 0, 0)); // 빨간색 펜 생성
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(centerX - 10, centerY - 10); // 좌측 상단에서 우측 하단으로 선
			dc.LineTo(centerX + 10, centerY + 10);

			dc.MoveTo(centerX - 10, centerY + 10); // 좌측 하단에서 우측 상단으로 선
			dc.LineTo(centerX + 10, centerY - 10);

			dc.SelectObject(pOldPen); // 펜 초기화

			// 좌표값 표시
			CString coordText;
			coordText.Format(_T("(%d, %d)"), centerX, centerY);
			dc.TextOutW(centerX + 15, centerY - 15, coordText);
		}
		else {
			AfxMessageBox(_T("이미지에서 원을 찾을 수 없습니다."));
		}
	}
}


