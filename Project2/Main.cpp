//Main.cpp
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <fstream>

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
		cout << "Неверно задан тип фигуры\n";
		break;
	}
	case INCORRECT_BRUSH:
	{
		cout << "Неверно задан тип кисти\n";
		break;
	}
	case INCORRECT_PEN_STYLE:
	{
		cout << "Неверно задан тип пера\n";
		break;
	}
	case OUT_FRAME:
	{
		cout <<"Координаты фигуры не входят в рамки окна\n";
		break;
	}
	case NOT_INCLUDED:
	{
		cout <<"Второй четырехугольник не вложен в первый\n";
		break;
	}
	case NOT_CONVEX:
	{
		cout <<"Координаты не удовлетворют условию выпуклого четырехугольника\n";
		break;
	}
	case THREE_POINTS_IN_LINE:
	{
		cout <<"В заданных кооринатах три точки лежат на одной прямой\n";
		break;
	}
	}

	_getch();
}
template <class QuadDraw>
void DrawAll(DoubleLinkedList<QuadDraw> list, HWND hwnd)
{
	for (int i = 0; i < list.GetLength(); i++)
	{
		list.GetElement(i).Draw(hwnd);
	}
}
template <class QuadDrawReverse>
void DrawAllReverse(DoubleLinkedList<QuadDrawReverse> list, HWND hwnd)
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

 template <class Quad>
 void SaveAllReverse(DoubleLinkedList<Quad> list, const char *fileName)
 {
	 FILE* saveFile = fopen(fileName, "w");
	 for (int i = 0; i < list.GetLength(); i++)
	 {
		 list.GetElement(i).SaveQuad(saveFile);
		 fprintf(saveFile,"\n");
	 }
	 fclose(saveFile);
 }

 template <class Quad>
 void SaveAll(DoubleLinkedList<Quad> list, const char* fileName)
 {
	 FILE* saveFile = fopen(fileName, "w");
	 for (int i = list.GetLength() - 1; i >= 0; i++)
	 {
		 list.GetElement(i).SaveQuad(saveFile);
		 fprintf(saveFile, "\n");
	 }
	 fclose(saveFile);
 }

 template <class QuadPrint>
 void PrintContourListByPenColor(DoubleLinkedList<QuadPrint> list)
 {
	 for (int i = 0; i < list.GetLength(); i++)
	 {
		 COLORREF penColor = list.GetElement(i).GetPen().GetColor();

		 cout <<("R: %d, G: %d, B: %d.\n", GetRValue(penColor), GetGValue(penColor), GetBValue(penColor));
	 }
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
	 HPEN newPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	 HPEN oldPen = SelectPen(hdc, newPen);
	 HBRUSH newBrush = CreateSolidBrush(RGB(0, 0, 0));
	 HBRUSH oldBrush = SelectBrush(hdc, newBrush);
	 Rectangle(hdc, ppt[0].x, ppt[0].y, ppt[1].x, ppt[1].y);
 }

 template<class T>
 void PrintColor(T list)
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
	 ifstream fin("test.txt");
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

	 while (!fin.eof())
	 {
		 fin >> type;
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
			 fin>>(ppt[i].x)>>(ppt[i].y);
		 }

		 fin>>(PenName);
		 fin >> (PenWidth);
		 int Red, Green, Blue;
		 fin >> Red >> Green >> Blue;

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
			 fin >> (brushName);
			 fin >> Red >> Green >> Blue;

			 COLORREF brushColor = RGB(Red, Green, Blue);
			 Brush brush = Brush(brushName, brushColor);

			 QuadrangleShaded quad = QuadrangleShaded(ppt, pen, brush);

			 listShaded.PushElement(quad);
			 break;
		 }
		 case DONUT:
		 {
			 char brushName[45];
			 fin >> (brushName);
			 fin >> Red >> Green >> Blue;
			 COLORREF brushColor = RGB(Red, Green, Blue);
			 Brush brush = Brush(brushName, brushColor);

			 POINT pptIn[4];
			 for (int i = 0; i < 4; i++)
			 {
				 fin >> pptIn[i].x >> pptIn[i].y;
			 }

			 char PenNameIn[16];
			 int PenWidthIn;
			 fin >> PenNameIn;
			 fin >> (PenWidthIn);
			 fin >> Red >> Green >> Blue;

			 COLORREF PenColorIn = RGB(Red, Green, Blue);
			 Pen penIn = Pen(PenNameIn, PenWidthIn, PenColorIn);

			 QuadrangleDonut quad = QuadrangleDonut(ppt, pptIn, pen, penIn, brush);

			 listDonut.PushElement(quad);

			 break;
		 }
		 }

		 if (!fin.eof())
		 {
			 char newLine[1];
			 fin.getline(newLine, 1);
		 }
	 }
	 fin.close();

	 if (listContour.GetLength() != 0)
	 {
		 PrintColor(listContour);
		 cout <<"Enter color:\n";
		 int red, green, blue;
		 cin >> red >> green >> blue;

		 QuadrangleContour foundContourQuad;
		 bool isFind = FindByPenColor<QuadrangleContour>(listContour, &foundContourQuad, RGB(red, green, blue));
		 if (isFind)
		 {
			 //cout <<"Quad was found");
			 DeleteAll(hwnd, hdc);
			 foundContourQuad.Draw(hwnd);
		 }
		 else
		 {
			 cout <<"Quad was not found";
		 }
	 }
	 if (listShaded.GetLength() != 0)
	 {
		 PrintColor(listShaded);
		 cout <<"Enter color:\n";
		 int red, green, blue;
		 cin >> red >> green >> blue;

		 QuadrangleShaded foundShadedQuad;
		 bool isFind = FindByPenColor<QuadrangleShaded>(listShaded, &foundShadedQuad, RGB(red, green, blue));
		 if (isFind)
		 {
			// cout <<"Quad was found");
			 DeleteAll(hwnd, hdc);
			 foundShadedQuad.Draw(hwnd);

		 }
		 else
		 {
			 cout <<"Quad was not found";
		 }
	 }
	 if (listDonut.GetLength() != 0)
	 {
		 PrintColor(listDonut);

		 cout <<"Enter color:\n";
		 int red, green, blue;
		 cin >> red >> green >> blue;

		 QuadrangleDonut foundDonutQuad;
		 bool isFind = FindByPenColor<QuadrangleDonut>(listDonut, &foundDonutQuad, RGB(red, green, blue));
		 if (isFind)
		 {
			 //cout <<"Quad was found");
			 DeleteAll(hwnd, hdc);
			 foundDonutQuad.Draw(hwnd);
		 }
		 else
		 {
			 cout <<"Quad was not found";
		 }
	 }
	// DrawAll(listContour, hwnd);
	 
	 const char* name = "listContour.txt";
	 SaveAll<QuadrangleContour>(listContour, name);
	 const char* nameShaded = "listShaded.txt";
	 SaveAll<QuadrangleShaded>(listShaded, nameShaded);
	 const char* nameDonut = "listDonut.txt";
	 SaveAll<QuadrangleDonut>(listDonut, nameDonut);

	 const char* name1 = "listContourReverse.txt";
	 SaveAllReverse<QuadrangleContour>(listContour, name);
	 const char* nameShaded1 = "listShadedReverse.txt";
	 SaveAllReverse<QuadrangleShaded>(listShaded, nameShaded1);
	 const char* nameDonut1 = "listDonutReverse.txt";
	 SaveAllReverse<QuadrangleDonut>(listDonut, nameDonut1);

	 _getch();
 }
 
