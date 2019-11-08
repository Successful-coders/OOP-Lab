#pragma once
#include "QdShaded.h"

class QuadrangleDonut : public QuadrangleShaded
{
protected:
	QuadrangleShaded In;
	void CheckIncluded  ();
	bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest);
public:
	QuadrangleDonut();
	QuadrangleDonut(POINT* points, POINT* pointsIn, Pen qd_pen, Pen qd_penIn, Brush qd_brush);
	void Save(FILE* saveFile);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
};
