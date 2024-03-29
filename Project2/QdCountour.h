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


class QuadrangleContour // Check in set
{
private:
	POINT points[4];
	Pen pen;
	HWND hwnd;
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckInFrame(HWND hwnd);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
	void DeleteAll(HWND hwnd);
public:
	QuadrangleContour();
	QuadrangleContour(POINT* points, Pen qd_pen);
	void SaveQuad(FILE *saveFile);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPoint();
	void SetPoint(POINT* points);
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
};