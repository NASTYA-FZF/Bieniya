
// BieniyaDlg.cpp: файл реализации
//

#include "pch.h"
#define _USE_MATH_DEFINES
#include "framework.h"
#include "Bieniya.h"
#include "BieniyaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CBieniyaDlg



CBieniyaDlg::CBieniyaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BIENIYA_DIALOG, pParent)
	, Omega(100)
	, dOmega(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBieniyaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, MyPicture);
	DDX_Text(pDX, IDC_EDIT1, Omega);
	DDX_Text(pDX, IDC_EDIT3, dOmega);
}

BEGIN_MESSAGE_MAP(CBieniyaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DRAW, &CBieniyaDlg::OnBnClickedDraw)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ANIMATION, &CBieniyaDlg::OnBnClickedAnimation)
END_MESSAGE_MAP()


// Обработчики сообщений CBieniyaDlg

BOOL CBieniyaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	fi = 0.;
	animation = false;
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CBieniyaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CBieniyaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBieniyaDlg::OnBnClickedDraw()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	MyPicture.my_func = Func_bieniya(Omega, dOmega, MyPicture.maxY, MyPicture.minY, MyPicture.maxX, MyPicture.minX, MyPicture.stepX);
	MyPicture.Invalidate(FALSE);
}

std::vector<double> CBieniyaDlg::Func_bieniya(double omega, double delta_omega, double& maxF, double& minF, double& maxX, double& minX, double& step)
{
	step = 0.001;
	int iter = 0;
	minX = 0.;
	maxX = 4 * M_PI / delta_omega;
	std::vector<double> func;
	for (double x = 0.; x < maxX; x += step)
	{
		func.push_back(cos(omega * x + fi) + cos((omega + delta_omega) * x));
		if (maxF < func[iter]) maxF = func[iter];
		if (minF > func[iter]) minF = func[iter];
		iter++;
	}
	return func;
}


void CBieniyaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	UpdateData(TRUE);
	fi += 0.1;
	MyPicture.my_func = Func_bieniya(Omega, dOmega, MyPicture.maxY, MyPicture.minY, MyPicture.maxX, MyPicture.minX, MyPicture.stepX);
	MyPicture.Invalidate(FALSE);
}


void CBieniyaDlg::OnBnClickedAnimation()
{
	// TODO: добавьте свой код обработчика уведомлений
	animation = !animation;
	if (animation) timer = SetTimer(1, 100, NULL);
	else KillTimer(timer);
}
