//Main.cpp
#include "QD.h"
#include "QdCountour.h"
#include "QdDonut.h"
#include "QdShaded.h"
#define UP 119
#define RIGHT 100
#define DOWN 115
#define LEFT 97



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
	do
	{
		switch (TypeDraw)
		{
		case CONTOUR:
		{
			fclose(file);
			QuadrangleContour quad = QuadrangleContour(ppt, pen);
			quad.Draw(hwnd);
			int codePress = _getch();
			while (codePress != 27)
			{
				switch (codePress)
				{
				case UP:
				{
					quad.Move(hwnd, 0, -20);
					break;
				}
				case RIGHT:
				{
					quad.Move(hwnd, 20, 0);
					break;
				}

				case DOWN:
				{
					quad.Move(hwnd, 0, 20);
					break;
				}

				case LEFT:
				{
					quad.Move(hwnd, -20, 0);
					break;
				}

				break;
				}
				codePress = _getch();
			} 

			quad.Save("ContourSave.txt");
			break;
		}
		case SHADED:
		{
			char brushName[45];
			fscanf(file, "%s", &(brushName));
			fscanf(file, "%i %i %i", &Red, &Green, &Blue);
			fclose(file);
			COLORREF brushColor = RGB(Red, Green, Blue);
			Brush brush = Brush(brushName, brushColor);

			QuadrangleShaded quad = QuadrangleShaded(ppt, pen, brush);
			quad.Draw(hwnd);
			int codePress = _getch();
			while (codePress != 27)
			{
				switch (codePress)
				{
				case UP:
				{
					quad.Move(hwnd, 0, -20);
					break;
				}
				case RIGHT:
				{
					quad.Move(hwnd, 20, 0);
					break;
				}

				case DOWN:
				{
					quad.Move(hwnd, 0, 20);
					break;
				}

				case LEFT:
				{
					quad.Move(hwnd, -20, 0);
					break;
				}
				break;
				}
				codePress = _getch();
			}

			quad.Save("ShadedSave.txt");
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

			char PenNameIn[16];
			int PenWidthIn;
			fscanf(file, "%s", &(PenNameIn));
			fscanf(file, "%i", &(PenWidthIn));
			fscanf(file, "%i %i %i", &Red, &Green, &Blue);
			fclose(file);
			COLORREF PenColorIn = RGB(Red, Green, Blue);
			Pen penIn = Pen(PenNameIn, PenWidthIn, PenColorIn);

			QuadrangleDonut quad = QuadrangleDonut(ppt, pptIn, pen, penIn, brush);
			quad.Draw(hwnd);
			int codePress = _getch();
			while (codePress != 27)
			{
				switch (codePress)
				{
				case UP:
				{
					quad.Move(hwnd, 0, -20);
					break;
				}
				case RIGHT:
				{
					quad.Move(hwnd, 20, 0);
					break;
				}

				case DOWN:
				{
					quad.Move(hwnd, 0, 20);
					break;
				}

				case LEFT:
				{
					quad.Move(hwnd, -20, 0);
					break;
				}
				break;
				}
				codePress = _getch();
			}

			quad.Save("DonatSave.txt");
			break;
		}
		}
	} while (_getch() != 27);



}
