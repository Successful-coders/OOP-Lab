#include "Qd.h"

void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	FILE* file = fopen("test.txt", "r");
	Quadrangle *quad = new Quadrangle, *quad2 = new Quadrangle;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	RECT rt;

	char type[15];
	fscanf(file, "%s", &type);
	quad->type = StringToEnum(type);
	Read_Characteristics(quad, file, quad2);

	do
	{
		Draw(hdc, quad, quad2);

		fclose(file);

	} while (getch() != 27);
}

