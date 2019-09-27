#pragma once
#include "QD.h"
class Pen
{
private:
	char name[16];
	int width;
	COLORREF color;
public:
	Pen();
	Pen(char* name, int width, COLORREF color);
	char* GetName();
	void SetName(char* name);
	int GetWidth();
	void SetWidth(int width);
	COLORREF GetColor();
	void SetColor(COLORREF color);
};

