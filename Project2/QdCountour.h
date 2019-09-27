#pragma once
#include"QD.h"

using namespace std;
class QuadrangleContour // Check in set
{
private:
	DRAW_TYPE type;
	POINT points[4];
	Pen pen;
	HDC hdc;
	HWND hwnd;
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckInFrame(HWND hwnd);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
public:
	QuadrangleContour();
	QuadrangleContour(POINT* points, Pen qd_pen);
	void Draw(HDC hdc, HWND hwnd);
	POINT* GetPoint();
	void SetPoint(POINT* points);
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
	HDC GetHdc();
};