
// BieniyaDlg.h: файл заголовка
//

#pragma once
#include <math.h>
#include "MyGraph.h"

// Диалоговое окно CBieniyaDlg
class CBieniyaDlg : public CDialogEx
{
// Создание
public:
	CBieniyaDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BIENIYA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDraw();
	MyGraph MyPicture;
	std::vector<double> Func_bieniya(double omega, double delta_omega, double& maxF, double& minF, double& maxX, double& minX, double& step);
	double Omega;
	double dOmega;
	double fi;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedAnimation();
	bool animation;
	UINT timer;
};
