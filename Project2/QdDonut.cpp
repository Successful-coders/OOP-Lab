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




void QuadrangleDonut::Draw(HWND hwnd)
{
	try
	{
		CheckConvex();
		CheckInFrame(hwnd);

		In.CheckConvex();
		CheckIncluded();
	}
	catch (ERROR error)
	{
		return Error::PrintError(error);
	}

	//Creating pen
	QuadrangleShaded::Draw(hwnd);
	
	In.Draw(hwnd);
	

}

void QuadrangleDonut::Move(HWND hwnd, int x, int y)
{
	DeleteAll(hwnd);
	QuadrangleShaded::Move(hwnd, x, y);
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
