#include "Error.h"

void Error:: PrintError(ERROR error)
{
	switch (error)
	{
	case INCORRECT_DRAW_TYPE:
	{
		printf("Неверно задан тип фигуры\n");
		break;
	}
	case INCORRECT_BRUSH:
	{
		printf("Неверно задан тип кисти\n");
		break;
	}
	case INCORRECT_PEN_STYLE:
	{
		printf("Неверно задан тип пера\n");
		break;
	}
	case OUT_FRAME:
	{
		printf("Координаты фигуры не входят в рамки окна\n");
		break;
	}
	case NOT_INCLUDED:
	{
		printf("Второй четырехугольник не вложен в первый\n");
		break;
	}
	case NOT_CONVEX:
	{
		printf("Координаты не удовлетворют условию выпуклого четырехугольника\n");
		break;
	}
	case THREE_POINTS_IN_LINE:
	{
		printf("В заданных кооринатах три точки лежат на одной прямой\n");
		break;
	}
	}

	_getch();
}