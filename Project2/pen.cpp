#include "pen.h"

Pen::Pen()
{
	memcpy(this->name, "PS_SOLID", 16);
	this->width = 1;
	this->color = RGB(255, 255, 255);
}
Pen::Pen(char* name, int width, COLORREF color)
{
	memcpy(this->name, name, 16);
	this->width = width;
	this->color = color;
}
char* Pen::GetName()
{
	return name;
}
void Pen::SetName(char* name)
{
	memcpy(this->name, name, 16);
}
int Pen::GetWidth()
{
	return width;
}
void Pen::SetWidth(int width)
{
	this->width = width;
}
COLORREF Pen::GetColor()
{
	return color;
}
void Pen::SetColor(COLORREF color)
{
	this->color = color;
}

