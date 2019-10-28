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
class Figure
{
public:
	Figure();
	Figure(POINT* points, Pen qd_pen);
	virtual void Draw(HWND hwnd);
protected:
	POINT points[4];
	Pen pen;
	HWND hwnd;
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckInFrame(HWND hwnd);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
};
