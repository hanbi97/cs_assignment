
#include "stdafx.h"
#include "MFCApplication6.h"
#include "MFCApplication6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool eflag = true;
bool dflag = false;
int p_count = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);  

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

CMFCApplication6Dlg::CMFCApplication6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION6_DIALOG, pParent)
	, m_input(_T(""))
	, m_temp(_T(""))
	, m_op(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_input);
	DDX_Text(pDX, IDC_EDIT2, m_temp);
	DDX_Text(pDX, IDC_EDIT3, m_op);
}

BEGIN_MESSAGE_MAP(CMFCApplication6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication6Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication6Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication6Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication6Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication6Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication6Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication6Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication6Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &CMFCApplication6Dlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCApplication6Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EQU, &CMFCApplication6Dlg::OnBnClickedButtonEqu)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CMFCApplication6Dlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_C, &CMFCApplication6Dlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CMFCApplication6Dlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_ROOT, &CMFCApplication6Dlg::OnBnClickedButtonRoot)
	ON_BN_CLICKED(IDC_BUTTON_SQU, &CMFCApplication6Dlg::OnBnClickedButtonSqu)
	ON_BN_CLICKED(IDC_BUTTON_POW, &CMFCApplication6Dlg::OnBnClickedButtonPow)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CMFCApplication6Dlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CMFCApplication6Dlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CMFCApplication6Dlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CMFCApplication6Dlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_LP, &CMFCApplication6Dlg::OnBnClickedButtonLp)
	ON_BN_CLICKED(IDC_BUTTON_RP, &CMFCApplication6Dlg::OnBnClickedButtonRp)
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


BOOL CMFCApplication6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(RGB(218, 217, 255)); //배경색 변경
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);	


	return TRUE; 
}

void CMFCApplication6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCApplication6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CMFCApplication6Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetTextColor(RGB(255, 54, 181)); //메시지창 텍스트 색 변경
	return hbr;
}
/*********************************************
	   공학용 계산기 버튼 기능 구현하기
**********************************************/

//숫자버튼 1
void CMFCApplication6Dlg::OnBnClickedButton1()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('1');
	UpdateData(false);
}

//숫자버튼 2
void CMFCApplication6Dlg::OnBnClickedButton2()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('2');
	UpdateData(false);
}

//숫자버튼 3
void CMFCApplication6Dlg::OnBnClickedButton3()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('3');
	UpdateData(false);
}

//숫자버튼 4
void CMFCApplication6Dlg::OnBnClickedButton4()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('4');
	UpdateData(false);
}

//숫자버튼 5
void CMFCApplication6Dlg::OnBnClickedButton5()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('5');
	UpdateData(false);
}

//숫자버튼 6
void CMFCApplication6Dlg::OnBnClickedButton6()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('6');
	UpdateData(false);
}

//숫자버튼 7
void CMFCApplication6Dlg::OnBnClickedButton7()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('7');
	UpdateData(false);
}

//숫자버튼 8
void CMFCApplication6Dlg::OnBnClickedButton8()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('8');
	UpdateData(false);
}

//숫자버튼 9
void CMFCApplication6Dlg::OnBnClickedButton9()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('9');
	UpdateData(false);
}

//숫자버튼 0
void CMFCApplication6Dlg::OnBnClickedButton0()
{
	if (eflag == true)
		m_input = "0";
	eflag = false;
	m_input.AppendChar('0');
	UpdateData(false);
}

//소수점
void CMFCApplication6Dlg::OnBnClickedButtonDot()
{
	if (!dflag)
		m_input.AppendChar('.');
	dflag = true;
	UpdateData(false);
}

// Clear
void CMFCApplication6Dlg::OnBnClickedButtonC()
{
	m_input = "";
	m_op = "";
	m_temp = "";
	eflag = true;
	dflag = false;
	UpdateData(false);
}

// 1글자 지우기
void CMFCApplication6Dlg::OnBnClickedButtonDel()
{
	char buf[100];
	wcstombs(buf, m_input, 100);
	int len = strlen(buf);
	if (len > 0) {
		if (m_input.GetAt(len - 1) == '.') {
			dflag = false;
		}
		m_input.Delete(len - 1, 1);
	}
	UpdateData(false);
}

/***********************************************
         이하 어셈블리어 구현 필수
************************************************/

double array[1000] = {}; //(괄호 안에 숫자 저장할 것
char symbol[100] = {}; // (괄호 안에 +,- 같은거 저장할 것
double array2[1000] = {};
char symbol2[100] = {};
//왼쪽 괄호
void CMFCApplication6Dlg::OnBnClickedButtonLp()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar('(');

	char vchar1[100];
	char vchar2[100];
	wcstombs(vchar1, m_temp, 100); //m_input 담는 배열 vchar1
	wcstombs(vchar2, m_op, 100); //연산자들 담는 배열 vchar2, 연산자들 따로 구분하려고 만듬
	double fval1 = atof(vchar1);//vchar1에 있는 숫자를 double형으로 바꿈
	double res = 0;

	if (m_op == "")
	{
		fval1 = 0;
		m_op = '+';
	}
	for (int i = 0; i < 100; i++)
	{
		if (m_temp == '(')
			break;
			
		else
		{
			array[i] = vchar1[i];
			symbol[i] = vchar2[i];
		}
	}
	
	__asm{
		
	}
	UpdateData(false);
}

//오른쪽 괄호
void CMFCApplication6Dlg::OnBnClickedButtonRp()
{
	if (eflag == true)
		m_input = "";
	eflag = false;
	m_input.AppendChar(')');
	char vchar3[100];
	char vchar4[100];
	char vchar5[100];
	wcstombs(vchar3, m_temp, 100); //m_input 담는 배열 vchar1
	wcstombs(vchar4, m_op, 100); //연산자들 담는 배열 vchar2, 연산자들 따로 구분하려고 만듬
	wcstombs(vchar5, m_input, 100);
	double fval1 = atof(vchar3);//vchar1에 있는 숫자를 double형으로 바꿈
	double fval2 = array2[0];
	double res = 0;
	
	for (int i = 0; i < 100; i++)
	{
		if (m_temp[i] == '(')
		{
			fval1 = 0;
			m_op = '+';

		}
		else if (m_temp[i] == ')')
			break;
		else
		{
			array2[i] = vchar3[i];
			symbol[i] = vchar4[i];
		}

		
	}

	__asm{
		fld fval1
		fld fval2
		fstp res

	}
	UpdateData(false);
}


/*************
   1항연산자
**************/
//제곱근
void CMFCApplication6Dlg::OnBnClickedButtonRoot()
{
	char vchar[100];
	wcstombs(vchar, m_input, 100);
	double fval = atof(vchar);	//입력된 실수
	double res = 0;				//출력할 결과

	/*fsqrt : 제곱근을 계산하는 명령어 
	fval을 로드해서 st(0)에 fval을 넣는다.
	fsqrt를 사용해서 st(0)에 있는 fval의 제곱근을 구한다.
	fstp를 사용해서 st(0)에 저장된 제곱근을 res에 리턴하고 st(0)에 있는 값을 pop한다.*/
	__asm{
	fld fval
	fsqrt
	fstp res
	}
	

	char rval[100];
	sprintf(rval, "%lf", res);
	m_input = rval;				//결과 출력

	eflag = true;
	dflag = false;

	UpdateData(false);
}

//2제곱
void CMFCApplication6Dlg::OnBnClickedButtonSqu()
{
	char vchar[100];
	wcstombs(vchar, m_input, 100);
	double fval = atof(vchar);	//입력된 실수
	double res = 0;				//출력할 결과
	
	/*fval을 로드해서 st(0)에 fval을 넣는다.
	st(0)에 fmul을 사용해서 fval을 곱하고 st(0)에 곱한 값을 저장한다.
	fstp를 사용해서 st(0)에 저장된 값을 res에 리턴하고 st(0)에 있는 값을 pop한다.*/
	__asm{
	fld fval
	fmul fval
	fstp res

	}
	
	
	char rval[100];
	sprintf(rval, "%lf", res);
	m_input = rval;				//결과 출력

	eflag = true;
	dflag = false;

	UpdateData(false);
}


/*************
   2항연산자
**************/
//덧셈 연산자 입력
void CMFCApplication6Dlg::OnBnClickedButtonAdd()
{
	if (m_op != "") {
		double res = calc();
		char rval[100];
		sprintf(rval, "%lf", res);
		m_temp = rval;
	}
	else m_temp = m_input;
	m_op = '+';
	m_input = "";
	dflag = false;
	UpdateData(false);
}
//뺄셈 연산자 입력
void CMFCApplication6Dlg::OnBnClickedButtonSub()
{
	if (m_op != "") {
		double res = calc();
		char rval[100];
		sprintf(rval, "%lf", res);
		m_temp = rval;
	}
	else m_temp = m_input;
	m_op = '-';
	m_input = "";
	dflag = false;
	UpdateData(false);
}
//곱셈 연산자 입력
void CMFCApplication6Dlg::OnBnClickedButtonMul()
{
	if (m_op != "") {
		double res = calc();
		char rval[100];
		sprintf(rval, "%lf", res);
		m_temp = rval;
	}
	else m_temp = m_input;
	m_op = '*';
	m_input = "";
	dflag = false;
	UpdateData(false);
}
//나눗셈 연산자 입력
void CMFCApplication6Dlg::OnBnClickedButtonDiv()
{
	if (m_op != "") {
		double res = calc();
		char rval[100];
		sprintf(rval, "%lf", res);
		m_temp = rval;
	}
	else m_temp = m_input;
	m_op = '/';
	m_input = "";
	dflag = false;
	UpdateData(false);
}
//Mod 연산자 입력
void CMFCApplication6Dlg::OnBnClickedButtonMod()
{
	if (m_op != "") {
		double res = calc();
		char rval[100];
		sprintf(rval, "%lf", res);
		m_temp = rval;
	}
	else m_temp = m_input;
	m_op = '%';
	m_input = "";
	dflag = false;
	UpdateData(false);
}
//n제곱 연산자 입력
void CMFCApplication6Dlg::OnBnClickedButtonPow()
{
	if (m_op != "") {
		double res = calc();
		char rval[100];
		sprintf(rval, "%lf", res);
		m_temp = rval;
	}
	else m_temp = m_input;
	m_op = '^';
	m_input = "";
	dflag = false;
	UpdateData(false);
}
/**********
  계산
***********/
double CMFCApplication6Dlg::calc()
{
	char vchar1[100], vchar2[100];
	wcstombs(vchar1, m_temp, 100);
	wcstombs(vchar2, m_input, 100);

	double fval1 = atof(vchar1);	//m_temp에 입력되어 있는 실수
	double fval2 = atof(vchar2);	//m_input에 입력되어 있는 실수
	double res = 0;	//출력할 결과
	double a = 0.49999;
	double b= 0;
					//m_op에 입력되어 있는 값에 따라 연산
	switch (m_op.GetAt(0)) {
	case '+':
		//c++
		//res = fval1 + fval2;

		//inline assembly
		__asm {
			fld fval1
			fld fval2
			fadd
			fstp res
		}
		break;
	case '-':
		/*fsub:st(1)-st(0)을 하는 명령어
		fval1,fval2를 로드해서 각각 st(1),st(0)에 저장한다.
		fsub 이용해서 뺄셈을 한다.
		st(0)에 저장된 값을 res에 리턴하고 pop한다*/
		__asm{
		fld fval1
		fld fval2
		fsub
		fstp res
		}
		
		break;
	case '*':
		/*fmul:st(1)*st(0)을 하는 명령어
		fval1,fval2를 로드해서 각각 st(1),st(0)에 저장한다.
		fmul 이용해서 곱셈을 한다.
		st(0)에 저장된 값을 res에 리턴하고 pop한다*/
		__asm{
		fld fval1
		fld fval2
		fmul
		fstp res
		}
		
		break;
	case '/':
		/*fdiv:st(1)/st(0)을 하는 명령어
		fval1,fval2를 로드해서 각각 st(1),st(0)에 저장한다.
		fdiv 이용해서 나눗셈을 한다.
		st(0)에 저장된 값을 res에 리턴하고 pop한다*/
		__asm{
		fld fval1
		fld fval2
		fdiv
		fstp res
		}
		
		break;
	case '%':
		/*나머지 연산 논리 : a와 b를 나눈 몫을 구하고 a-b*몫을 구하면 나머지를 구할 수 있다.
		frndint : 정수로 반올림 하는 명령어, 근데 1.5는 반올림 하면 1이 된다.
		fval1,fval2를 로드해서 각각 st(1),st(0)에 저장한다.
		fdiv 이용해서 나눗셈을 한다. fdiv는 몫만 구하는게 아니라 소수점자리까지 나눗셈을 해준다.
		정수부분 몫만 구하기 위해 나눗셈 값에서 소수점 부분을 버리기 위해 미리 선언한 a=0.49999를 fdiv한 값에서 빼준다.
		그래서 나온 값을 frndint하면 버림이 되서 정수부분 몫을 구할 수 있다.
		fval2와 정수부분 몫을 곱하고 fval1을 로드한다.
		fval1-fval2*정수부분 몫을 계산해서 나머지를 구한다.
		st(0)에 저장된 값을 res에 리턴하고 pop한다.
		*/
		__asm{
		fld fval1
		fld fval2
		fdiv
		fld a
		fsub
		frndint
		fld fval2
		fmul 
		fld fval1
		fsub st(0), st(1)
		fstp res
		}
	
		break;
	case '^':
	/* n제곱 연산 논리 : 로그함수를 이용, x^(a+b)=x^a+x^b 임을 이용
	fyl2x: y*log2x
	fist: integer 저장
	fild: integer 로드
	f2xml: 2^x-1
	fxchg: 레지스터 값을 서로 교환
	fscale: ST(1)의 정수를 ST(0)의 지수에 추가.
	fval2,fval1을 로드해서 각각 st(1),st(0)에 저장한다.
	fy12x 이용해서 log2fval2^fval1 형태로 만들어준다.
	st(0)에 있는 값이 0이 아닐 때 그 값을 부호 있는 정수로 바꿔주고 결과를 b에 저장한다.
	(b에 log2fval2^fval1의 정수 부분 저장)
	b를 로드한다.
	st(1)-st(0)을 해준다, st(0)에는 소수 부분만 남음
	f2xml 이용해서 2^(소수부분)-1을 st(0)에 저장한다.
	fld1을 이용해 스택에 1을 푸쉬한다.
	2^소수부분-1+1을 한다.
	저장되어 있는 수 b를 로드한다.
	fxch 이용해서 st(1)에 있는 2^소수부분과 st(0)에 있는 b를 서로 바꾼다.
	fscale 이용해서 st(1)에 있는 정수 값 b를 st(0)의 지수에 추가한다.
	따라서 fval2^fval1 값 출력 가능
	st(0)에 저장된 값을 res에 리턴하고 pop한다.
	*/
		__asm{
	
		fld fval2
		fld fval1
		fyl2x
		fist b
		fild b
		fsub
		f2xm1
		fld1
		fadd
		fild b
		fxch
		fscale
		fstp res
		}
		break;
	default:
		res = fval2;
		break;
	}
	return res;
}
//등호 버튼
void CMFCApplication6Dlg::OnBnClickedButtonEqu()
{
	double res = calc();
	char rval[100];
	sprintf(rval, "%lf", res);
	m_input = rval;

	m_temp = "";
	m_op = "";
	eflag = true;
	dflag = false;

	UpdateData(false);
}





void setBtnColor(CDC  *dc, RECT rect, COLORREF color) {
	dc->FillSolidRect(&rect, color);
	dc->SetBkColor(color);
}


void CMFCApplication6Dlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
#define green RGB(0,200,0)
#define red RGB(200,0,0)
#define aa  RGB(255,217,250)
#define bb RGB(255,108,235)
	CDC dc;
	RECT rect;
	dc.Attach(lpDrawItemStruct->hDC);   
	dc.Draw3dRect(&rect, RGB(255, 255, 255), RGB(0, 0, 0));

	rect = lpDrawItemStruct->rcItem;  
	
	//버튼 색생 변경하기

	if (nIDCtl == IDC_BUTTON_ADD)		//덧셈
	{
		setBtnColor(&dc, rect, green);	//구현 완료 : green
	}
	if (nIDCtl == IDC_BUTTON_SUB)		//뺄셈
	{
		setBtnColor(&dc, rect, green);
	}
	if (nIDCtl == IDC_BUTTON_MUL)		//곱셈
	{
		setBtnColor(&dc, rect, green);
	}	
	if (nIDCtl == IDC_BUTTON_DIV)		//나눗셈
	{
		setBtnColor(&dc, rect, green);
	}
	if (nIDCtl == IDC_BUTTON_MOD)		//MOD
	{
		setBtnColor(&dc, rect, green);
	}
	if (nIDCtl == IDC_BUTTON_ROOT)		//제곱근
	{
		setBtnColor(&dc, rect, green);
	}
	if (nIDCtl == IDC_BUTTON_SQU)		//2제곱
	{
		setBtnColor(&dc, rect, green);
	}
	if (nIDCtl == IDC_BUTTON_POW)		//n제곱
	{
		setBtnColor(&dc, rect, green);
	}
	if (nIDCtl == IDC_BUTTON_LP)		//왼쪽괄호
	{
		setBtnColor(&dc, rect, red);
	}
	if (nIDCtl == IDC_BUTTON_RP)		//오른쪽괄호
	{
		setBtnColor(&dc, rect, red);
	}
	
		//숫자 버튼 색 변경
	if (nIDCtl == IDC_BUTTON1)		
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON2)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON3)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON4)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON5)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON6)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON7)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON8)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON9)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON0)
	{
		setBtnColor(&dc, rect, aa);
	}
	if (nIDCtl == IDC_BUTTON_DOT)
	{
		setBtnColor(&dc, rect, bb);
	}
	if (nIDCtl == IDC_BUTTON_C)
	{
		setBtnColor(&dc, rect, bb);
	}
	if (nIDCtl == IDC_BUTTON_EQU)
	{
		setBtnColor(&dc, rect, bb);
	}
	if (nIDCtl == IDC_BUTTON_DEL)
	{
		setBtnColor(&dc, rect, bb);

	}

	dc.SetTextColor(RGB(255, 255, 255)); // 연산자 텍스트 색상 변경

	UINT state = lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 
	if ((state & ODS_SELECTED))
		dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
	else
		dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);

	TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
	ZeroMemory(buffer, MAX_PATH);     //Intializing the buffer to zero
	::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH); //Get the Caption of Button Window 

	dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//Redraw the  Caption of Button Window 
	dc.Detach();  // Detach the Button DC
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);

}
