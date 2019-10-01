#include "QdDonut.h"
QuadrangleDonut::QuadrangleDonut()
{
	this->type = CONTOUR;
	this->points[0].x = 50;
	this->points[0].y = 50;
	this->points[0].x = 100;
	this->points[0].y = 50;
	this->points[0].x = 100;
	this->points[0].y = 100;
	this->points[0].x = 50;
	this->points[0].y = 100;

	this->pointsIn[0].x = 25;
	this->pointsIn[0].y = 25;
	this->pointsIn[0].x = 50;
	this->pointsIn[0].y = 25;
	this->pointsIn[0].x = 50;
	this->pointsIn[0].y = 50;
	this->pointsIn[0].x = 25;
	this->pointsIn[0].y = 50;
	Pen qd_pen();
	Pen qd_penIn();
	Brush qd_brush();
}
QuadrangleDonut::QuadrangleDonut(POINT* points, POINT* pointsIn, Pen qd_pen, Pen qd_penIn, Brush qd_brush)
{
	this->type = type;
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
	for (int i = 0; i < 4; i++)
	{
		this->pointsIn[i] = pointsIn[i];
	}
	this->pen = qd_pen;
	this->penIn = qd_penIn;
	this->brush = qd_brush;
}

POINT *QuadrangleDonut::GetPoint()
{
	return points;
}
POINT *QuadrangleDonut::GetPointIn()
{
	return pointsIn;
}
void QuadrangleDonut::SetPoint(POINT* points)
{
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
}
void QuadrangleDonut::SetPointIn(POINT* points)
{
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
}
Pen QuadrangleDonut::GetPen()
{
	return pen;
}
void QuadrangleDonut::SetPen(char* name, int width, COLORREF color)
{
	this->pen = Pen(name, width, color);
}
Pen QuadrangleDonut::GetPenIn()
{
	return penIn;
}
void QuadrangleDonut::SetPenIn(char* name, int width, COLORREF color)
{
	this->penIn = Pen(name, width, color);
}
Brush QuadrangleDonut::GetBrush()
{
	return brush;
}
void QuadrangleDonut::SetBrush(char* name, COLORREF color)
{
	this->brush = Brush(name, color);
}

DRAW_TYPE QuadrangleDonut::StringToEnum(const char string[])
{
	if (strcmp(string, "CONTOUR") == 0)
	{
		return CONTOUR;
	}
	else if (strcmp(string, "SHADED") == 0)
	{
		return SHADED;
	}
	else if (strcmp(string, "DONUT") == 0)
	{
		return DONUT;
	}
	else
	{
		throw INCORRECT_DRAW_TYPE;
	}
}
int QuadrangleDonut::StringToBrushHash(const char string[])
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
int QuadrangleDonut::StringToPenStyle(const char string[])
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



void QuadrangleDonut::Draw(HDC hdc, HWND hwnd)
{
	try
	{
		CheckConvex();
		CheckInFrame(hwnd);

		CheckConvex2();
		CheckIncluded();
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
	HPEN oldPen = SelectPen(hdc, newPen);

	HBRUSH newBrush;
	HBRUSH oldBrush;

	//Creating brush
	if (strcmp(brush.GetName(), "SOLID") == 0)
	{
		newBrush = CreateSolidBrush(brush.GetColor());
	}
	else
	{
		try
		{
			newBrush = CreateHatchBrush(StringToBrushHash(brush.GetName()), brush.GetColor());
		}
		catch (ERROR error)
		{
			return Error::PrintError(error);
		}
	}
	oldBrush = SelectBrush(hdc, newBrush);

	Polygon(hdc, GetPoint(), 4);

	//Creating pen
	newPen;
	try
	{
		newPen = CreatePen(StringToPenStyle(penIn.GetName()), penIn.GetWidth(), penIn.GetColor());
	}
	catch (ERROR error)
	{
		return Error::PrintError(error);
	}
	oldPen = SelectPen(hdc, newPen);

	//Creating brush
	newBrush = CreateSolidBrush(RGB(0,0,0));
	oldBrush = SelectBrush(hdc, newBrush);

	Polygon(hdc, GetPointIn(), 4);

}

void QuadrangleDonut::Move(HWND hwnd, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		points[i].x += x;
		points[i].y += y;
		pointsIn[i].x += x;
		pointsIn[i].y += y;
	}
	//ReleaseDC(hwnd, hdc);
	HWND newhwnd = GetConsoleWindow();
	HDC newhdc = GetDC(hwnd);
	Draw(newhdc, newhwnd);
}
void QuadrangleDonut::CheckConvex()
{
	if (!IsPoint(GetPoint()[0], GetPoint()[1], GetPoint()[2], GetPoint()[3])
		|| !IsPoint(GetPoint()[1], GetPoint()[2], GetPoint()[3], GetPoint()[0])
		|| !IsPoint(GetPoint()[2], GetPoint()[3], GetPoint()[0], GetPoint()[1])
		|| !IsPoint(GetPoint()[3], GetPoint()[0], GetPoint()[1], GetPoint()[2]))
	{
		throw NOT_CONVEX;
	}
}

void QuadrangleDonut::CheckConvex2()
{
	if (!IsPoint(GetPointIn()[0], GetPointIn()[1], GetPointIn()[2], GetPointIn()[3])
		|| !IsPoint(GetPointIn()[1], GetPointIn()[2], GetPointIn()[3], GetPointIn()[0])
		|| !IsPoint(GetPointIn()[2], GetPointIn()[3], GetPointIn()[0], GetPointIn()[1])
		|| !IsPoint(GetPointIn()[3], GetPointIn()[0], GetPointIn()[1], GetPointIn()[2]))
	{
		throw NOT_CONVEX;
	}
}
void QuadrangleDonut::CheckInFrame(HWND hwnd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	for (int i = 0; i < 4; i++)
	{
		if (GetPoint()[i].x > rt.right || GetPoint()[i].y > rt.bottom || GetPoint()[i].x < 0 || GetPoint()[i].y < 0)
		{
			throw OUT_FRAME;
		}
	}
}
void QuadrangleDonut::CheckIncluded()
{
	for (int i = 0; i < 4; i++)
	{
		if (!IsInQuadrangle(GetPoint()[0], GetPoint()[1], GetPoint()[2], GetPoint()[3], GetPointIn()[i]))
		{
			throw NOT_INCLUDED;
		}
	}
}
bool QuadrangleDonut::IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest)
{
	int a = (P1.x - PTest.x) * (P2.y - P1.y) - (P2.x - P1.x) * (P1.y - PTest.y);
	int b = (P2.x - PTest.x) * (P3.y - P2.y) - (P3.x - P2.x) * (P2.y - PTest.y);
	int c = (P3.x - PTest.x) * (P4.y - P3.y) - (P4.x - P3.x) * (P3.y - PTest.y);
	int d = (P4.x - PTest.x) * (P1.y - P4.y) - (P1.x - P4.x) * (P4.y - PTest.y);

	if ((a >= 0 && b >= 0 && c >= 0 && d >= 0) || (a <= 0 && b <= 0 && c <= 0 && d <= 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool QuadrangleDonut::IsPoint(POINT k1, POINT k2, POINT k3, POINT k4)
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