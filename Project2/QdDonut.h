#pragma once
#include "QD.h"


class QuadrangleDonut
{
private:
	DRAW_TYPE type;
	POINT points[4];
	POINT pointsIn[4];
	PEN qd_pen;
	PEN qd_penIn;
	BRUSH qd_brush;
	HDC hdc;
	HWND hwnd;
	DRAW_TYPE StringToEnum(const char string[]);
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void PrintError(ERROR error);
	void CheckConvex();
	void CheckConvex2();
	void CheckInFrame(HWND hwnd);
	void CheckIncluded();
	bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest);
	bool IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
public:
	QuadrangleDonut();
	QuadrangleDonut(DRAW_TYPE type, POINT* points, POINT* pointsIn, PEN qd_pen, PEN qd_penIn, BRUSH qd_brush);
	void Draw(HDC hdc, HWND hwnd);
	DRAW_TYPE GetType();
	void SetType(DRAW_TYPE type);
	POINT* GetPoint();
	POINT* GetPointIn();
	void SetPoint(POINT* points);
	void SetPointIn(POINT* points);
	PEN GetPen();
	void SetPen(char* name, int width, COLORREF color);
	PEN GetPenIn();
	void SetPen(char* name, int width, COLORREF color);
	BRUSH GetBrush();
	void SetBrush(char* name, COLORREF color);
};