//Main.cpp
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "DoubleLinkedList.h"
#include "QdCountour.h"
#include "QdDonut.h"
#include "QdShaded.h"

#define UP 119
#define RIGHT 100
#define DOWN 115
#define LEFT 97

using namespace std;


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

void DrawAll(DoubleLinkedList<QuadrangleContour> list, HWND hwnd)
{
	for (int i = 0; i < list.GetLength(); i++)
	{
		list.GetElement(i).Draw(hwnd);
	}
}

void DrawAllReverse(DoubleLinkedList<QuadrangleContour> list, HWND hwnd)
{
	for (int i = list.GetLength() - 1; i >= 0; i--)
	{
		list.GetElement(i).Draw(hwnd);
	}
}

template <class Quad>
 bool FindByPenColor(DoubleLinkedList<Quad> list, Quad*foundQuad, COLORREF color)
{
	for (int i = 0; i < list.GetLength(); i++)
	{
		Quad quad = list.GetElement(i);

		if (quad.GetPen().GetColor() == color)
		{
			*foundQuad = Quad(quad);
			return true;
		}
	}

	return false;
}

 void PrintContourListByPenColor(DoubleLinkedList<QuadrangleContour> list)
 {
	 for (int i = 0; i < list.GetLength(); i++)
	 {
		 COLORREF penColor = list.GetElement(i).GetPen().GetColor();

		 printf_s("R: %d, G: %d, B: %d.\n", GetRValue(penColor), GetGValue(penColor), GetBValue(penColor));
	 }
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
	DoubleLinkedList<QuadrangleContour> listContour = DoubleLinkedList<QuadrangleContour>();
	DoubleLinkedList<QuadrangleShaded> listShaded = DoubleLinkedList<QuadrangleShaded>();
	DoubleLinkedList<QuadrangleDonut> listDonut = DoubleLinkedList<QuadrangleDonut>();

	while (!feof(file))
	{
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

				listContour.PushElement(quad);

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

				listShaded.PushElement(quad);
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

				listDonut.PushElement(quad);

				break;
			}
		}

		if (!feof(file))
		{
			char newLine;
			fscanf(file, "%c", &newLine);
		}
	}
	fclose(file);

	for (int i = 0; i < 4; i++)
	{
		COLORREF penColor = listContour.GetElement(i).GetPen().GetColor();

		printf_s("R: %d, G: %d, B: %d.\n", GetRValue(penColor), GetGValue(penColor), GetBValue(penColor));
	}

	printf("Enter color:\n");
	int red, green, blue;
	scanf_s("%d %d %d", &red, &green, &blue);

	QuadrangleContour foundContourQuad;
	bool isFind = FindByPenColor<QuadrangleContour>(listContour, &foundContourQuad, RGB(red, green, blue));

	if (isFind)
	{
		printf("Quad was found");
		foundContourQuad.Draw(hwnd);
	}
	else
	{
		printf("Quad was not found");
	}

	_getch();
}
