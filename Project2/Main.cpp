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
		return PrintError(error);
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

	PEN pen;

	switch (TypeDraw)
	{
	case CONTOUR:
	{
		QuadrangleContour Quad;
		PEN pen;
		BRUSH brush;
		/*pen.SetName(PenName);
		pen.SetWidth(PenWidth);
		pen.SetColor(PenColor);
		brush.SetColor(RGB(0, 0, 0));*/
		pen.PEN(PenName, PenWidth, PenColor);
		Quad.QuadrangleContour(TypeDraw, ppt, pen, brush);
		break;
	}

	case SHADED:
	{
		fscanf(file, "%s", &quad->qd_brush.name);

		int Red, Green, Blue;
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		quad->qd_brush.color = RGB(Red, Green, Blue);
		break;
	}

	case DONUT:
	{
		fscanf(file, "%s", &quad->qd_brush.name);

		int Red, Green, Blue;
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		quad->qd_brush.color = RGB(Red, Green, Blue);

		for (int i = 0; i < 4; i++)
			fscanf(file, "%d %d", &(quad2->points[i].x), &(quad2->points[i].y));

		fscanf(file, "%s", &quad2->qd_pen.name);

		fscanf(file, "%d", &quad2->qd_pen.width);

		int Red2, Green2, Blue2;
		fscanf(file, "%i %i %i", &Red2, &Green2, &Blue2);
		quad2->qd_pen.color = RGB(Red2, Green2, Blue2);

		memcpy(quad2->qd_brush.name, "SOLID", 11);
		quad2->qd_brush.color = GetBkColor(hdc);
		break;
	}
	}

	
	fclose(file);

	do
	{
		switch (quad.type)
		{
		case CONTOUR:
		{
			DrawContour(hdc, hwnd);

			break;
		}
		case SHADED:
		{

			DrawShaded(hdc, hwnd);

			break;
		}
		case DONUT:
		{

			DrawDonut(hdc, hwnd);
			break;
		}
		}
	} while (getch() != 27);
}

