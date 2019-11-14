///////////////////////////////////////////////////////////
//  Error.h
//  Implementation of the Class Error
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Darya
///////////////////////////////////////////////////////////

#if !defined(EA_82650FA8_E5F0_47ff_AFC0_364A4B9D264E__INCLUDED_)
#define EA_82650FA8_E5F0_47ff_AFC0_364A4B9D264E__INCLUDED_

class Error
{

public:
	Error();
	virtual ~Error();

	static void PrintError(ERROR errror);

};
#endif // !defined(EA_82650FA8_E5F0_47ff_AFC0_364A4B9D264E__INCLUDED_)
