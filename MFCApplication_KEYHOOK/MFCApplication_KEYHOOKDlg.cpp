
// MFCApplication_KEYHOOKDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication_KEYHOOK.h"
#include "MFCApplication_KEYHOOKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WH_KEYBOARD_LL 13


// Global variables
HHOOK g_hHook = NULL;
bool g_bAltPressed = false;


// Hook procedure prototype
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
// Function to install the hook
void InstallHook()
{
	g_hHook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	if (g_hHook == NULL)
	{
		OutputDebugString(L"Failed to install hook!");
	}
}
// Function to uninstall the hook
void UninstallHook()
{
	if (g_hHook != NULL)
	{
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
	}
}
// The hook procedure that processes key events
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) // If the hook code is HC_ACTION
	{
		KBDLLHOOKSTRUCT* pKbd = (KBDLLHOOKSTRUCT*)lParam;

		if (wParam == 0x104) {

			if (pKbd->vkCode == VK_LMENU ) // Detect Alt key
			{
				//MessageBox(NULL, _T("Alt Detected!"), _T("Key Pressed"), MB_OK);
				OutputDebugString(_T("Alt Detected!"));
				g_bAltPressed = true; // Set Alt as pressed		
			}
			if (pKbd->vkCode == VK_TAB && g_bAltPressed) // Detect Alt key
			{
				//MessageBox(NULL, _T("Alt Detected!"), _T("Key Pressed"), MB_OK);
				OutputDebugString(_T("Alt + TAB Detected!"));
				g_bAltPressed = false; // Set Alt as pressed
				return 1;
			}
		}
		if (wParam == WM_KEYDOWN) {
			if (pKbd->vkCode == VK_LWIN || pKbd->vkCode == VK_RWIN) {
				OutputDebugString(_T("WinMenu Detected!"));
				return 1;
			}
		}
		if (wParam == WM_KEYUP) {
			g_bAltPressed = false;
		}
	}
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}
// CAboutDlg dialog used for App About


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCApplicationKEYHOOKDlg dialog



CMFCApplicationKEYHOOKDlg::CMFCApplicationKEYHOOKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_KEYHOOK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationKEYHOOKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationKEYHOOKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplicationKEYHOOKDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplicationKEYHOOKDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCApplicationKEYHOOKDlg message handlers

BOOL CMFCApplicationKEYHOOKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InstallHook();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplicationKEYHOOKDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplicationKEYHOOKDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplicationKEYHOOKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationKEYHOOKDlg::OnBnClickedOk()
{


	InstallHook();

}


void CMFCApplicationKEYHOOKDlg::OnBnClickedCancel()
{

	UninstallHook();
	CDialogEx::OnCancel();
}
