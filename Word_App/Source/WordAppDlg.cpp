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

	// 초기화가 필요한 변수들을 초기화한다.
	m_BlinkStep = 0;
	m_bStart = FALSE;
	m_QCount = 0;
	m_SelectRow = -1;

	// 화면을 구성하는 기본 값을 불러들인다.
	InitButton();
	InitFont();
	InsertColumn();
	OnLoad();
	OnMenu1button();

	int nItems = m_List.GetItemCount();	// 저장된 단어 개수를 가져온다.
	if(nItems == 0) {
		m_QNumber = -1;
	} else {
		SetQNumber();					// 문제 번호를 난수를 발생시켜 생성한다.
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
	// 폰트를 초기화 한다.
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
	// 이미지 버튼을 초기화 한다.
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
	m_QNumber = rand() % nItems;		// 문제 번호를 생성한다.
}

void CWordAppDlg::OnSave()
{
	CFile file;
	char szWord[64] = {0,};
	char szMeaning[64] = {0,};
	CString szBuffer;

	CFile::Remove("ENGword.txt"); // 파일이 존재하는 경우 삭제 후 새로 저장한다.
	file.Open(_T("ENGword.txt"), CFile::modeNoTruncate | CFile::modeWrite | CFile::modeCreate);

	for(int i = 0; i < m_List.GetItemCount(); i++)	// 입력된 단어의 개수만큼 반복.
	{
		m_List.GetItemText(i, 0, szWord, 64);
		m_List.GetItemText(i, 1, szMeaning, 64);
		
		szBuffer.Format("%s|%s\r\n", szWord, szMeaning);
		file.Write(szBuffer, strlen(szBuffer));	// 파일에 단어를 저장한다.
	}
	file.Close();
}

void CWordAppDlg::OnLoad()
{
	// ENGword.txt를 불러들인다.
	CStdioFile file;
	CString szBuffer;
	CString Word;
	CString Meaning;

	file.Open(_T("ENGword.txt"), CFile::modeNoTruncate | CFile::modeRead | CFile::modeCreate);

	while(file.ReadString(szBuffer)) // EOF까지 한줄 단위로 문자열을 읽어들인다.
	{
		AfxExtractSubString(Word, szBuffer, 0, '|');		// 단어 저장
		AfxExtractSubString(Meaning, szBuffer, 1, '|');		// 뜻 저장

		InsertWord(Word, Meaning);							// 읽어들인 단어를 리스트 컨트롤에 추가한다.
	}
	file.Close();
}

void CWordAppDlg::OnSavebutton() 
{
	CFile file;
	CString szBuffer;

	UpdateData(TRUE);	// 컨트롤의 값을 컨트롤변수에 갱신시킨다.

	if(m_InputWord == "" || m_InputMeaning == "") {	// 단어 또는 뜻을 입력하지 않은 경우.
		CWnd::MessageBox("단어와 뜻을 모두 입력하셔야 합니다.", "삽 입", MB_OK);
		return;
	}

	m_InputWord.Replace(_T("|"), _T(","));
	m_InputMeaning.Replace(_T("|"), _T(","));	// 구분자로 쓰이는 '|'를 ','로 수정한 후 입력되게끔 한다.
	if(!IsDuplicate(m_InputWord)) {	// 중복된 단어는 입력할 수 없다.
		CWnd::MessageBox("중복된 단어는 입력하실 수 없습니다.", "삽 입", MB_OK);
		return;
	}
	szBuffer.Format("%s|%s\r\n", m_InputWord, m_InputMeaning);

	file.Open(_T("ENGword.txt"), CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
	file.SeekToEnd();						// 파일의 가장 마지막 위치로 이동한 후,
	file.Write(szBuffer, strlen(szBuffer));	// 파일에 단어를 기록한다.
	file.Close();

	InsertWord(m_InputWord, m_InputMeaning);	// 기록한 단어를 리스트 컨트롤에 추가한다.

	m_InputWord = "";
	m_InputMeaning = "";
	m_SelectWord = "";
	m_SelectMeaning = "";
	m_SelectRow = -1;

	UpdateData(FALSE);	// 변수에 설정된 값을 컨트롤에 갱신시킨다.

	CWnd::MessageBox("기록하였습니다.", "단어 입력", MB_OK);	
}

void CWordAppDlg::OnDeletebutton() 
{
	if(m_SelectRow < 0)	// 삭제할 단어를 선택하지 않은 경우.
	{
		CWnd::MessageBox("삭제할 단어를 선택하시기 바랍니다.", "삭 제", MB_OK);
		return;
	} else if(CWnd::MessageBox("선택된 항목을 삭제 하시겠습니까?", "삭 제", MB_YESNO) == 6) {
		m_List.DeleteItem(m_SelectRow);	// 단어를 삭제한다.

		m_SelectWord = "";
		m_SelectMeaning = "";

		((CEdit *)GetDlgItem(IDC_SELECTWORD))->SetWindowText(m_SelectWord);
		((CEdit *)GetDlgItem(IDC_SELECTMEANING))->SetWindowText(m_SelectMeaning);

		m_SelectRow = -1;
		OnSave();	// 단어장을 새로 txt 파일에 기록한다.

		CWnd::MessageBox("삭제되었습니다.", "알 림", MB_OK);
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
		if(strcmp(szWord1, szWord2) == 0) return FALSE;	// 이미 입력된 단어인 경우 FALSE를 반환한다.
	}

	return TRUE; // 새로 입력된 단어인 경우에 이곳까지 진입한다.
}

void CWordAppDlg::InsertColumn()
{
	CRect rect;
	m_List.GetClientRect(&rect); // 리스트 컨트롤의 크기를 얻어온다.

	// 컬럼 추가
	m_List.InsertColumn(0, _T("단어"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(1, _T("의미"), LVCFMT_LEFT, rect.Width() - 150);
}

void CWordAppDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	// 리스트 컨트롤의 선택된 항목이 변경되면 호출된다.
	POSITION Row = m_List.GetFirstSelectedItemPosition();

	int nRow = (int)Row;
	if(nRow-- == 0) return;

	CString strTmp;

	// 선택된 단어란에 단어와 뜻을 기록한다.
	m_List.GetItemText(nRow, 0, (LPSTR)(LPCSTR)strTmp, 64);
	((CEdit *)GetDlgItem(IDC_SELECTWORD))->SetWindowText(strTmp);
	m_List.GetItemText(nRow, 1, (LPSTR)(LPCSTR)strTmp, 64);
	((CEdit *)GetDlgItem(IDC_SELECTMEANING))->SetWindowText(strTmp);

	m_SelectRow = nRow;

	*pResult = 0;
}

void CWordAppDlg::InsertWord(CString Word, CString Meaning)
{
	// 단어를 단어장의 가장 마지막 위치에 기록한다.
	int nItemNum = m_List.GetItemCount();
	m_List.InsertItem(nItemNum, Word, 0);
	m_List.SetItemText(nItemNum, 1, Meaning);
	SetQNumber();
}

// 디버깅을 위한 선언. 후에 삭제.
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
		CWnd::MessageBox("입력된 단어가 없으므로 실행할 수 없습니다.", "알 림", MB_OK);
		return;
	}
	SetMenu1Series(FALSE);
	SetMenu3Series(FALSE);

	SetMenu2Series(TRUE);
}

void CWordAppDlg::OnMenu3button() 
{	
	if(m_QNumber == -1) {
		CWnd::MessageBox("입력된 단어가 없으므로 실행할 수 없습니다.", "알 림", MB_OK);
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
	m_QCount = 1;	// 10문항 선택
}

void CWordAppDlg::OnRadio2() 
{
	m_QCount = 2;	// 20문항 선택
}

void CWordAppDlg::OnStartbutton() 
{
	int nItems;
	CString strTmp;

	if(m_bStart) {
		if(CWnd::MessageBox("진행중인 테스트를 중단하고 새로하시겠습니까?", "알 림", MB_YESNO) == 6) {
			((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText("");
			InitProgressBar();	// 프로그레스바 초기화
			m_QCount = 0;		// 선택문항 수 초기화
			m_bStart = FALSE;	// 시작 변수 초기화
			return;
		}
		else return;
	} else if(m_QCount < 1) {	// 문항수가 선택되지 않은 경우
		CWnd::MessageBox("문항수를 선택해주시기 바랍니다.", "알 림", MB_OK);
		return;
	}

	nItems = m_List.GetItemCount();	// 저장된 단어 개수를 가져온다.
	m_bStart = TRUE;	// 시작 변수를 갱신한다.
	m_QCount *= 10;		// 문항 수를 지정한다.
	SetProgressBar(m_QCount);	// 프로그레스 바의 범위를 지정한다.

	srand((unsigned)time(NULL));	// 시간 값을 시드로 받아와 난수를 생성한다.
	m_QNumber = rand() % nItems;

	m_List.GetItemText(m_QNumber, 1, (LPSTR)(LPCSTR)strTmp, 64);
	((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText(strTmp);	// 문제를 제출한다.
}

void CWordAppDlg::OnOkanswer() 
{
	int nItems = m_List.GetItemCount();
	char szQuestion[64] = {0, };
	char szAnswer[64] = {0, };
	float grade;
	CString strTmp;

	if(!m_bStart) {
		CWnd::MessageBox("문항수를 선택해주시기 바랍니다.", "알 림", MB_OK);
		return;
	}

	m_List.GetItemText(m_QNumber, 0, szQuestion, 64); // 정답을 불러온다.
	((CEdit *)GetDlgItem(IDC_ANSWER))->GetWindowText(szAnswer, 64); // 사용자의 답을 가져온다.
	
	// 정답 여부 판정.
	if(strcmp(szAnswer, szQuestion) == 0) {
		CWnd::MessageBox("정답입니다.", "확 인", MB_OK);
		m_CorrectBar.SetPos(m_CorrectBar.GetPos() + 1);
	} else {
		CWnd::MessageBox("오답입니다.", "확 인", MB_OK);
		m_WrongBar.SetPos(m_WrongBar.GetPos() + 1);
	}

	grade = (float)m_CorrectBar.GetPos() / (float)(m_CorrectBar.GetPos() + m_WrongBar.GetPos()) * 100;
	m_GradeBar.SetPos((int)grade);	// 정답률을 기록한다.

	((CEdit *)GetDlgItem(IDC_ANSWER))->SetWindowText(""); // 정답 기입란을 비운다.

	if(--m_QCount == 0)	// 퀴즈가 끝난 경우.
	{
		m_bStart = FALSE; // 시작 변수를 초기화 한다.
		((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText(""); // 문제란을 비운다.
		strTmp.Format("정답수 : %d\n오답수 : %d\n정답률 : %d％\n\n수고하셨습니다.", m_CorrectBar.GetPos(), m_WrongBar.GetPos(), m_GradeBar.GetPos());
		CWnd::MessageBox(strTmp, "결 과", MB_OK); // 결과를 출력한다.
		InitProgressBar();
	} 
	else { // 다음 문제를 준비한다.
		m_QNumber = rand() % nItems; // 문제 번호를 생성한다.
		m_List.GetItemText(m_QNumber, 1, (LPSTR)(LPCSTR)strTmp, 64);
		((CEdit *)GetDlgItem(IDC_QUESTION))->SetWindowText(strTmp); // 문제를 제시한다.
	}
}

void CWordAppDlg::InitProgressBar()
{
	// 프로그레스 바의 현재 값을 0으로 초기화한다.
	m_CorrectBar.SetPos(0);
	m_WrongBar.SetPos(0);
	m_GradeBar.SetPos(0);
}

void CWordAppDlg::SetProgressBar(int Range)
{
	// 프로그레스 바의 범위를 설정한다.
	m_CorrectBar.SetRange(0, Range);
	m_WrongBar.SetRange(0, Range);
	m_GradeBar.SetRange(0, 100);
}

void CWordAppDlg::OnPlaybutton() 
{
	KillTimer(1);			// 타이머의 초기화를 수행하기 위해 타이머를 종료시킨다.
	m_BlinkStep = 0;
	SetTimer(1, 500, NULL);	// 타이머를 실행시킨다. 3초가 지나면 자동 만료된다.
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
		BlinkText(TRUE);	// 학습할 단어를 출력한다.
	} else {
		BlinkText(FALSE);	// 학습할 단어를 지운다. (출력 -> 지움 = 깜빡임 효과)
	}
	if(++m_BlinkStep == 5) {	// 3번 깜빡이면 타이머를 종료시킨다.
		m_BlinkStep = 0;
		KillTimer(1);
	}
	CBitmapDialog::OnTimer(nIDEvent);
}


void CWordAppDlg::BlinkText(BOOL bBlink)
{
	CString strTmp;
	InvalidateRect(NULL, FALSE); // OnPaint() 함수를 호출하여 화면을 새로 구성한다.

	if(bBlink) {	// 학습할 단어를 출력한다.
		m_List.GetItemText(m_QNumber, 0, (LPSTR)(LPCSTR)strTmp, 64);
		((CEdit *)GetDlgItem(IDC_BLINKWORD))->SetWindowText(strTmp);
		m_List.GetItemText(m_QNumber, 1, (LPSTR)(LPCSTR)strTmp, 64);
		((CEdit *)GetDlgItem(IDC_BLINKMEANING))->SetWindowText(strTmp);
	} else {		// 학습할 단어를 지운다.
		((CEdit *)GetDlgItem(IDC_BLINKWORD))->SetWindowText("");
		((CEdit *)GetDlgItem(IDC_BLINKMEANING))->SetWindowText("");
	}
}

void CWordAppDlg::OnExitbutton() 
{
	// 종료 함수.
	if(CWnd::MessageBox("종료하시겠습니까?", "종 료", MB_YESNO) == 6) {
		CBitmapDialog::OnOK();
	}
}
void CWordAppDlg::OnCancel() { OnExitbutton(); }
