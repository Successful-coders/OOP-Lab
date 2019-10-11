#include "QD.h"
#include "QdCountour.h"
#include <cstddef>
#include <utility>

template <typename T>
class DoubleLinkedList 
{
	struct node
	{
		T value;
		node* prev;
		node* next;
	};

public:
	DoubleLinkedList();
	~DoubleLinkedList();

	T GetElement(int index);
	void PushElement(T elemnent);
	T* PopElement(T element);
private:
	node* head;
	void Init(node *initNode);
};