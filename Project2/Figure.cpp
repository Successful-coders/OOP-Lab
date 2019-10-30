#pragma once
#include "Figure.h"

using namespace std;

Pen Figure::GetPen()
{
	return pen;
}
void Figure::SetPen(char* name, int width, COLORREF color)
{
	this->pen = Pen(name, width, color);
}