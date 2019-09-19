#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <conio.h>
using namespace std;


enum DRAW_TYPE
{
	CONTOUR,
	SHADED,
	DONUT
};



struct PEN
{
	char name[16];
	int width;
	COLORREF color;
};

struct BRUSH
{
	char name[16];
	COLORREF color;
};

struct Quadrangle
{
	DRAW_TYPE type;
	POINT points[4];
	PEN qd_pen;
	BRUSH qd_brush;
};

DRAW_TYPE StringToEnum(const char string[]);
COLORREF RGBToColor(int R, int G, int B);
void Draw(HDC hdc, HWND hwnd, Quadrangle* quadrangle, Quadrangle* quad2);
void Read_Characteristics(Quadrangle* quad, FILE* file, Quadrangle* quad2, HDC hdc);
int StringToBrushHash(const char string[]);
int StringToPenStyle(const char string[]);
bool IsQuadrangle(Quadrangle* quad);
bool IsInFrame(HWND hwnd, Quadrangle* qd);
bool IsDonut(Quadrangle* quad1, Quadrangle* quad2);
bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest);
#pragma once
