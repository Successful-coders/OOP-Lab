#pragma once
#include <windows.h>
#include <windowsx.h>

class Brush
{
private:
	char name[16];
	COLORREF color;
public:
	Brush();
	Brush(const char* name);
	Brush(char* name, COLORREF color);
	char* GetName();
	void SetName(char* name);
	COLORREF GetColor();
	void SetColor(COLORREF color);
};
