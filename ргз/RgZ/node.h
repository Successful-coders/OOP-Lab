///////////////////////////////////////////////////////////
//  node.h
//  Implementation of the Class node
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Жопчики
///////////////////////////////////////////////////////////

#if !defined(EA_F27657A5_7389_43b0_94AC_F382631D253F__INCLUDED_)
#define EA_F27657A5_7389_43b0_94AC_F382631D253F__INCLUDED_

class node
{

public:
	node();
	virtual ~node();

private:
	node* next;
	node* prev;
	T value;

};
#endif // !defined(EA_F27657A5_7389_43b0_94AC_F382631D253F__INCLUDED_)
