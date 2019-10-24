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


class QuadrangleShaded
{
private:
	POINT points[4];
	Pen pen;
	Brush brush;
	HWND hwnd;
	DRAW_TYPE StringToEnum(const char string[]);
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckInFrame(HWND hwnd);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
	void DeleteAll(HWND hwnd);
public:
	QuadrangleShaded();
	QuadrangleShaded(POINT* points, Pen qd_pen, Brush qd_brush);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPoint();
	void SetPoint(POINT* points);
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
	void SaveQuad(FILE* saveFile);
	Brush GetBrush();
	void SetBrush(char* name, COLORREF color);
};