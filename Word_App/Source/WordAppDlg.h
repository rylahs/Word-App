// WordAppDlg.h : header file
//

#if !defined(AFX_WORDAPPDLG_H__FBD9FC12_348A_4D45_B87F_19C08033EF7C__INCLUDED_)
#define AFX_WORDAPPDLG_H__FBD9FC12_348A_4D45_B87F_19C08033EF7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWordAppDlg dialog

#include "BitmapDialog.h"

class CWordAppDlg : public CBitmapDialog
{
// Construction
public:
	void SetQNumber();
	void InitFont();
// 공통
	// 공통 함수
	void InitButton();								// 이미지 버튼을 초기화 한다.
	void OnLoad();									// 단어를 파일로부터 읽어들인다.
	void OnSave();									// 단어를 파일에 기록한다.
	// 공통 변수
	CFont cFont;									// 사용 폰트 1
	CFont cFont2;									// 사용 폰트 2

// 단어장 메뉴
	// 단어장 메뉴의 함수
	void SetMenu1Series(BOOL bShow);				// 단어장 메뉴를 위한 화면을 구성함.
	void InsertColumn();							// 단어장 리스트 컨트롤 컬럼 추가
	void InsertWord(CString Word, CString Meaning);	// 단어장에 단어를 추가한다.
	BOOL IsDuplicate(CString Word);					// 중복 입력되는 단어인지를 검사한다.
	// 단어장 메뉴의 변수
	int m_SelectRow;								// 단어장에서 선택된 행

// 단어학습 메뉴
	// 단어학습 메뉴의 함수
	void SetMenu2Series(BOOL bShow);				// 단어학습 메뉴를 위한 화면을 구성함.
	void BlinkText(BOOL bBlink);					// 단어를 깜빡인다.
	// 단어학습 메뉴의 변수
	int m_BlinkStep;								// 타이머 종료를 위한 변수.

// 단어시험 메뉴
	// 단어시험 메뉴의 함수
	void SetMenu3Series(BOOL bShow);				// 단어시험 메뉴를 위한 화면을 구성함.
	void SetProgressBar(int Range);					// 프로그레스바의 범위를 재설정한다.
	void InitProgressBar();							// 프로그레스바를 초기화 시킨다.
	// 단어시험 메뉴의 변수
	BOOL m_bStart;									// 단어시험의 시작 여부
	int m_QNumber;									// 문제 번호
	
	void IntMsgBox(int arg); // 추후 삭제
	
	CWordAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWordAppDlg)
	enum { IDD = IDD_WORDAPP_DIALOG };
	CBitmapButton	m_NextBtn;
	CBitmapButton	m_PlayBtn;
	CProgressCtrl	m_CorrectBar;
	CProgressCtrl	m_WrongBar;
	CProgressCtrl	m_GradeBar;
	CBitmapButton	m_SaveBtn;
	CBitmapButton	m_DeleteBtn;
	CBitmapButton	m_MenuBtn1;
	CBitmapButton	m_MenuBtn2;
	CBitmapButton	m_MenuBtn3;
	CBitmapButton	m_MenuBtn4;
	CBitmapButton	m_QuestionMark;
	CBitmapButton	m_StartBtn;
	CBitmapButton	m_OkAnswerBtn;
	CListCtrl	m_List;
	CString	m_InputMeaning;
	CString	m_InputWord;
	CString	m_SelectMeaning;
	CString	m_SelectWord;
	int		m_QCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordAppDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWordAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDeletebutton();
	afx_msg void OnExitbutton();
	virtual void OnCancel();
	afx_msg void OnSavebutton();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenu1button();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnStartbutton();
	afx_msg void OnOkanswer();
	afx_msg void OnMenu2button();
	afx_msg void OnMenu3button();
	afx_msg void OnPlaybutton();
	afx_msg void OnNextbutton();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDAPPDLG_H__FBD9FC12_348A_4D45_B87F_19C08033EF7C__INCLUDED_)
