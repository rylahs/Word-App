// WordAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WordApp.h"
#include "WordAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFF_SIZE 64

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CBitmapDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBitmapDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordAppDlg dialog

CWordAppDlg::CWordAppDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CWordAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWordAppDlg)
	m_InputMeaning = _T("");
	m_InputWord = _T("");
	m_SelectMeaning = _T("");
	m_SelectWord = _T("");
	m_QCount = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAIN);
}

void CWordAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordAppDlg)
	DDX_Control(pDX, IDC_NEXTBUTTON, m_NextBtn);
	DDX_Control(pDX, IDC_PLAYBUTTON, m_PlayBtn);
	DDX_Control(pDX, IDC_CORRECTBAR, m_CorrectBar);
	DDX_Control(pDX, IDC_WRONGBAR, m_WrongBar);
	DDX_Control(pDX, IDC_GRADEBAR, m_GradeBar);
	DDX_Control(pDX, IDC_SAVEBUTTON, m_SaveBtn);
	DDX_Control(pDX, IDC_DELETEBUTTON, m_DeleteBtn);
	DDX_Control(pDX, IDC_MENU1BUTTON, m_MenuBtn1);
	DDX_Control(pDX, IDC_MENU2BUTTON, m_MenuBtn2);
	DDX_Control(pDX, IDC_MENU3BUTTON, m_MenuBtn3);
	DDX_Control(pDX, IDC_MENU4BUTTON, m_MenuBtn4);
	DDX_Control(pDX, IDC_QUESTIONMARK, m_QuestionMark);
	DDX_Control(pDX, IDC_STARTBUTTON, m_StartBtn);
	DDX_Control(pDX, IDC_OKANSWER, m_OkAnswerBtn);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_INPUTMEANING, m_InputMeaning);
	DDX_Text(pDX, IDC_INPUTWORD, m_InputWord);
	DDX_Text(pDX, IDC_SELECTMEANING, m_SelectMeaning);
	DDX_Text(pDX, IDC_SELECTWORD, m_SelectWord);
	DDX_Radio(pDX, IDC_RADIO1, m_QCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWordAppDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CWordAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DELETEBUTTON, OnDeletebutton)
	ON_BN_CLICKED(IDC_MENU4BUTTON, OnExitbutton)
	ON_BN_CLICKED(IDC_SAVEBUTTON, OnSavebutton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_MENU1BUTTON, OnMenu1button)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_STARTBUTTON, OnStartbutton)
	ON_BN_CLICKED(IDC_OKANSWER, OnOkanswer)
	ON_BN_CLICKED(IDC_MENU2BUTTON, OnMenu2button)
	ON_BN_CLICKED(IDC_MENU3BUTTON, OnMenu3button)
	ON_BN_CLICKED(IDC_PLAYBUTTON, OnPlaybutton)
	ON_BN_CLICKED(IDC_NEXTBUTTON, OnNextbutton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordAppDlg message handlers

BOOL CWordAppDlg::OnInitDialog()
{
	CBitmapDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetBitmap(IDB_BG, CBitmapDialog::BITMAP_STRETCH);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ�Ѵ�.
	m_BlinkStep = 0;
	m_bStart = FALSE;
	m_QCount = 0;
	m_SelectRow = -1;

	// ȭ���� �����ϴ� �⺻ ���� �ҷ����δ�.
	InitButton();
	InitFont();
	InsertColumn();
	OnLoad();
	OnMenu1button();

	int nItems = m_List.GetItemCount();	// ����� �ܾ� ������ �����´�.
	if(nItems == 0) {
		m_QNumber = -1;
	} else {
		SetQNumber();					// ���� ��ȣ�� ������ �߻����� �����Ѵ�.
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWordAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBitmapDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWordAppDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		CRect rect;
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		GetClientRect(&rect);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBitmapDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWordAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CWordAppDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{          
		return TRUE;
	}
	return CBitmapDialog::PreTranslateMessage(pMsg);
}

void CWordAppDlg::InitFont()
{
	// ��Ʈ�� �ʱ�ȭ �Ѵ�.
	cFont.CreateFont(24, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Tahoma"));
	cFont2.CreateFont(18, 8, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Tahoma"));

	GetDlgItem(IDC_INSERTION)->SetFont(&cFont);
	GetDlgItem(IDC_DELETION)->SetFont(&cFont);
	GetDlgItem(IDC_QUESTION)->SetFont(&cFont);
	GetDlgItem(IDC_QUESTION2)->SetFont(&cFont);
	GetDlgItem(IDC_ANSWER)->SetFont(&cFont);

	GetDlgItem(IDC_RADIO1)->SetFont(&cFont2);
	GetDlgItem(IDC_RADIO2)->SetFont(&cFont2);
	GetDlgItem(IDC_CORRECTS)->SetFont(&cFont2);
	GetDlgItem(IDC_WRONGS)->SetFont(&cFont2);
	GetDlgItem(IDC_RATE)->SetFont(&cFont2);

	GetDlgItem(IDC_BLINKWORD)->SetFont(&cFont);
	GetDlgItem(IDC_BLINKMEANING)->SetFont(&cFont);
}

void CWordAppDlg::InitButton()
{
	// �̹��� ��ư�� �ʱ�ȭ �Ѵ�.
	m_MenuBtn1.LoadBitmaps(IDB_MENU1);
	m_MenuBtn1.SizeToContent();

	m_MenuBtn2.LoadBitmaps(IDB_MENU2);
	m_MenuBtn2.SizeToContent();

	m_MenuBtn3.LoadBitmaps(IDB_MENU3);
	m_MenuBtn3.SizeToContent();

	m_MenuBtn4.LoadBitmaps(IDB_MENU4);
	m_MenuBtn4.SizeToContent();

	m_SaveBtn.LoadBitmaps(IDB_ADD);
	m_SaveBtn.SizeToContent();

	m_DeleteBtn.LoadBitmaps(IDB_DELETE);
	m_DeleteBtn.SizeToContent();

	m_StartBtn.LoadBitmaps(IDB_START);
	m_StartBtn.SizeToContent();

	m_OkAnswerBtn.LoadBitmaps(IDB_SUBMIT);
	m_OkAnswerBtn.SizeToContent();

	m_QuestionMark.LoadBitmaps(IDB_QUESTION);
	m_QuestionMark.SizeToContent();

	m_PlayBtn.LoadBitmaps(IDB_PLAY);
	m_PlayBtn.SizeToContent();

	m_NextBtn.LoadBitmaps(IDB_NEXT);
	m_NextBtn.SizeToContent();
}

void CWordAppDlg::SetQNumber()
{
	int nItems = m_List.GetItemCount();
	srand((unsigned int)time(NULL));
	m_QNumber = rand() % nItems;		// ���� ��ȣ�� �����Ѵ�.
}

void CWordAppDlg::OnSave()
{
	CFile file;
	char szWord[64] = {0,};
	char szMeaning[64] = {0,};
	CString szBuffer;

	CFile::Remove("ENGword.txt"); // ������ �����ϴ� ��� ���� �� ���� �����Ѵ�.
	file.Open(_T("ENGword.txt"), CFile::modeNoTruncate | CFile::modeWrite | CFile::modeCreate);

	for(int i = 0; i < m_List.GetItemCount(); i++)	// �Էµ� �ܾ��� ������ŭ �ݺ�.
	{
		m_List.GetItemText(i, 0, szWord, 64);
		m_List.GetItemText(i, 1, szMeaning, 64);
		
		szBuffer.Format("%s|%s\r\n", szWord, szMeaning);
		file.Write(szBuffer, strlen(szBuffer));	// ���Ͽ� �ܾ �����Ѵ�.
	}
	file.Close();
}

void CWordAppDlg::OnLoad()
{
	// ENGword.txt�� �ҷ����δ�.
	CStdioFile file;
	CString szBuffer;
	CString Word;
	CString Meaning;

	file.Open(_T("ENGword.txt"), CFile::modeNoTruncate | CFile::modeRead | CFile::modeCreate);

	while(file.ReadString(szBuffer)) // EOF���� ���� ������ ���ڿ��� �о���δ�.
	{
		AfxExtractSubString(Word, szBuffer, 0, '|');		// �ܾ� ����
		AfxExtractSubString(Meaning, szBuffer, 1, '|');		// �� ����

		InsertWord(Word, Meaning);							// �о���� �ܾ ����Ʈ ��Ʈ�ѿ� �߰��Ѵ�.
	}
	file.Close();
}

void CWordAppDlg::OnSavebutton() 
{
	CFile file;
	CString szBuffer;

	UpdateData(TRUE);	// ��Ʈ���� ���� ��Ʈ�Ѻ����� ���Ž�Ų��.

	if(m_InputWord == "" || m_InputMeaning == "") {	// �ܾ� �Ǵ� ���� �Է����� ���� ���.
		CWnd::MessageBox("�ܾ�� ���� ��� �Է��ϼž� �մϴ�.", "�� ��", MB_OK);
		return;
	}

	m_InputWord.Replace(_T("|"), _T(","));
	m_InputMeaning.Replace(_T("|"), _T(","));	// �����ڷ� ���̴� '|'�� ','�� ������ �� �ԷµǰԲ� �Ѵ�.
	if(!IsDuplicate(m_InputWord)) {	// �ߺ��� �ܾ�� �Է��� �� ����.
		CWnd::MessageBox("�ߺ��� �ܾ�� �Է��Ͻ� �� �����ϴ�.", "�� ��", MB_OK);
		return;
	}
	szBuffer.Format("%s|%s\r\n", m_InputWord, m_InputMeaning);

	file.Open(_T("ENGword.txt"), CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
	file.SeekToEnd();						// ������ ���� ������ ��ġ�� �̵��� ��,
	file.Write(szBuffer, strlen(szBuffer));	// ���Ͽ� �ܾ ����Ѵ�.
	file.Close();

	InsertWord(m_InputWord, m_InputMeaning);	// ����� �ܾ ����Ʈ ��Ʈ�ѿ� �߰��Ѵ�.

	m_InputWord = "";
	m_InputMeaning = "";
	m_SelectWord = "";
	m_SelectMeaning = "";
	m_SelectRow = -1;

	UpdateData(FALSE);	// ������ ������ ���� ��Ʈ�ѿ� ���Ž�Ų��.

	CWnd::MessageBox("����Ͽ����ϴ�.", "�ܾ� �Է�", MB_OK);	
}

void CWordAppDlg::OnDeletebutton() 
{
	if(m_SelectRow < 0)	// ������ �ܾ �������� ���� ���.
	{
		CWnd::MessageBox("������ �ܾ �����Ͻñ� �ٶ��ϴ�.", "�� ��", MB_OK);
		return;
	} else if(CWnd::MessageBox("���õ� �׸��� ���� �Ͻðڽ��ϱ�?", "�� ��", MB_YESNO) == 6) {
		m_List.DeleteItem(m_SelectRow);	// �ܾ �����Ѵ�.

		m_SelectWord = "";
		m_SelectMeaning = "";

		((CEdit *)GetDlgItem(IDC_SELECTWORD))->SetWindowText(m_SelectWord);
		((CEdit *)GetDlgItem(IDC_SELECTMEANING))->SetWindowText(m_SelectMeaning);

		m_SelectRow = -1;
		OnSave();	// �ܾ����� ���� txt ���Ͽ� ����Ѵ�.

		CWnd::MessageBox("�����Ǿ����ϴ�.", "�� ��", MB_OK);
	}	
}

BOOL CWordAppDlg::IsDuplicate(CString Word)
{
	char szWord1[BUFF_SIZE] = {0, };
	char szWord2[BUFF_SIZE] = {0, };
	int nLength = (BUFF_SIZE > strlen(Word)) ? strlen(Word) : BUFF_SIZE;
	int nTxtLength = 0;
	int nRows = m_List.GetItemCount();

	strncpy(szWord1, (LPSTR)(LPCSTR)Word, nLength);
	for(int i = 0; i < nRows; i++)
	{
		nTxtLength = m_List.GetItemText(i, 0, szWord2, BUFF_SIZE);
		if(strcmp(szWord1, szWord2) == 0) return FALSE;	// �̹� �Էµ� �ܾ��� ��� FALSE�� ��ȯ�Ѵ�.
	}

	return TRUE; // ���� �Էµ� �ܾ��� ��쿡 �̰����� �����Ѵ�.
}

void CWordAppDlg::InsertColumn()
{
	CRect rect;
	m_List.GetClientRect(&rect); // ����Ʈ ��Ʈ���� ũ�⸦ ���´�.

	// �÷� �߰�
	m_List.InsertColumn(0, _T("�ܾ�"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(1, _T("�ǹ�"), LVCFMT_LEFT, rect.Width() - 150);
}

void CWordAppDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	// ����Ʈ ��Ʈ���� ���õ� �׸��� ����Ǹ� ȣ��ȴ�.
	POSITION Row = m_List.GetFirstSelectedItemPosition();

	int nRow = (int)Row;
	if(nRow-- == 0) return;

	CString strTmp;

	// ���õ� �ܾ���� �ܾ�� ���� ����Ѵ�.
	m_List.GetItemText(nRow, 0, (LPSTR)(LPCSTR)strTmp, 64);
	((CEdit *)GetDlgItem(IDC_SELECTWORD))->SetWindowText(strTmp);
	m_List.GetItemText(nRow, 1, (LPSTR)(LPCSTR)strTmp, 64);
	((CEdit *)GetDlgItem(IDC_SELECTMEANING))->SetWindowText(strTmp);

	m_SelectRow = nRow;

	*pResult = 0;
}

void CWordAppDlg::InsertWord(CString Word, CString Meaning)
{
	// �ܾ �ܾ����� ���� ������ ��ġ�� ����Ѵ�.
	int nItemNum = m_List.GetItemCount();
	m_List.InsertItem(nItemNum, Word, 0);
	m_List.SetItemText(nItemNum, 1, Meaning);
	SetQNumber();
}

// ������� ���� ����. �Ŀ� ����.
void CWordAppDlg::IntMsgBox(int arg)
{
	CString strTmp;
	strTmp.Format("%d", arg);
	AfxMessageBox(strTmp);
}

void CWordAppDlg::OnMenu1button() 
{
	SetMenu2Series(FALSE);
	SetMenu3Series(FALSE);
	
	SetMenu1Series(TRUE);

	InvalidateRect(FALSE);
}

void CWordAppDlg::OnMenu2button() 
{
	if(m_QNumber == -1) {
		CWnd::MessageBox("�Էµ� �ܾ �����Ƿ� ������ �� �����ϴ�.", "�� ��", MB_OK);
		return;
	}
	SetMenu1Series(FALSE);
	SetMenu3Series(FALSE);

	SetMenu2Series(TRUE);
}

void CWordAppDlg::OnMenu3button() 
{	
	if(m_QNumber == -1) {
		CWnd::MessageBox("�Էµ� �ܾ �����Ƿ� ������ �� �����ϴ�.", "�� ��", MB_OK);
		return;
	}
	SetMenu1Series(FALSE);
	SetMenu2Series(FALSE);
	
	SetMenu3Series(TRUE);
}

void CWordAppDlg::SetMenu1Series(BOOL bShow)
{
	GetDlgItem(IDC_INSERTION)->ShowWindow(bShow);
	GetDlgItem(IDC_DELETION)->ShowWindow(bShow);
	GetDlgItem(IDC_INPUTWORD)->ShowWindow(bShow);
	GetDlgItem(IDC_INPUTMEANING)->ShowWindow(bShow);
	GetDlgItem(IDC_SAVEBUTTON)->ShowWindow(bShow);
	GetDlgItem(IDC_SELECTWORD)->ShowWindow(bShow);
	GetDlgItem(IDC_SELECTMEANING)->ShowWindow(bShow);
	GetDlgItem(IDC_DELETEBUTTON)->ShowWindow(bShow);
	GetDlgItem(IDC_LIST)->ShowWindow(bShow);
	m_SelectRow = -1;
}

void CWordAppDlg::SetMenu2Series(BOOL bShow)
{
	GetDlgItem(IDC_BLINK)->ShowWindow(bShow);
	GetDlgItem(IDC_PLAYBUTTON)->ShowWindow(bShow);
	GetDlgItem(IDC_NEXTBUTTON)->ShowWindow(bShow);
	GetDlgItem(IDC_BLINKWORD)->ShowWindow(bShow);
	GetDlgItem(IDC_BLINKMEANING)->ShowWindow(bShow);
	((CEdit *)GetDlgItem(IDC_BLINKWORD))->SetWindowText("Click");
	((CEdit *)GetDlgItem(IDC_BLINKMEANING))->SetWindowText("Play Button!");
}

void CWordAppDlg::SetMenu3Series(BOOL bShow)
{
	GetDlgItem(IDC_QUESTIONS)->ShowWindow(bShow);
	GetDlgItem(IDC_RADIO1)->ShowWindow(bShow);
	GetDlgItem(IDC_RADIO2)->ShowWindow(bShow);
	GetDlgItem(IDC_STARTBUTTON)->ShowWindow(bShow);
	GetDlgItem(IDC_QUESTION)->ShowWindow(bShow);
	GetDlgItem(IDC_QUESTION2)->ShowWindow(bShow);
	GetDlgItem(IDC_ANSWER)->ShowWindow(bShow);
	GetDlgItem(IDC_OKANSWER)->ShowWindow(bShow);
	GetDlgItem(IDC_CORRECTBAR)->ShowWindow(bShow);
	GetDlgItem(IDC_WRONGBAR)->ShowWindow(bShow);
	GetDlgItem(IDC_GRADEBAR)->ShowWindow(bShow);
	GetDlgItem(IDC_CORRECTS)->ShowWindow(bShow);
	GetDlgItem(IDC_WRONGS)->ShowWindow(bShow);
	GetDlgItem(IDC_RATE)->ShowWindow(bShow);
	GetDlgItem(IDC_QUESTIONMARK)->ShowWindow(bShow);
}

void CWordAppDlg::OnRadio1() 
{
	m_QCount = 1;	// 10���� ����
}

void CWordAppDlg::OnRadio2() 
{
	m_QCount = 2;	// 20���� ����
}

void CWordAppDlg::OnStartbutton() 
{
	int nItems;
	CString strTmp;

	if(m_bStart) {
		if(CWnd::MessageBox("�������� �׽�Ʈ�� �ߴ��ϰ� �����Ͻðڽ��ϱ�?", "�� ��", MB_YESNO) == 6) {
			((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText("");
			InitProgressBar();	// ���α׷����� �ʱ�ȭ
			m_QCount = 0;		// ���ù��� �� �ʱ�ȭ
			m_bStart = FALSE;	// ���� ���� �ʱ�ȭ
			return;
		}
		else return;
	} else if(m_QCount < 1) {	// ���׼��� ���õ��� ���� ���
		CWnd::MessageBox("���׼��� �������ֽñ� �ٶ��ϴ�.", "�� ��", MB_OK);
		return;
	}

	nItems = m_List.GetItemCount();	// ����� �ܾ� ������ �����´�.
	m_bStart = TRUE;	// ���� ������ �����Ѵ�.
	m_QCount *= 10;		// ���� ���� �����Ѵ�.
	SetProgressBar(m_QCount);	// ���α׷��� ���� ������ �����Ѵ�.

	srand((unsigned)time(NULL));	// �ð� ���� �õ�� �޾ƿ� ������ �����Ѵ�.
	m_QNumber = rand() % nItems;

	m_List.GetItemText(m_QNumber, 1, (LPSTR)(LPCSTR)strTmp, 64);
	((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText(strTmp);	// ������ �����Ѵ�.
}

void CWordAppDlg::OnOkanswer() 
{
	int nItems = m_List.GetItemCount();
	char szQuestion[64] = {0, };
	char szAnswer[64] = {0, };
	float grade;
	CString strTmp;

	if(!m_bStart) {
		CWnd::MessageBox("���׼��� �������ֽñ� �ٶ��ϴ�.", "�� ��", MB_OK);
		return;
	}

	m_List.GetItemText(m_QNumber, 0, szQuestion, 64); // ������ �ҷ��´�.
	((CEdit *)GetDlgItem(IDC_ANSWER))->GetWindowText(szAnswer, 64); // ������� ���� �����´�.
	
	// ���� ���� ����.
	if(strcmp(szAnswer, szQuestion) == 0) {
		CWnd::MessageBox("�����Դϴ�.", "Ȯ ��", MB_OK);
		m_CorrectBar.SetPos(m_CorrectBar.GetPos() + 1);
	} else {
		CWnd::MessageBox("�����Դϴ�.", "Ȯ ��", MB_OK);
		m_WrongBar.SetPos(m_WrongBar.GetPos() + 1);
	}

	grade = (float)m_CorrectBar.GetPos() / (float)(m_CorrectBar.GetPos() + m_WrongBar.GetPos()) * 100;
	m_GradeBar.SetPos((int)grade);	// ������� ����Ѵ�.

	((CEdit *)GetDlgItem(IDC_ANSWER))->SetWindowText(""); // ���� ���Զ��� ����.

	if(--m_QCount == 0)	// ��� ���� ���.
	{
		m_bStart = FALSE; // ���� ������ �ʱ�ȭ �Ѵ�.
		((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText(""); // �������� ����.
		strTmp.Format("����� : %d\n����� : %d\n����� : %d��\n\n�����ϼ̽��ϴ�.", m_CorrectBar.GetPos(), m_WrongBar.GetPos(), m_GradeBar.GetPos());
		CWnd::MessageBox(strTmp, "�� ��", MB_OK); // ����� ����Ѵ�.
		InitProgressBar();
	} 
	else { // ���� ������ �غ��Ѵ�.
		m_QNumber = rand() % nItems; // ���� ��ȣ�� �����Ѵ�.
		m_List.GetItemText(m_QNumber, 1, (LPSTR)(LPCSTR)strTmp, 64);
		((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText(strTmp); // ������ �����Ѵ�.
	}
}

void CWordAppDlg::InitProgressBar()
{
	// ���α׷��� ���� ���� ���� 0���� �ʱ�ȭ�Ѵ�.
	m_CorrectBar.SetPos(0);
	m_WrongBar.SetPos(0);
	m_GradeBar.SetPos(0);
}

void CWordAppDlg::SetProgressBar(int Range)
{
	// ���α׷��� ���� ������ �����Ѵ�.
	m_CorrectBar.SetRange(0, Range);
	m_WrongBar.SetRange(0, Range);
	m_GradeBar.SetRange(0, 100);
}

void CWordAppDlg::OnPlaybutton() 
{
	KillTimer(1);			// Ÿ�̸��� �ʱ�ȭ�� �����ϱ� ���� Ÿ�̸Ӹ� �����Ų��.
	m_BlinkStep = 0;
	SetTimer(1, 500, NULL);	// Ÿ�̸Ӹ� �����Ų��. 3�ʰ� ������ �ڵ� ����ȴ�.
	BlinkText(TRUE);
}

void CWordAppDlg::OnNextbutton() 
{
	SetQNumber();
	OnPlaybutton();
}

void CWordAppDlg::OnTimer(UINT nIDEvent) 
{
	if( (m_BlinkStep % 2) == 1) {
		BlinkText(TRUE);	// �н��� �ܾ ����Ѵ�.
	} else {
		BlinkText(FALSE);	// �н��� �ܾ �����. (��� -> ���� = ������ ȿ��)
	}
	if(++m_BlinkStep == 5) {	// 3�� �����̸� Ÿ�̸Ӹ� �����Ų��.
		m_BlinkStep = 0;
		KillTimer(1);
	}
	CBitmapDialog::OnTimer(nIDEvent);
}


void CWordAppDlg::BlinkText(BOOL bBlink)
{
	CString strTmp;
	InvalidateRect(NULL, FALSE); // OnPaint() �Լ��� ȣ���Ͽ� ȭ���� ���� �����Ѵ�.

	if(bBlink) {	// �н��� �ܾ ����Ѵ�.
		m_List.GetItemText(m_QNumber, 0, (LPSTR)(LPCSTR)strTmp, 64);
		((CEdit *)GetDlgItem(IDC_BLINKWORD))->SetWindowText(strTmp);
		m_List.GetItemText(m_QNumber, 1, (LPSTR)(LPCSTR)strTmp, 64);
		((CEdit *)GetDlgItem(IDC_BLINKMEANING))->SetWindowText(strTmp);
	} else {		// �н��� �ܾ �����.
		((CEdit *)GetDlgItem(IDC_BLINKWORD))->SetWindowText("");
		((CEdit *)GetDlgItem(IDC_BLINKMEANING))->SetWindowText("");
	}
}

void CWordAppDlg::OnExitbutton() 
{
	// ���� �Լ�.
	if(CWnd::MessageBox("�����Ͻðڽ��ϱ�?", "�� ��", MB_YESNO) == 6) {
		CBitmapDialog::OnOK();
	}
}
void CWordAppDlg::OnCancel() { OnExitbutton(); }
