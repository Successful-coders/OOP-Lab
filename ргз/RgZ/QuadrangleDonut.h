///////////////////////////////////////////////////////////
//  QuadrangleDonut.h
//  Implementation of the Class QuadrangleDonut
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Darya
///////////////////////////////////////////////////////////

#if !defined(EA_52A97DD1_6D44_4f2a_98BA_E2FB28FD9600__INCLUDED_)
#define EA_52A97DD1_6D44_4f2a_98BA_E2FB28FD9600__INCLUDED_

#include "QuadrangleShaded.h"

class QuadrangleDonut : public QuadrangleShaded
{

public:
	virtual ~QuadrangleDonut();
	QuadrangleShaded *m_QuadrangleShaded;

	QuadrangleDonut();
	QuadrangleDonut(POINT* points, Pen qd_pen, Brush qd_brush, Pen qd_penIn, POINT* pointsIn);
	void Draw(HWND hwnd);
	void Move(HWND hwnd, int x, int y);
	void Save(FILE* saveFile);

protected:
	QuadrangleShade In;

	void CheckIncluded();
	boolean IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4);

};
#endif // !defined(EA_52A97DD1_6D44_4f2a_98BA_E2FB28FD9600__INCLUDED_)
