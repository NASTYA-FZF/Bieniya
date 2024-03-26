// MyGraph.cpp: файл реализации
//

#include "pch.h"
#include "Bieniya.h"
#include "MyGraph.h"
using namespace Gdiplus;

// MyGraph

IMPLEMENT_DYNAMIC(MyGraph, CStatic)

MyGraph::MyGraph()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&token, &input, NULL);
	on_off = true;
	maxY = 0.;
	minY = 0.;
	maxX = 0.;
	minX = 0.;
	if (s != Ok)
	{
		MessageBox(L"Не удалось нарисовать", L"Ошибка", NULL);
	}
}

MyGraph::~MyGraph()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(MyGraph, CStatic)
END_MESSAGE_MAP()



// Обработчики сообщений MyGraph




void MyGraph::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  Добавьте исходный код для отображения указанного элемента
	if (on_off)
	{
		on_off = false;
	}
	else
	{
		Graphics wnd(lpDrawItemStruct->hDC);
		Bitmap buffer(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &wnd);
		Graphics draw_in_buffer(&buffer);
		draw_in_buffer.SetSmoothingMode(SmoothingModeAntiAlias);
		draw_in_buffer.Clear(Color(255, 255, 255, 255));

		double otstup = 50.;

		RectF rect_graph(
			otstup,
			otstup,
			lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left - 2 * otstup,
			lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - 2 * otstup
		);

		draw_in_buffer.TranslateTransform(otstup, (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) / 2);
		double Xscale = rect_graph.Width / (maxX - minX);
		double Yscale = rect_graph.Height / (maxY - minY);
		draw_in_buffer.ScaleTransform(Xscale, -Yscale);

		Pen pen_ortho(Color(255, 0, 0, 0), 0.001);

		draw_in_buffer.DrawLine(&pen_ortho, PointF(minX, minY), PointF(minX, maxY));
		draw_in_buffer.DrawLine(&pen_ortho, PointF(minX, minY), PointF(maxX, minY));

		Pen pen_network(Color(255, 220, 220, 220), 0.001);

		int num = 12;
		double step_ver_network = (maxX - minX) / num;
		double step_hor_network = (maxY - minY) / num;

		int iter = 1;
		double x = minX;
		for (int i = 0; i < num; i++)
		{
			draw_in_buffer.DrawLine(&pen_network, PointF(minX + (i + 1) * step_ver_network, minY), PointF(minX + (i + 1) * step_ver_network, maxY));
			draw_in_buffer.DrawLine(&pen_network, PointF(minX, minY + (i + 1) * step_hor_network), PointF(maxX, minY + (i + 1) * step_hor_network));
		}

		Pen pen_graph(Color(255, 30, 144, 255), 0.001);

		iter = 1;

		for (x = minX + stepX; x < maxX; x += stepX)
		{
			draw_in_buffer.DrawLine(&pen_graph, PointF((x - stepX), my_func[iter - 1]), PointF(x, my_func[iter]));
			iter++;
		}

		draw_in_buffer.ScaleTransform(1 / Xscale, -1 / Yscale);

		FontFamily my_font_family(L"Arial");
		Gdiplus::Font my_font(&my_font_family, 14, FontStyleRegular, UnitPixel);
		SolidBrush brush_font(Color(255, 0, 0, 0));

		x = minX;
		double y = minY;
		wchar_t podpis_ortho[10];
		for (int i = 0; i < num + 1; i++)
		{
			swprintf_s(podpis_ortho, L"%.1f", x);
			draw_in_buffer.DrawString(podpis_ortho, -1, &my_font, PointF(x * Xscale - 10., rect_graph.Height / 2), &brush_font);
			x += step_ver_network;

			swprintf_s(podpis_ortho, L"%.1f", y);
			draw_in_buffer.DrawString(podpis_ortho, -1, &my_font, PointF(minX - 35., -y * Yscale - 10.), &brush_font);
			y += step_hor_network;
		}

		wnd.DrawImage(&buffer, 0, 0, 0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, UnitPixel);
	}
}
