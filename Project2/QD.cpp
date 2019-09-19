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

void Read_Characteristics(Quadrangle* quad, FILE *file, Quadrangle* quad2, HDC hdc)
{
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
		quad2->qd_brush.color = GetBkColor(hdc);
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

void Draw(HDC hdc, HWND hwnd, Quadrangle* quadrangle, Quadrangle* quad2)
{
	
	if (IsQuadrangle(quadrangle) && IsInFrame(hwnd, quadrangle))
	{
		HPEN hRedPen = CreatePen(StringToPenStyle(quadrangle->qd_pen.name), quadrangle->qd_pen.width, quadrangle->qd_pen.color);
		HPEN hOldPen = SelectPen(hdc, hRedPen);
		HBRUSH hGreenBrush = CreateSolidBrush(quadrangle->qd_brush.color);
		HBRUSH hOldBrush = SelectBrush(hdc, hGreenBrush);

		//SelectObject(hdc, hOldPen);

		switch (quadrangle->type)
		{

			case CONTOUR:
			{
				//SelectObject(hdc, CreateHatchBrush(NULL_BRUSH, quadrangle->qd_brush.color));

				Polygon(hdc, quadrangle->points, 4);
				break;
			}
			case SHADED:
			{
				if (strcmp(quadrangle->qd_brush.name, "SOLID") == 0)
				{
					HBRUSH hNewBrush = CreateSolidBrush(quadrangle->qd_brush.color);
					//SelectObject(hdc, CreateSolidBrush(quadrangle->qd_brush.color));
				}
				else
				{
					HBRUSH hNewBrush = CreateHatchBrush(StringToBrushHash(quadrangle->qd_brush.name), quadrangle->qd_brush.color);
					//SelectObject(hdc, CreateHatchBrush(StringToBrushHash(quadrangle->qd_brush.name), quadrangle->qd_brush.color));
				}

				Polygon(hdc, quadrangle->points, 4);
				break;
			}
			case DONUT:
			{
				if (IsQuadrangle(quad2) && IsDonut(quadrangle, quad2))
				{
					if (strcmp(quadrangle->qd_brush.name, "SOLID") == 0)
					{
						HBRUSH hNewBrush = CreateSolidBrush(quadrangle->qd_brush.color);
						//SelectObject(hdc, CreateSolidBrush(quadrangle->qd_brush.color));
					}
					else
					{
						HBRUSH hNewBrush = CreateHatchBrush(StringToBrushHash(quadrangle->qd_brush.name), quadrangle->qd_brush.color);
						//SelectObject(hdc, CreateHatchBrush(StringToBrushHash(quadrangle->qd_brush.name), quadrangle->qd_brush.color));
					}
					HPEN hNewPen = CreatePen(StringToPenStyle(quadrangle->qd_pen.name), quadrangle->qd_pen.width, quadrangle->qd_pen.color);
					//SelectObject(hdc, CreatePen(StringToPenStyle(quadrangle->qd_pen.name), quadrangle->qd_pen.width, quadrangle->qd_pen.color));

					Polygon(hdc, quadrangle->points, 4);



					HBRUSH hNewBrush = CreateSolidBrush(RGB(0, 0, 0));
					//SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));

					HPEN hNewPen2 = CreatePen(StringToPenStyle(quad2->qd_pen.name), quad2->qd_pen.width, quad2->qd_pen.color);
					//SelectObject(hdc, CreatePen(StringToPenStyle(quad2->qd_pen.name), quad2->qd_pen.width, quad2->qd_pen.color));

					Polygon(hdc, quad2->points, 4);

					break;
				}

			}
		}


	}
}

bool IsQuadrangle(Quadrangle* quad)
{
	if (quad->points[0].x - quad->points[1].x)
	{
		float k;
		k = (float)(quad->points[0].y - quad->points[1].y) / (float)(quad->points[0].x - quad->points[1].x);
		float b = quad->points[0].y - k * quad->points[0].x;
		float y1 = k * quad->points[2].x + b;
		float y2 = k * quad->points[3].x + b;
		if (y1 == quad->points[2].y || y2 == quad->points[3].y)
		{
			printf("В заданных кооринатах три точки лежат на одной прямой. \n");
			return false;
		}
		if ((y1 > (float)quad->points[2].y && y2 > (float)quad->points[3].y) || (y1 < (float)quad->points[2].y && y2 < (float)quad->points[3].y))
			return true;
		else
		{
			printf("Координаты не удовлетворют условию выпуклого четырехугольника.\n");
			return false;
		}

	}
	else
	{
		if (quad->points[2].x == quad->points[0].x || quad->points[3].x == quad->points[0].x)
		{

			printf("В заданных кооринатах три точки лежат на одной прямой. \n");
			return false;
		}
		if ((quad->points[0].x > quad->points[2].x && quad->points[1].x > quad->points[3].x) || (quad->points[0].x < quad->points[2].x && quad->points[1].x < quad->points[3].x))
			return true;
		else
		{
		printf("Координаты не удовлетворют условию выпуклого четырехугольника.\n");
		return false;
		}
	}

	return true;
}

bool IsInFrame(HWND hwnd, Quadrangle *qd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	for (int i = 0; i < 4; i++)
	{
		if (qd->points[i].x > rt.right || qd->points[i].y > rt.bottom || qd->points[i].x < 0 || qd->points[i].y < 0)
		{
			printf_s("Координаты фигуры не входят в рамки окна \n");
			return false;
		}
	}

	return true;
}

bool IsDonut(Quadrangle* quad1, Quadrangle* quad2)
{
	for (int i = 0; i < 4; i++)
	{
		if (!IsInQuadrangle(quad1->points[0], quad1->points[1], quad1->points[2], quad1->points[3], quad2->points[i]))
		{
			printf("Не вложен");
			return false;
		}
	}

	return true;
}

bool IsInQuadrangle(POINT P1, POINT P2, POINT P3, POINT P4, POINT PTest)
{
	int a = (P1.x - PTest.x) * (P2.y - P1.y) - (P2.x - P1.x) * (P1.y - PTest.y);
	int b = (P2.x - PTest.x) * (P3.y - P2.y) - (P3.x - P2.x) * (P2.y - PTest.y);
	int c = (P3.x - PTest.x) * (P4.y - P3.y) - (P4.x - P3.x) * (P3.y - PTest.y);
	int d = (P4.x - PTest.x) * (P1.y - P4.y) - (P1.x - P4.x) * (P4.y - PTest.y);

	if ((a >= 0 && b >= 0 && c >= 0 && d >= 0) || (a <= 0 && b <= 0 && c <= 0 && d <= 0))
		return true;
	else
		return false;
}