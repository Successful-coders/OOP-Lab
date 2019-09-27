#include "Error.h"

void Error:: PrintError(ERROR error)
{
	switch (error)
	{
	case INCORRECT_DRAW_TYPE:
	{
		printf("������� ����� ��� ������\n");
		break;
	}
	case INCORRECT_BRUSH:
	{
		printf("������� ����� ��� �����\n");
		break;
	}
	case INCORRECT_PEN_STYLE:
	{
		printf("������� ����� ��� ����\n");
		break;
	}
	case OUT_FRAME:
	{
		printf("���������� ������ �� ������ � ����� ����\n");
		break;
	}
	case NOT_INCLUDED:
	{
		printf("������ ��������������� �� ������ � ������\n");
		break;
	}
	case NOT_CONVEX:
	{
		printf("���������� �� ������������ ������� ��������� ����������������\n");
		break;
	}
	case THREE_POINTS_IN_LINE:
	{
		printf("� �������� ���������� ��� ����� ����� �� ����� ������\n");
		break;
	}
	}

	_getch();
}