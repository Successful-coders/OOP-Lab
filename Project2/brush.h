#pragma once
#include "QD.h"
class BRUSH
{
private:
	char name[16];
	COLORREF color;
public:
	BRUSH();
	BRUSH(char* name, COLORREF color);
	char* GetName();
	void SetName(char* name);
	COLORREF GetColor();
	void SetColor(COLORREF color);
};
