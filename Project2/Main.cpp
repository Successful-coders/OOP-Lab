//Main.cpp
#include "QD.h"
#include "QdCountour.h"
#include "QdDonut.h"
#include "QdShaded.h"
#define up 119
#define righ 100
#define down 115
#define left 97



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
		printf("������� ����� ��� ������\n");
		break;
	}
	case INCORRECT_BRUSH:
	{
		printf("������� ����� ��� �����\n");
		break;
	}
	case INCORRECT_PEN_STYLE:
	{
		printf("������� ����� ��� ����\n");
		break;
	}
	case OUT_FRAME:
	{
		printf("���������� ������ �� ������ � ����� ����\n");
		break;
	}
	case NOT_INCLUDED:
	{
		printf("������ ��������������� �� ������ � ������\n");
		break;
	}
	case NOT_CONVEX:
	{
		printf("���������� �� ������������ ������� ��������� ����������������\n");
		break;
	}
	case THREE_POINTS_IN_LINE:
	{
		printf("� �������� ���������� ��� ����� ����� �� ����� ������\n");
		break;
	}
	}

	_getch();
}

void DeleteAll(HWND hwnd, HDC hdc)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	POINT ppt[2];
	ppt[0].x = 0;
	ppt[0].y = 0;
	ppt[1].x = rt.right;
	ppt[1].y = rt.bottom;
	HPEN newPen = CreatePen(PS_SOLID, 0, RGB(0,0,0));
	HPEN oldPen = SelectPen(hdc, newPen);
	HBRUSH newBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = SelectBrush(hdc, newBrush);
	Rectangle(hdc, ppt[0].x, ppt[0].y, ppt[1].x, ppt[1].y);
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
			QuadrangleContour quad = QuadrangleContour(ppt, pen);
			quad.Draw(hdc, hwnd);
			int codePress = _getch();
			while (codePress != 27)
			{
				switch (codePress)
				{
				case up:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 0, -20);
					break;
				}
				case righ:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 20, 0);
					break;
				}

				case down:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 0, 20);
					break;
				}

				case left:
				{
					DeleteAll(hwnd, hdc);
					//sReleaseDC(hwnd, hdc);
					quad.Move(hwnd, -20, 0);
					break;
				}

				break;
				}
				codePress = _getch();
			} 
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
			int codePress = _getch();
			while (codePress != 27)
			{
				switch (codePress)
				{
				case up:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 0, -20);
					break;
				}
				case righ:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 20, 0);
					break;
				}

				case down:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 0, 20);
					break;
				}

				case left:
				{
					DeleteAll(hwnd, hdc);
					//sReleaseDC(hwnd, hdc);
					quad.Move(hwnd, -20, 0);
					break;
				}
				break;
				}
				codePress = _getch();
			}
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
			COLORREF PenColorIn = RGB(Red, Green, Blue);
			Pen penIn = Pen(PenNameIn, PenWidthIn, PenColorIn);

			QuadrangleDonut quad = QuadrangleDonut(ppt, pptIn, pen, penIn, brush);
			quad.Draw(hdc, hwnd);
			int codePress = _getch();
			while (codePress != 27)
			{
				switch (codePress)
				{
				case up:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 0, -20);
					break;
				}
				case righ:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 20, 0);
					break;
				}

				case down:
				{
					DeleteAll(hwnd, hdc);
					//ReleaseDC(hwnd, hdc);
					quad.Move(hwnd, 0, 20);
					break;
				}

				case left:
				{
					DeleteAll(hwnd, hdc);
					//sReleaseDC(hwnd, hdc);
					quad.Move(hwnd, -20, 0);
					break;
				}
				break;
				}
				codePress = _getch();
			}
			break;
		}

		}
	} while (_getch() != 27);
	fclose(file);


}
