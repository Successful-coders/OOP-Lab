#pragma once
#include "Figure.h"

using namespace std;

class QuadrangleContour : public Figure
{
protected:
	POINT points[4];
	int StringToPenStyle(const char string[]);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
	void DeleteAll(HWND hwnd);
public:
	void CheckInFrame(HWND hwnd);
	void CheckConvex();
	QuadrangleContour();
	QuadrangleContour(POINT* points, Pen qd_pen);
	void Save(FILE *saveFile);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPoint();
	void SetPoint(POINT* points);
};