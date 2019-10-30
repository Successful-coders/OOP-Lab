#pragma once
#include "QdContour.h"

using namespace std;

class QuadrangleShaded : public QuadrangleContour
{
protected:
	Brush brush;
	int StringToBrushHash(const char string[]);
public:
	QuadrangleShaded();
	QuadrangleShaded(POINT* points, Pen qd_pen, Brush qd_brush);
	void Draw(HWND hwnd);
	void Save(FILE* saveFile);
	Brush GetBrush();
	void SetBrush(char* name, COLORREF color);
};