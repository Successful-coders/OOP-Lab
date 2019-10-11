#pragma once
#include <stdlib.h>

template <class T>
class DoubleLinkedList
{
public:
	DoubleLinkedList();
	~DoubleLinkedList();

	T GetElement(int index);
	void PushElement(T elemnent);
	T PopElement();

private:
	struct node
	{
		T value;
		node* prev;
		node* next;
	};

	node* head;
};


template <class T>
DoubleLinkedList <T> ::DoubleLinkedList()
{
	head = new node;
	head->value = T();
	head->next = head;
	head->prev = head;
}

template <class T>
DoubleLinkedList <T> ::~DoubleLinkedList()
{
	while (head != NULL)
	{
		node* deletedNode = head;
		head = head->next;
		delete deletedNode;
	}
}

template <class T>
void DoubleLinkedList <T> ::PushElement(T element)
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

template <class T>
T DoubleLinkedList <T> ::GetElement(int index)
{

}

template <class T>
T DoubleLinkedList <T> ::PopElement()
{

}