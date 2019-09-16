#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
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
void Draw(HDC hdc, Quadrangle* quadrangle, Quadrangle* quad2);
void Read_Characteristics(Quadrangle* quad, FILE *file, Quadrangle *quad2);
int StringToBrushHash(const char string[]);
int StringToPenStyle(const char string[]);
#pragma once
