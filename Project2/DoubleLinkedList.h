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
	void PopElement();
	int GetLength();

private:
	struct node
	{
		T value;
		node* prev;
		node* next;
	};

	node* head;
	int length;
};


template <class T>
DoubleLinkedList <T> ::DoubleLinkedList()
{
	length = 0;
	head = new node;
	head->value = T();
	head->next = NULL;
	head->prev = NULL;
}

template <class T>
DoubleLinkedList <T> ::~DoubleLinkedList()
{
	while (head->prev!= NULL&& head->next!=NULL)
	{
		node* deletedNode = head;
		head = head->next;
		free (deletedNode);
	}
}

template <class T>
void DoubleLinkedList <T> ::PushElement(T element)
{
	length++;

	node* temp, * p;
	temp = new node;
	p = head->next;
	head->next = temp;
	temp->value = element;
	temp->next = p;
	temp->prev = head;
	if (p != NULL)
		p->prev = temp;
	head = temp;
}

template <class T>
T DoubleLinkedList <T> ::GetElement(int index)
{
	node *savehead = head;
	if (this->length == 1)
		return head->value;
	for (int i = 0; i != index && savehead->prev->prev != NULL ; i++)
	{
		savehead = savehead->prev;
	}
	return savehead->value;
}

template <class T>
void DoubleLinkedList <T> ::PopElement()
{
	node* prev, * next;
	prev = head->prev;
	next = head->next;
	if (prev != NULL)
		prev->next = head->next;
	if (next != NULL)
		next->prev = head->prev;
	free(head);
	head = prev;
}

template<class T>
inline int DoubleLinkedList<T>::GetLength()
{
	return this->length;
}