#pragma once
#include"QD.h"
using namespace std;

class QuadrangleShaded
{
private:
	DRAW_TYPE type;
	POINT points[4];
	Pen pen;
	Brush brush;
	HDC hdc;
	HWND hwnd;
	DRAW_TYPE StringToEnum(const char string[]);
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckInFrame(HWND hwnd);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
public:
	QuadrangleShaded();
	QuadrangleShaded(POINT* points, Pen qd_pen, Brush qd_brush);
	void Draw(HDC hdc, HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPoint();
	void SetPoint(POINT* points);
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
	Brush GetBrush();
	void SetBrush(char* name, COLORREF color);
};