///////////////////////////////////////////////////////////
//  Figure.cpp
//  Implementation of the Class Figure
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Жопчики
///////////////////////////////////////////////////////////

#include "Figure.h"


Figure::Figure(){

}



Figure::~Figure(){

}





virtual void Figure::CheckInFrame(HWND hwnd){

	return  NULL;
}


virtual void Figure::Draw(HWND hwnd){

	return  NULL;
}


Pen Figure::GetPen(){

	return  NULL;
}


virtual void Figure::Move(HWND hwnd, int x, int y){

	return  NULL;
}


virtual void Figure::Save(FILE* saveFile){

	return  NULL;
}


void Figure::SetPen(char* name, int width, COLORREF color){

}