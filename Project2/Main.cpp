//Main.cpp
#include "QD.h"
#include "QdCountour.h"
#include "QdDonut.h"
#include "QdShaded.h"



DRAW_TYPE StringToEnum(const char string[])
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

void PrintError(ERROR error)
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

void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	FILE* file = fopen("test.txt", "r");
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));

	POINT ppt[4];
	char PenName[16];
	int PenWidth;
	COLORREF PenColor;
	DRAW_TYPE TypeDraw;
	char type[15];
	fscanf(file, "%s", &type);
	try
	{
		TypeDraw = StringToEnum(type);
	}
	catch (ERROR error)
	{
		return Error::PrintError(error);
	}

	for (int i = 0; i < 4; i++)
	{
		fscanf(file, "%d %d", &(ppt[i].x), &(ppt[i].y));
	}

	fscanf(file, "%s", &(PenName));
	fscanf(file, "%d", &(PenWidth));
	int Red, Green, Blue;
	fscanf(file, "%i %i %i", &Red, &Green, &Blue);
	PenColor = RGB(Red, Green, Blue);
	Pen pen = Pen(PenName, PenWidth, PenColor);

	switch (TypeDraw)
	{
	case CONTOUR:
	{
		QuadrangleContour quad = QuadrangleContour(ppt, pen);
		quad.Draw(hdc, hwnd);
		break;
	}
	case SHADED:
	{
		char brushName[45];
		fscanf(file, "%s", &(brushName));
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		COLORREF brushColor = RGB(Red, Green, Blue);
		Brush brush = Brush(brushName, brushColor);

		QuadrangleShaded quad = QuadrangleShaded(ppt, pen, brush);
		quad.Draw(hdc, hwnd);
		break;
	}
	case DONUT:
	{
		char brushName[45];
		fscanf(file, "%s", &(brushName));
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		COLORREF brushColor = RGB(Red, Green, Blue);
		Brush brush = Brush(brushName, brushColor);

		POINT pptIn[4];
		for (int i = 0; i < 4; i++)
		{
			fscanf(file, "%d %d", &(pptIn[i].x), &(pptIn[i].y));
		}

		fscanf(file, "%s", &(PenName));
		fscanf(file, "%d", &(PenWidth));
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		PenColor = RGB(Red, Green, Blue);
		Pen penIn = Pen(PenName, PenWidth, PenColor);
		
		Brush brushIn = Brush("NULL_BRUSH");

		QuadrangleDonut quad = QuadrangleDonut(ppt, pptIn, pen, penIn, brush);
		quad.Draw(hdc, hwnd);
		break;
	}
	}
	fclose(file);
	_getch();
}

