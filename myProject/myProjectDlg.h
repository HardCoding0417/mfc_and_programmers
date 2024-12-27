
// myProjectDlg.h: 헤더 파일
//

#pragma once


// CmyProjectDlg 대화 상자
class CmyProjectDlg : public CDialogEx
{
private:
	CImage m_image;
	BOOL validImgPos(int x, int y);
	int m_nRadius;  // 원 반지름
	int m_nGray;    // 원 색상
	int m_currentX;        // 현재 X 좌표
	int m_currentY;        // 현재 Y 좌표
	bool m_isActionActive; // 액션 활성 상태
// 생성입니다.
public:
	CmyProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	void UpdateDisplay();

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonAction();
	bool moveCircle(int &currentX, int &currentY, int targetX, int targetY);
	void InitDisplay();
	void DrawCircle(int centerX, int centerY, int radius);
	int m_nEditX1;
	int m_nEditY1;
	int m_nEditX2;
	int m_nEditY2;
	int m_nMoveSpeed;
	afx_msg void OnBnClickedButtonOpen();
	void SaveImage(int stepCount);
	int m_nSaveFrequency;
};
