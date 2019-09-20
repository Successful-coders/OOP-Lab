//QD.h
#pragma once

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#undef ERROR

using namespace std;
enum ERROR
{
	INCORRECT_DRAW_TYPE,
	INCORRECT_BRUSH,
	INCORRECT_PEN_STYLE,
	OUT_FRAME,
	NOT_INCLUDED,
	NOT_CONVEX,
	THREE_POINTS_IN_LINE,
};

enum DRAW_TYPE
{
	CONTOUR,
	SHADED,
	DONUT
};

class PEN
{
private:
	char name[16];
	int width;
	COLORREF color;
public:
	PEN()
	{
		memcpy(this->name, "PS_SOLID", 16);
		this->width = 1;
		this->color = RGB(255, 255, 255);
	}
	PEN(char* name, int width, COLORREF color)
	{
		memcpy(this->name, name, 16);
		this->width = width;
		this->color = color;
	}
	char* GetName()
	{
		return name;
	}
	void SetName(char* name)
	{
		memcpy(this->name, name, 16);
	}
	//TODO for all
};

class BRUSH
{
private:
	char name[16];
	COLORREF color;
public:
	BRUSH()
	{
		memcpy(this->name, "BLACK_BRUSH", 16);
		this->color = RGB(0, 0, 0);
	}
	BRUSH(char* name, COLORREF color)
	{
		memcpy(this->name, name, 16);
		this->color = color;
	}
	char* GetName()
	{
		return name;
	}
	void SetName(char* name)
	{
		memcpy(this->name, name, 16);
	}
};


DRAW_TYPE StringToEnum(const char string[]);
void DrawShaded(HDC hdc, HWND hwnd, Quadrangle quad);
void DrawDonut(HDC hdc, HWND hwnd, Quadrangle quad, Quadrangle quad2);
void Read_Characteristics(Quadrangle* quad, FILE* file, Quadrangle* quad2, HDC hdc);
int StringToBrushHash(const char string[]);
int StringToPenStyle(const char string[]);
void PrintError(ERROR error);
void CheckConvex(Quadrangle quad);
void CheckInFrame(HWND hwnd, Quadrangle qd);
void CheckIncluded(Quadrangle quad1, Quadrangle quad2);
bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest);
bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);