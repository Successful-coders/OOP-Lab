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
protected:
	Pen pen;
	HWND hwnd;
	virtual void CheckInFrame(HWND hwnd) = 0;
public:
	virtual void Save(FILE* saveFile) = 0;
	virtual void Draw(HWND hwnd) = 0;
	virtual void Move(HWND hwnd, int x, int y) = 0;
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
};