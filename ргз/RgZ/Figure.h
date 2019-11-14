///////////////////////////////////////////////////////////
//  Figure.h
//  Implementation of the Class Figure
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Жопчики
///////////////////////////////////////////////////////////

#if !defined(EA_A16A1B75_6665_43ec_8B0A_61ECF896770E__INCLUDED_)
#define EA_A16A1B75_6665_43ec_8B0A_61ECF896770E__INCLUDED_

#include "Error.h"
#include "Pen.h"

class Figure
{

public:
	Figure();
	virtual ~Figure();
	Error *m_Error;
	Pen *m_Pen;

	virtual void Draw(HWND hwnd);
	Pen GetPen();
	virtual void Move(HWND hwnd, int x, int y);
	virtual void Save(FILE* saveFile);
	void SetPen(char* name, int width, COLORREF color);

protected:
	HWND hwnd;
	Pen pen;

	virtual void CheckInFrame(HWND hwnd);

};
#endif // !defined(EA_A16A1B75_6665_43ec_8B0A_61ECF896770E__INCLUDED_)
