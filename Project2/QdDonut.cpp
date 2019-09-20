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

	this->pointsIn[0].x = 50;
	this->pointsIn[0].y = 50;
	this->pointsIn[0].x = 100;
	this->pointsIn[0].y = 50;
	this->pointsIn[0].x = 100;
	this->pointsIn[0].y = 100;
	this->pointsIn[0].x = 50;
	this->pointsIn[0].y = 100;
	PEN qd_pen();
	PEN qd_penIn();
	BRUSH qd_brush();
}
QuadrangleDonut::QuadrangleDonut(DRAW_TYPE type, POINT* points, POINT* pointsIn, PEN qd_pen, PEN qd_penIn, BRUSH qd_brush)
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
	this->qd_pen = qd_pen;
	this->qd_penIn = qd_penIn;
	this->qd_brush = qd_brush;
}
void QuadrangleDonut::Draw()
{

}
DRAW_TYPE QuadrangleDonut::GetType()
{
	return type;
}
void QuadrangleDonut::SetType(DRAW_TYPE type)
{
	this->type = type;
}
POINT* QuadrangleDonut::GetPoint()
{
	return points;
}
void QuadrangleDonut::SetPoint(POINT* points)
{
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
}
PEN QuadrangleDonut::GetPen()
{
	return qd_pen;
}
void QuadrangleDonut::SetPen(char* name, int width, COLORREF color)
{
	this->qd_pen = PEN(name, width, color);
}
PEN QuadrangleDonut::GetPenIn()
{
	return qd_penIn;
}
void QuadrangleDonut::SetPen(char* name, int width, COLORREF color)
{
	this->qd_penIn = PEN(name, width, color);
}
BRUSH QuadrangleDonut::GetBrush()
{
	return qd_brush;
}
void QuadrangleDonut::SetBrush(char* name, COLORREF color)
{
	this->qd_brush = BRUSH(name, color);
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



void QuadrangleDonut::Draw(HDC hdc, HWND hwnd, Quadrangle quad, Quadrangle quad2)
{
	try
	{
		CheckConvex(quad);
		CheckInFrame(hwnd, quad);

		CheckConvex(quad2);
		CheckIncluded(quad, quad2);
	}
	catch (ERROR error)
	{
		return PrintError(error);
	}

	//Creating pen
	HPEN newPen;
	try
	{
		newPen = CreatePen(StringToPenStyle(quad.qd_pen.name), quad.qd_pen.width, quad.qd_pen.color);
	}
	catch (ERROR error)
	{
		return PrintError(error);
	}
	HPEN oldPen = SelectPen(hdc, newPen);

	HBRUSH newBrush;
	HBRUSH oldBrush;

	//Creating brush
	if (strcmp(quad.qd_brush.name, "SOLID") == 0)
	{
		newBrush = CreateSolidBrush(quad.qd_brush.color);
	}
	else
	{
		try
		{
			newBrush = CreateHatchBrush(StringToBrushHash(quad.qd_brush.name), quad.qd_brush.color);
		}
		catch (ERROR error)
		{
			return PrintError(error);
		}
	}
	oldBrush = SelectBrush(hdc, newBrush);

	Polygon(hdc, quad.points, 4);

	//Creating pen
	try
	{
		newPen = CreatePen(StringToPenStyle(quad2.qd_pen.name), quad2.qd_pen.width, quad2.qd_pen.color);
	}
	catch (ERROR error)
	{
		return PrintError(error);
	}
	oldPen = SelectPen(hdc, newPen);

	//Creating brush
	newBrush = CreateSolidBrush(GetBkColor(hdc));
	oldBrush = SelectBrush(hdc, newBrush);

	Polygon(hdc, quad2.points, 4);

}


void QuadrangleDonut::PrintError(ERROR error)
{
	switch (error)
	{
	case INCORRECT_DRAW_TYPE:
	{
		printf("Неверно задан тип фигуры\n");
		break;
	}
	case INCORRECT_BRUSH:
	{
		printf("Неверно задан тип кисти\n");
		break;
	}
	case INCORRECT_PEN_STYLE:
	{
		printf("Неверно задан тип пера\n");
		break;
	}
	case OUT_FRAME:
	{
		printf("Координаты фигуры не входят в рамки окна\n");
		break;
	}
	case NOT_INCLUDED:
	{
		printf("Второй четырехугольник не вложен в первый\n");
		break;
	}
	case NOT_CONVEX:
	{
		printf("Координаты не удовлетворют условию выпуклого четырехугольника\n");
		break;
	}
	case THREE_POINTS_IN_LINE:
	{
		printf("В заданных кооринатах три точки лежат на одной прямой\n");
		break;
	}
	}

	_getch();
}
void QuadrangleDonut::CheckConvex(Quadrangle quad)
{
	if (!IsPoint(quad.points[0], quad.points[1], quad.points[2], quad.points[3])
		|| !IsPoint(quad.points[1], quad.points[2], quad.points[3], quad.points[0])
		|| !IsPoint(quad.points[2], quad.points[3], quad.points[0], quad.points[1])
		|| !IsPoint(quad.points[3], quad.points[0], quad.points[1], quad.points[2]))
	{
		throw NOT_CONVEX;
	}
}
void QuadrangleDonut::CheckInFrame(HWND hwnd, Quadrangle qd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	for (int i = 0; i < 4; i++)
	{
		if (qd.points[i].x > rt.right || qd.points[i].y > rt.bottom || qd.points[i].x < 0 || qd.points[i].y < 0)
		{
			throw OUT_FRAME;
		}
	}
}
void QuadrangleDonut::CheckIncluded(Quadrangle quad1, Quadrangle quad2)
{
	for (int i = 0; i < 4; i++)
	{
		if (!IsInQuadrangle(quad1.points[0], quad1.points[1], quad1.points[2], quad1.points[3], quad2.points[i]))
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