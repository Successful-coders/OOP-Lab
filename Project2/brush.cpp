#include "brush.h"

Brush::Brush()
{
	memcpy(this->name, "SOLID", 6);
	this->color = RGB(0, 0, 0);
}
Brush::Brush(const char* name)
{
	memcpy(this->name, name, 16);
}
Brush::Brush(char* name, COLORREF color)
{
	memcpy(this->name, name, 16);
	this->color = color;
}
char* Brush::GetName()
{
	return name;
}
void Brush::SetName(char* name)
{
	memcpy(this->name, name, 16);
}
COLORREF Brush::GetColor()
{
	return color;
}
void Brush::SetColor(COLORREF color)
{
	this->color = color;
}

