#include "QdShaded.h"

QuadrangleShaded::QuadrangleShaded()
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
QuadrangleShaded::QuadrangleShaded(POINT* points, Pen qd_pen, Brush qd_brush)
{
	for (int i = 0; i < 4; i++)
	{
		this->points[i] = points[i];
	}
	this->pen = qd_pen;
	this->brush = qd_brush;
}
Brush QuadrangleShaded::GetBrush()
{
	return brush;
}
void QuadrangleShaded::SetBrush(char* name, COLORREF color)
{
	this->brush = Brush(name, color);
}
int QuadrangleShaded::StringToBrushHash(const char string[])
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

void QuadrangleShaded::Draw(HWND hwnd)
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

	HBRUSH newBrush;
	HBRUSH oldBrush;

	//Creating brush
	newBrush;;
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

}
void QuadrangleShaded::Save(FILE* saveFile)
{
	

	fprintf(saveFile, "%s\n", "SHADED");
	for (int i = 0; i < 4; i++)
	{
		fprintf(saveFile, "%d %d\n", points[i].x, points[i].y);
	}
	fprintf(saveFile, "%s\n", pen.GetName());
	fprintf(saveFile, "%d\n", pen.GetWidth());
	fprintf(saveFile, "%d %d %d\n", GetRValue(pen.GetColor()), GetGValue(pen.GetColor()), GetBValue(pen.GetColor()));
	fprintf(saveFile, "%s\n", brush.GetName());
	fprintf(saveFile, "%d %d %d\n", GetRValue(brush.GetColor()), GetGValue(brush.GetColor()), GetBValue(brush.GetColor()));


}