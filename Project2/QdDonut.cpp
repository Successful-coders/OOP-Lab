#include "QdDonut.h"
QuadrangleDonut::QuadrangleDonut()
{
	
	this->points[0].x = 50;
	this->points[0].y = 50;
	this->points[1].x = 100;
	this->points[1].y = 50;
	this->points[2].x = 100;
	this->points[2].y = 100;
	this->points[3].x = 50;
	this->points[3].y = 100;

	POINT* point;
	for (int i = 0; i < 4; i++)
	{
		point[i].x = 0;
		point[i].y = 0;
	}
	In.SetPoint(point);
	Pen qd_pen();
	Pen qd_penIn();
	Brush qd_brush();
}
QuadrangleDonut::QuadrangleDonut(POINT* points, POINT* pointsIn, Pen qd_pen, Pen qd_penIn, Brush qd_brush)
{
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
	Brush brushBlack = Brush();
	In = QuadrangleShaded(pointsIn, qd_penIn, brushBlack);
	//In.SetPoint(pointsIn);
	this->pen = qd_pen;
	//In->pen = qd_penIn;
	this->brush = qd_brush;
}

//POINT *QuadrangleDonut::GetPointIn()
//{
//	return pointsIn;
//}
//
//void QuadrangleDonut::SetPointIn(POINT* points)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		this->points[i] = points[i];
//	}
//}

//Pen QuadrangleDonut::GetPenIn()
//{
//	return penIn;
//}
//
//void QuadrangleDonut::SetPenIn(char* name, int width, COLORREF color)
//{
//	this->penIn = Pen(name, width, color);
//}



void QuadrangleDonut::Draw(HWND hwnd)
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
	HDC hdc = GetDC(hwnd);
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
	newPen ;
	Pen Inpen = In.GetPen();
	try
	{
		newPen = CreatePen(StringToPenStyle(Inpen.GetName()),Inpen.GetWidth(), Inpen.GetColor());
	}
	catch (ERROR error)
	{
		return Error::PrintError(error);
	}
	oldPen = SelectPen(hdc, newPen);

	//Creating brush
	newBrush = CreateSolidBrush(RGB(0,0,0));
	oldBrush = SelectBrush(hdc, newBrush);

	Polygon(hdc, In.GetPoint(), 4);

}

void QuadrangleDonut::Move(HWND hwnd, int x, int y)
{
	DeleteAll(hwnd);
	for (int i = 0; i < 4; i++)
	{
		points[i].x += x;
		points[i].y += y;
	}
		In.Move(hwnd, x, y);

	HWND newhwnd = GetConsoleWindow();
	Draw(newhwnd);
}


void QuadrangleDonut::Save(FILE* saveFile)
{
	

	fprintf(saveFile, "%s\n", "DONUT");
	for (int i = 0; i < 4; i++)
	{
		fprintf(saveFile, "%d %d\n", points[i].x, points[i].y);
	}
	fprintf(saveFile, "%s\n", pen.GetName());
	fprintf(saveFile, "%d\n", pen.GetWidth());
	fprintf(saveFile, "%d %d %d\n", GetRValue(pen.GetColor()), GetGValue(pen.GetColor()), GetBValue(pen.GetColor()));
	fprintf(saveFile, "%s\n", brush.GetName());
	fprintf(saveFile, "%d %d %d\n", GetRValue(brush.GetColor()), GetGValue(brush.GetColor()), GetBValue(brush.GetColor()));
	In.Save(saveFile);

}
void QuadrangleDonut::CheckConvex2()
{
	if (!IsPoint(In.GetPoint()[0], In.GetPoint()[1], In.GetPoint()[2], In.GetPoint()[3])
		|| !IsPoint(In.GetPoint()[1], In.GetPoint()[2], In.GetPoint()[3], In.GetPoint()[0])
		|| !IsPoint(In.GetPoint()[2], In.GetPoint()[3], In.GetPoint()[0], In.GetPoint()[1])
		|| !IsPoint(In.GetPoint()[3], In.GetPoint()[0], In.GetPoint()[1], In.GetPoint()[2]))
	{
		throw NOT_CONVEX;
	}

}

void QuadrangleDonut::CheckIncluded()
{
	for (int i = 0; i < 4; i++)
	{
		if (!IsInQuadrangle(GetPoint()[0], GetPoint()[1], GetPoint()[2], GetPoint()[3], In.GetPoint()[i]))
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
