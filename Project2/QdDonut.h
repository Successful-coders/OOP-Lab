#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "brush.h"
#include "pen.h"
#include "DrawTypeEnum.h"
#include "Error.h"

using namespace std;


class QuadrangleDonut
{
private:
	POINT points[4];
	POINT pointsIn[4];
	Pen pen;
	Pen penIn;
	Brush brush;
	HWND hwnd;
	DRAW_TYPE StringToEnum(const char string[]);
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckConvex2();
	void CheckInFrame(HWND hwnd);
	void CheckIncluded();
	bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
	void DeleteAll(HWND hwnd);
public:
	QuadrangleDonut();
	QuadrangleDonut(POINT* points, POINT* pointsIn, Pen qd_pen, Pen qd_penIn, Brush qd_brush);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPoint();
	POINT* GetPointIn();
	void SetPoint(POINT* points);
	void SetPointIn(POINT* points);
	void Save(FILE* saveFile);
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
	Pen GetPenIn();
	void SetPenIn(char* name, int width, COLORREF color);
	Brush GetBrush();
	void SetBrush(char* name, COLORREF color);
};
