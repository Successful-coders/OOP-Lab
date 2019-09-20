#pragma once
#include"QD.h"
using namespace std;
class QuadrangleCountour // Check in set
{
private:
	DRAW_TYPE type;
	POINT points[4];
	PEN qd_pen;
	BRUSH qd_brush;
	HDC hdc;
	HWND hwnd;
	DRAW_TYPE StringToEnum(const char string[]);
	int StringToBrushHash(const char string[]);
	int StringToPenStyle(const char string[]);
	void PrintError(ERROR error);
	void CheckConvex();
	void CheckInFrame();
	bool IsPoint();
public:
	QuadrangleCountour();
	QuadrangleCountour(DRAW_TYPE type, POINT* points, PEN qd_pen, BRUSH qd_brush);
	void Draw();
	DRAW_TYPE GetType();
	void SetType(DRAW_TYPE type);
	POINT* GetPoint();
	void SetPoint(POINT* points);
	PEN GetPen();
	void SetPen(char* name, int width, COLORREF color);
	BRUSH GetBrush();
	void SetBrush(char* name, COLORREF color);

};