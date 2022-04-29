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
// ����
	// ���� �Լ�
	void InitButton();								// �̹��� ��ư�� �ʱ�ȭ �Ѵ�.
	void OnLoad();									// �ܾ ���Ϸκ��� �о���δ�.
	void OnSave();									// �ܾ ���Ͽ� ����Ѵ�.
	// ���� ����
	CFont cFont;									// ��� ��Ʈ 1
	CFont cFont2;									// ��� ��Ʈ 2

// �ܾ��� �޴�
	// �ܾ��� �޴��� �Լ�
	void SetMenu1Series(BOOL bShow);				// �ܾ��� �޴��� ���� ȭ���� ������.
	void InsertColumn();							// �ܾ��� ����Ʈ ��Ʈ�� �÷� �߰�
	void InsertWord(CString Word, CString Meaning);	// �ܾ��忡 �ܾ �߰��Ѵ�.
	BOOL IsDuplicate(CString Word);					// �ߺ� �ԷµǴ� �ܾ������� �˻��Ѵ�.
	// �ܾ��� �޴��� ����
	int m_SelectRow;								// �ܾ��忡�� ���õ� ��

// �ܾ��н� �޴�
	// �ܾ��н� �޴��� �Լ�
	void SetMenu2Series(BOOL bShow);				// �ܾ��н� �޴��� ���� ȭ���� ������.
	void BlinkText(BOOL bBlink);					// �ܾ �����δ�.
	// �ܾ��н� �޴��� ����
	int m_BlinkStep;								// Ÿ�̸� ���Ḧ ���� ����.

// �ܾ���� �޴�
	// �ܾ���� �޴��� �Լ�
	void SetMenu3Series(BOOL bShow);				// �ܾ���� �޴��� ���� ȭ���� ������.
	void SetProgressBar(int Range);					// ���α׷������� ������ �缳���Ѵ�.
	void InitProgressBar();							// ���α׷����ٸ� �ʱ�ȭ ��Ų��.
	// �ܾ���� �޴��� ����
	BOOL m_bStart;									// �ܾ������ ���� ����
	int m_QNumber;									// ���� ��ȣ
	
	void IntMsgBox(int arg); // ���� ����
	
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
