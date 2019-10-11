#include "QdCountour.h"

using namespace std;
QuadrangleContour::QuadrangleContour()
{
	this->points[0].x = 50;
	this->points[0].y = 50;
	this->points[0].x = 100;
	this->points[0].y = 50;
	this->points[0].x = 100;
	this->points[0].y = 100;
	this->points[0].x = 50;
	this->points[0].y = 100;
	Pen qd_pen();
	Brush qd_brush();
}
QuadrangleContour::QuadrangleContour(POINT* points, Pen qd_pen)
{
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
	this->pen = qd_pen;
	
}
POINT* QuadrangleContour::GetPoint()
{
	return points;
}
void QuadrangleContour::SetPoint(POINT* points)
{
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
}
Pen QuadrangleContour:: GetPen()
{
	return pen;
}
void QuadrangleContour:: SetPen(char* name, int width, COLORREF color)
{
	this->pen = Pen(name, width, color);
}


int QuadrangleContour::StringToBrushHash(const char string[])
{
	if (strcmp(string, "HS_BDIAGONAL") == 0)
	{
		return HS_BDIAGONAL;
	}
	else if (strcmp(string, "HS_CROSS") == 0)
	{
		return HS_CROSS;
	}
	else if (strcmp(string, "HS_DIAGCROSS") == 0)
	{
		return HS_DIAGCROSS;
	}
	else if (strcmp(string, "HS_FDIAGONAL") == 0)
	{
		return HS_FDIAGONAL;
	}
	else if (strcmp(string, "HS_HORIZONTAL") == 0)
	{
		return HS_HORIZONTAL;
	}
	else if (strcmp(string, "HS_VERTICAL") == 0)
	{
		return HS_VERTICAL;
	}
	else
	{
		throw INCORRECT_BRUSH;
	}
}
int QuadrangleContour::StringToPenStyle(const char string[])
{
	if (strcmp(string, "PS_SOLID") == 0)
	{
		return PS_SOLID;
	}
	else if (strcmp(string, "PS_DASH") == 0)
	{
		return PS_DASH;
	}
	else if (strcmp(string, "PS_DOT") == 0)
	{
		return PS_DOT;
	}
	else if (strcmp(string, "PS_DASHDOT") == 0)
	{
		return PS_DASHDOT;
	}
	else if (strcmp(string, "PS_DASHDOTDOT") == 0)
	{
		return PS_DASHDOTDOT;
	}
	else if (strcmp(string, "PS_NULL") == 0)
	{
		return PS_NULL;
	}
	else if (strcmp(string, "PS_INSIDEFRAME") == 0)
	{
		return PS_INSIDEFRAME;
	}
	else
	{
		throw INCORRECT_PEN_STYLE;
	}
}



void QuadrangleContour::Draw(HWND hwnd)
{
	try
	{
		CheckConvex();
		CheckInFrame(hwnd);
	}
	catch (ERROR error)
	{
		return Error::PrintError(error);
	}

	//Creating pen
	HPEN newPen;
	try
	{
		newPen = CreatePen(StringToPenStyle(pen.GetName()), pen.GetWidth(), pen.GetColor());
	}
	catch (ERROR error)
	{
		return Error::PrintError(error);
	}
	HDC hdc = GetDC(hwnd);
	HPEN oldPen = SelectPen(hdc, newPen);

	//Creating brush
	HBRUSH newBrush = GetStockBrush(NULL_BRUSH);
	HBRUSH oldBrush = SelectBrush(hdc, newBrush);

	Polygon(hdc, points, 4);

}
void QuadrangleContour::Move(HWND hwnd, int x, int y)
{
	DeleteAll(hwnd);
	for (int i = 0; i < 4; i++)
	{
		points[i].x += x;
		points[i].y += y;
	}

	HWND newhwnd = GetConsoleWindow();
	Draw(newhwnd);
}
void QuadrangleContour::Save(const char* fileName)
{
	FILE* saveFile = fopen(fileName, "w");

	fprintf(saveFile, "%s\n", "CONTOUR");
	for (int i = 0; i < 4; i++)
	{
		fprintf(saveFile, "%d %d\n", points[i].x, points[i].y);
	}
	fprintf(saveFile, "%s\n", pen.GetName());
	fprintf(saveFile, "%d\n", pen.GetWidth());
	fprintf(saveFile, "%d %d %d\n", GetRValue(pen.GetColor()), GetGValue(pen.GetColor()), GetBValue(pen.GetColor()));

	fclose(saveFile);
}
void QuadrangleContour::CheckConvex()
{
	if (!IsPoint(GetPoint()[0],GetPoint()[1],GetPoint()[2],GetPoint()[3])
		|| !IsPoint(GetPoint()[1],GetPoint()[2],GetPoint()[3],GetPoint()[0])
		|| !IsPoint(GetPoint()[2],GetPoint()[3],GetPoint()[0],GetPoint()[1])
		|| !IsPoint(GetPoint()[3],GetPoint()[0],GetPoint()[1], GetPoint()[2]))
	{
		throw NOT_CONVEX;
	}
}
void QuadrangleContour::CheckInFrame(HWND hwnd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	for (int i = 0; i < 4; i++)
	{
		if (points[i].x > rt.right || points[i].y > rt.bottom || points[i].x < 0 || points[i].y < 0)
		{
			throw OUT_FRAME;
		}
	}
}
void QuadrangleContour::DeleteAll(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	RECT rt;
	GetClientRect(hwnd, &rt);
	POINT ppt[2];
	ppt[0].x = 0;
	ppt[0].y = 0;
	ppt[1].x = rt.right;
	ppt[1].y = rt.bottom;
	HPEN newPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	HPEN oldPen = SelectPen(hdc, newPen);
	HBRUSH newBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = SelectBrush(hdc, newBrush);
	Rectangle(hdc, ppt[0].x, ppt[0].y, ppt[1].x, ppt[1].y);
}

bool QuadrangleContour::IsPoint(POINT k1, POINT k2, POINT k3, POINT k4)
{
	if (k1.x - k2.x)
	{
		float k;
		k = (float)(k1.y - k2.y) / (float)(k1.x - k2.x);
		float b = k1.y - k * k1.x;
		float y1 = k * k3.x + b;
		float y2 = k * k4.x + b;
		if (y1 == k3.y || y2 == k4.y)
		{
			throw THREE_POINTS_IN_LINE;
		}
		if ((y1 > (float)k3.y && y2 > (float)k4.y) || (y1 < (float)k3.y && y2 < (float)k4.y))
		{
			return true;
		}
		else
		{
			throw NOT_CONVEX;
		}
	}
	else
	{
		if (k3.x == k1.x || k4.x == k1.x)
		{
			throw THREE_POINTS_IN_LINE;
		}
		if ((k1.x > k3.x && k2.x > k4.x) || (k1.x < k3.x && k2.x < k4.x))
		{
			return true;
		}
		else
		{
			throw NOT_CONVEX;
		}
	}
}