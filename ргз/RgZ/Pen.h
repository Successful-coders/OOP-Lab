///////////////////////////////////////////////////////////
//  Pen.h
//  Implementation of the Class Pen
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Darya
///////////////////////////////////////////////////////////

#if !defined(EA_41F0F467_B650_4d58_B3D1_E7B021569DFD__INCLUDED_)
#define EA_41F0F467_B650_4d58_B3D1_E7B021569DFD__INCLUDED_

class Pen
{

public:
	virtual ~Pen();

	Pen();
	Pen(char *name, int width, COLORREF color);
	COLORREF GetColor();
	char* GetName();
	int GetWidth();
	void SetColor(COLORREF color);
	void SetName(char* name);
	void SetWidth(int width);

private:
	COLORREF color;
	char name[16];
	int width;

};
#endif // !defined(EA_41F0F467_B650_4d58_B3D1_E7B021569DFD__INCLUDED_)
