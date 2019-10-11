#include "QD.h"
#include "QdCountour.h"
#include "QdDonut.h"
#include "QdShaded.h"
#include "DoubleLinkedList.h"
template <typename T>
DoubleLinkedList <T> ::DoubleLinkedList()
{
	Init(head);
}

template <typename T>
DoubleLinkedList <T> ::~DoubleLinkedList()
{
	while (head!=NULL)
	{
		node *deletedNode = head;
		head = head->next;
		delete deletedNode;
	}
}

template <typename T>
void DoubleLinkedList <T> :: PushElement(T element)
{	
	if (head->next != head->prev)
	{
		node* lastElement = head->prev;
		
		lastElement->next = new node;
		lastElement->next->value = element;
		lastElement->next->next = head;
		lastElement->next->prev = lastElement;
	}
	else
	{
		head->next = new node;
		head->next->value = element;
		head->next->next = head;
		head->next->prev = head;
	}
}

template <typename T>
void  DoubleLinkedList <T> :: Init(node *initNode)
{
	initNode = new node;
	initNode->value = T();
	initNode->next = initNode->prev;
	initNode->prev = initNode->next;
}