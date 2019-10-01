#pragma once
#include "QD.h"


class QuadrangleDonut
{
private:
	DRAW_TYPE type;
	POINT points[4];
	POINT pointsIn[4];
	Pen pen;
	Pen penIn;
	Brush brush;
	HDC hdc;
	HWND hwnd;
	DRAW_TYPE StringToEnum(const char string[]);
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void CheckConvex();
	void CheckConvex2();
	void CheckInFrame(HWND hwnd);
	void CheckIncluded();
	bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
public:
	QuadrangleDonut();
	QuadrangleDonut(POINT* points, POINT* pointsIn, Pen qd_pen, Pen qd_penIn, Brush qd_brush);
	void Draw(HDC hdc, HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPoint();
	POINT* GetPointIn();
	void SetPoint(POINT* points);
	void SetPointIn(POINT* points);
	Pen GetPen();
	void SetPen(char* name, int width, COLORREF color);
	Pen GetPenIn();
	void SetPenIn(char* name, int width, COLORREF color);
	Brush GetBrush();
	void SetBrush(char* name, COLORREF color);
};
