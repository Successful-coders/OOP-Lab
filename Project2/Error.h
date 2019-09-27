#pragma once
#include "QD.h"
#undef ERROR
enum ERROR
{
	INCORRECT_DRAW_TYPE,
	INCORRECT_BRUSH,
	INCORRECT_PEN_STYLE,
	OUT_FRAME,
	NOT_INCLUDED,
	NOT_CONVEX,
	THREE_POINTS_IN_LINE,
};
class Error
{
public:
	static void PrintError(ERROR error);
};