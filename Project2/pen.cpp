#pragma once
#include "pen.h"

PEN::PEN()
{
	memcpy(this->name, "PS_SOLID", 16);
	this->width = 1;
	this->color = RGB(255, 255, 255);
}
PEN::PEN(char* name, int width, COLORREF color)
{
	memcpy(this->name, name, 16);
	this->width = width;
	this->color = color;
}
char* PEN::GetName()
{
	return name;
}
void PEN::SetName(char* name)
{
	memcpy(this->name, name, 16);
}
int PEN::GetWidth()
{
	return width;
}
void PEN::SetWidth(int width)
{
	this->width = width;
}
COLORREF PEN::GetColor()
{
	return color;
}
void PEN::SetColor(COLORREF color)
{
	this->color = color;
}

