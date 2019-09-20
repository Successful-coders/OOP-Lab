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

	Read_Characteristics(&quad, file, &quad2, hdc);
	fclose(file);

	do
	{
		switch (quad.type)
		{
		case CONTOUR:
		{
			DrawContour(hdc, hwnd, quad);

			break;
		}
		case SHADED:
		{

			DrawShaded(hdc, hwnd, quad);

			break;
		}
		case DONUT:
		{

			DrawDonut(hdc, hwnd, quad, quad2);
			break;
		}
		}
	//	Draw(hdc, hwnd, quad, quad2);

	} while (getch() != 27);
}

