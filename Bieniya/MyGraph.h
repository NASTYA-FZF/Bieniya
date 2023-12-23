#pragma once
#include <gdiplus.h>
#include <vector>

// MyGraph

class MyGraph : public CStatic
{
	DECLARE_DYNAMIC(MyGraph)

public:
	MyGraph();
	virtual ~MyGraph();

protected:
	DECLARE_MESSAGE_MAP()

public:
	ULONG_PTR token;
	std::vector<double> my_func;
	bool on_off;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	double maxX, maxY;
	double minX, minY;
	double stepX;
};


