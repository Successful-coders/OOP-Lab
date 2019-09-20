//Main.cpp
#include "Qd.h"



void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	FILE* file = fopen("test.txt", "r");

	Quadrangle quad, quad2;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	SetBkColor(hdc, RGB(0, 0, 0));
	char type[15];
	fscanf(file, "%s", &type);
	try
	{
		quad->type = StringToEnum(type);
	}
	catch (ERROR error)
	{
		return PrintError(error);
	}


	for (int i = 0; i < 4; i++)
	{
		fscanf(file, "%d %d", &(quad->points[i].x), &(quad->points[i].y));
	}

	fscanf(file, "%s", &(quad->qd_pen.name));
	fscanf(file, "%d", &(quad->qd_pen.width));

	int Red, Green, Blue;
	fscanf(file, "%i %i %i", &Red, &Green, &Blue);
	quad->qd_pen.color = RGB(Red, Green, Blue);

	switch (quad->type)
	{
	case CONTOUR:
	{
		memcpy(quad->qd_brush.name, "SOLID", 11);
		quad->qd_brush.color = GetBkColor(hdc);
		break;
	}

	case SHADED:
	{
		fscanf(file, "%s", &quad->qd_brush.name);

		int Red, Green, Blue;
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		quad->qd_brush.color = RGB(Red, Green, Blue);
		break;
	}

	case DONUT:
	{
		fscanf(file, "%s", &quad->qd_brush.name);

		int Red, Green, Blue;
		fscanf(file, "%i %i %i", &Red, &Green, &Blue);
		quad->qd_brush.color = RGB(Red, Green, Blue);

		for (int i = 0; i < 4; i++)
			fscanf(file, "%d %d", &(quad2->points[i].x), &(quad2->points[i].y));

		fscanf(file, "%s", &quad2->qd_pen.name);

		fscanf(file, "%d", &quad2->qd_pen.width);

		int Red2, Green2, Blue2;
		fscanf(file, "%i %i %i", &Red2, &Green2, &Blue2);
		quad2->qd_pen.color = RGB(Red2, Green2, Blue2);

		memcpy(quad2->qd_brush.name, "SOLID", 11);
		quad2->qd_brush.color = GetBkColor(hdc);
		break;
	}
	}

	
	fclose(file);

	do
	{
		switch (quad.type)
		{
		case CONTOUR:
		{
			DrawContour(hdc, hwnd);

			break;
		}
		case SHADED:
		{

			DrawShaded(hdc, hwnd);

			break;
		}
		case DONUT:
		{

			DrawDonut(hdc, hwnd);
			break;
		}
		}
	} while (getch() != 27);
}

