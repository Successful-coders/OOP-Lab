#include "Qd.h"

DRAW_TYPE StringToEnum(const char string[])
{
	if (strcmp(string, "CONTOUR") == 0)
	{
		return CONTOUR;
	}
	else if (strcmp(string, "SHADED") == 0)
	{
		return SHADED;
	}
	else if (strcmp(string, "DONUT") == 0)
	{
		return DONUT;
	}
	else
	{
		throw "incorrect draw type";
	}
}

int StringToBrushHash(const char string[])
{
	if (strcmp(string, "HS_BDIAGONAL") == 0)
	{
		return HS_BDIAGONAL;
	}
	else if (strcmp(string, "HS_CROSS") == 0)
	{
		return HS_CROSS;
	}
	else if (strcmp(string, "HS_DIAGCROSS") == 0)
	{
		return HS_DIAGCROSS;
	}
	else if (strcmp(string, "HS_FDIAGONAL") == 0)
	{
		return HS_FDIAGONAL;
	}
	else if (strcmp(string, "HS_HORIZONTAL") == 0)
	{
		return HS_HORIZONTAL;
	}
	else if (strcmp(string, "HS_VERTICAL") == 0)
	{
		return HS_VERTICAL;
	}
	else
	{
		throw "incorrect brush";
	}
}

int StringToPenStyle(const char string[])
{
	if (strcmp(string, "PS_SOLID") == 0)
	{
		return PS_SOLID;
	}
	else if (strcmp(string, "PS_DASH") == 0)
	{
		return PS_DASH;
	}
	else if (strcmp(string, "PS_DOT") == 0)
	{
		return PS_DOT;
	}
	else if (strcmp(string, "PS_DASHDOT") == 0)
	{
		return PS_DASHDOT;
	}
	else if (strcmp(string, "PS_DASHDOTDOT") == 0)
	{
		return PS_DASHDOTDOT;
	}
	else if (strcmp(string, "PS_NULL") == 0)
	{
		return PS_NULL;
	}
	else if (strcmp(string, "PS_INSIDEFRAME") == 0)
	{
		return PS_INSIDEFRAME;
	}
	else
	{
		throw "incorrect pen style";
	}
}

COLORREF RGBToColor(int R, int G, int B)
{
	return RGB(R, G, B);
}

void Read_Characteristics(Quadrangle* quad, FILE *file, Quadrangle* quad2)
{
	// read points
	for (int i = 0; i < 4; i++)
		fscanf(file, "%d %d", &(quad->points[i].x), &(quad->points[i].y));

	fscanf(file, "%s", &quad->qd_pen.name);

	fscanf(file, "%d", &quad->qd_pen.width);

	int Red, Green, Blue;
	fscanf(file, "%i %i %i", &Red, &Green, &Blue);
	quad->qd_pen.color = RGBToColor(Red, Green, Blue);

	switch (quad->type)
	{
	case CONTOUR:
	{
		memcpy(quad->qd_brush.name, "SOLID", 11);
		quad2->qd_brush.color = RGBToColor(0, 0, 0);
		break;
	}

	case SHADED:
	{
		fscanf(file, "%s", &quad->qd_brush.name);

		int Red, Green, Blue;
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		quad->qd_brush.color = RGBToColor(Red, Green, Blue);
		
		break;
	}

	case DONUT:
	{
		fscanf(file, "%s", &quad->qd_brush.name);

		int Red, Green, Blue;
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		quad->qd_brush.color = RGBToColor(Red, Green, Blue);

		for (int i = 0; i < 4; i++)
			fscanf(file, "%d %d", &(quad2->points[i].x), &(quad2->points[i].y));

		fscanf(file, "%s", &quad2->qd_pen.name);

		fscanf(file, "%d", &quad2->qd_pen.width);

		int Red2, Green2, Blue2;
		fscanf(file, "%i %i %i", &Red2, &Green2, &Blue2);
		quad2->qd_pen.color = RGBToColor(Red2, Green2, Blue2);

		memcpy(quad2->qd_brush.name, "SOLID", 11);
		quad2->qd_brush.color = RGBToColor(0, 0, 0);
		break;
	}


	}

}

void Draw(HDC hdc, Quadrangle* quadrangle, Quadrangle* quad2)
{
	
	SelectObject(hdc, CreatePen(StringToPenStyle(quadrangle->qd_pen.name), quadrangle->qd_pen.width, quadrangle->qd_pen.color));

	switch (quadrangle->type)
	{

		case CONTOUR:
		{
			SelectObject(hdc, CreateHatchBrush(NULL_BRUSH, quadrangle->qd_brush.color));

			Polygon(hdc, quadrangle->points, 4);
			break;
		}
		case SHADED:
		{
			if (strcmp(quadrangle->qd_brush.name, "SOLID") == 0) 
			{
				SelectObject(hdc, CreateSolidBrush(quadrangle->qd_brush.color));
			}
			else
			{
				SelectObject(hdc, CreateHatchBrush(StringToBrushHash(quadrangle->qd_brush.name), quadrangle->qd_brush.color));
			}

			Polygon(hdc, quadrangle->points, 4);
			break;
		}
		case DONUT:
		{
			if (strcmp(quadrangle->qd_brush.name, "SOLID") == 0)
			{
				SelectObject(hdc, CreateSolidBrush(quadrangle->qd_brush.color));
			}
			else
			{
				SelectObject(hdc, CreateHatchBrush(StringToBrushHash(quadrangle->qd_brush.name), quadrangle->qd_brush.color));
			}
			SelectObject(hdc, CreatePen(StringToPenStyle(quadrangle->qd_pen.name), quadrangle->qd_pen.width, quadrangle->qd_pen.color));

			Polygon(hdc, quadrangle->points, 4);



			SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
			SelectObject(hdc, CreatePen(StringToPenStyle(quad2->qd_pen.name), quad2->qd_pen.width, quad2->qd_pen.color));

			Polygon(hdc, quad2->points, 4);
			
			break;
		}
	}




}

