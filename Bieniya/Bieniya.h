
// Bieniya.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CBieniyaApp:
// Сведения о реализации этого класса: Bieniya.cpp
//

class CBieniyaApp : public CWinApp
{
public:
	CBieniyaApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CBieniyaApp theApp;
