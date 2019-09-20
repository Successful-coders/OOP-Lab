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
public:
	QuadrangleDonut()
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

		this->pointsIn[0].x = 50;
		this->pointsIn[0].y = 50;
		this->pointsIn[0].x = 100;
		this->pointsIn[0].y = 50;
		this->pointsIn[0].x = 100;
		this->pointsIn[0].y = 100;
		this->pointsIn[0].x = 50;
		this->pointsIn[0].y = 100;
		PEN qd_pen();
		PEN qd_penIn();
		BRUSH qd_brush();
	}
	QuadrangleDonut(DRAW_TYPE type, POINT* points, POINT* pointsIn, PEN qd_pen, PEN qd_penIn, BRUSH qd_brush)
	{
		this->type = type;
		for (int i = 0; i < 4; i++)
		{
			this->points[i] = points[i];
		}
		for (int i = 0; i < 4; i++)
		{
			this->pointsIn[i] = pointsIn[i];
		}
		this->qd_pen = qd_pen;
		this->qd_penIn = qd_penIn;
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