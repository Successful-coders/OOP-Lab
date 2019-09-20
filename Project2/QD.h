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
#include "pen.h"
#include "brush.h"
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

