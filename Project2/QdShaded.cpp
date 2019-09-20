#include "QD.h"

class QuadrangleShaded
{
private:
	DRAW_TYPE type;
	POINT points[4];
	PEN qd_pen;
	BRUSH qd_brush;
public:
	QuadrangleShaded()
	{
		this->type = CONTOUR;
		this->points[0].x = 50;
		this->points[0].y = 50;
		this->points[0].x = 100;
		this->points[0].y = 50;
		this->points[0].x = 100;
		this->points[0].y = 100;
		this->points[0].x = 50;
		this->points[0].y = 100;
		PEN qd_pen();
		BRUSH qd_brush();
	}
	QuadrangleShaded(DRAW_TYPE type, POINT* points, PEN qd_pen, BRUSH qd_brush)
	{
		this->type = type;
		for (int i = 0; i < 4; i++)
		{
			this->points[i] = points[i];
		}
		this->qd_pen = qd_pen;
		this->qd_brush = qd_brush;
	}
	void Draw()
	{

	}
	DRAW_TYPE GetType()
	{
		return type;
	}
	void SetType(DRAW_TYPE type)
	{
		this->type = type;
	}
	POINT* GetPoint()
	{
		return points;
	}
	void SetPoint(POINT* points)
	{
		for (int i = 0; i < 4; i++)
		{
			this->points[i] = points[i];
		}
	}
	//TODO for all
};