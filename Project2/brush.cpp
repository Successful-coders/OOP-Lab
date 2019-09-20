#include "brush.h"

BRUSH::BRUSH()
{
	memcpy(this->name, "BLACK_BRUSH", 16);
	this->color = RGB(0, 0, 0);
}
BRUSH::BRUSH(char* name, COLORREF color)
{
	memcpy(this->name, name, 16);
	this->color = color;
}
char* BRUSH::GetName()
{
	return name;
}
void BRUSH::SetName(char* name)
{
	memcpy(this->name, name, 16);
}
COLORREF BRUSH::GetColor()
{
	return color;
}
void BRUSH::SetColor(COLORREF color)
{
	this->color = color;
}

