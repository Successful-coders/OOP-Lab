///////////////////////////////////////////////////////////
//  Brush.h
//  Implementation of the Class Brush
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Darya
///////////////////////////////////////////////////////////

#if !defined(EA_C414F92A_D0CB_46e6_ADCB_EA186BFD1101__INCLUDED_)
#define EA_C414F92A_D0CB_46e6_ADCB_EA186BFD1101__INCLUDED_

class Brush
{

public:
	virtual ~Brush();

	Brush();
	Brush(const char* name);
	Brush(char* name, COLORREF color);
	COLORREF GetColor();
	char* Getname();
	void SetColor(COLORREF color);
	void SetName(char* name);

private:
	COLORREF color;
	char name[16];

};
#endif // !defined(EA_C414F92A_D0CB_46e6_ADCB_EA186BFD1101__INCLUDED_)
