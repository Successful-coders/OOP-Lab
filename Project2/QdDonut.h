#pragma once
#include "QdShaded.h"

class QuadrangleDonut : public QuadrangleShaded
{
protected:
	POINT pointsIn[4];
	Pen penIn;
	void CheckConvex2();
	void CheckIncluded();
	bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest);
public:
	QuadrangleDonut();
	QuadrangleDonut(POINT* points, POINT* pointsIn, Pen qd_pen, Pen qd_penIn, Brush qd_brush);
	void Save(FILE* saveFile);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	POINT* GetPointIn();
	void SetPointIn(POINT* points);
	Pen GetPenIn();
	void SetPenIn(char* name, int width, COLORREF color);
};
