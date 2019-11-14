///////////////////////////////////////////////////////////
//  QuadrangleShaded.h
//  Implementation of the Class QuadrangleShaded
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Darya
///////////////////////////////////////////////////////////

#if !defined(EA_2D71DB4A_CFA3_426d_8276_0BF1E272741B__INCLUDED_)
#define EA_2D71DB4A_CFA3_426d_8276_0BF1E272741B__INCLUDED_

#include "QuadrangleContour.h"
#include "Brush.h"

class QuadrangleShaded : public QuadrangleContour
{

public:
	virtual ~QuadrangleShaded();
	Brush *m_Brush;

	QuadrangleShaded();
	QuadrangleShaded(POINT* points, Pen qd_pen, Brush qd_brush);
	void Draw(HWND hwnd);
	Brush GetBrush();
	void Save(FILE* saveFile);
	void SetBrush(char* name, COLORREF color);

protected:
	Brush brush[16];

	int StringToBrushHash(const char string[]);

};
#endif // !defined(EA_2D71DB4A_CFA3_426d_8276_0BF1E272741B__INCLUDED_)
