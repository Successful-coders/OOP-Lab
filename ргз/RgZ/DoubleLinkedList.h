///////////////////////////////////////////////////////////
//  DoubleLinkedList.h
//  Implementation of the Class DoubleLinkedList
//  Created on:      14-ноя-2019 13:08:27
//  Original author: Darya
///////////////////////////////////////////////////////////

#if !defined(EA_8D5965E3_72E9_4c5c_B995_2DB7B00D5A5F__INCLUDED_)
#define EA_8D5965E3_72E9_4c5c_B995_2DB7B00D5A5F__INCLUDED_

#include "node.h"

class DoubleLinkedList
{

public:
	node *m_node;

	DoubleLinkedList();
	~DoubleLinkedList();
	void DeleteElement(int indexs);
	T GetElement(int index);
	int GetLength();
	void PushElement(T element);

private:
	node* head;
	int lenght;
	node node;

};
#endif // !defined(EA_8D5965E3_72E9_4c5c_B995_2DB7B00D5A5F__INCLUDED_)
