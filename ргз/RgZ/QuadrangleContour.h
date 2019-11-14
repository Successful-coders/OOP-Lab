///////////////////////////////////////////////////////////
//  QuadrangleContour.h
//  Implementation of the Class QuadrangleContour
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Darya
///////////////////////////////////////////////////////////

#if !defined(EA_E6C2ED97_8C26_4406_A65C_B1D0731660D9__INCLUDED_)
#define EA_E6C2ED97_8C26_4406_A65C_B1D0731660D9__INCLUDED_

#include "Figure.h"

class QuadrangleContour : public Figure
{

public:
	virtual ~QuadrangleContour();

	QuadrangleContour();
	QuadrangleContour(POINT* points, Pen qd_pen);
	void CheckConvex();
	void CheckInFrame(HWND hwnd);
	void Draw(HWND hwnd);
	POINT* GetPoint();
	void Move(HWND hwnd, int x, int y);
	void Save(FILE* saveFile);
	void SetPoint(POINT* points);

protected:
	POINT points;

	void DeleteAll(HWND hwnd);
	boolean IsPoint(POINT k1, POINT k2, POINT k3, POINT k4);
	int StringToPenStyle(const char string[]);

};
#endif // !defined(EA_E6C2ED97_8C26_4406_A65C_B1D0731660D9__INCLUDED_)
