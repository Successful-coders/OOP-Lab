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

	do
	{
		Draw(hdc, hwnd, quad, quad2);

		fclose(file);
	} while (getch() != 27);
}

