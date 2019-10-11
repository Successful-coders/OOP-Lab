#pragma once
#include"QD.h"

using namespace std;
class QuadrangleContour // Check in set
{
private:
	POINT points[4];
	Pen pen;
	HWND hwnd;
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckInFrame(HWND hwnd);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
	void DeleteAll(HWND hwnd);
public:
	QuadrangleContour();
	QuadrangleContour(POINT* points, Pen qd_pen);
	void Save(const char* fileName);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPoint();
	void SetPoint(POINT* points);
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
};