#pragma once
#include "PQ_Node.h" 
template <class T1, class T2>
class PriorityQ
{
	PQ_Node<T1, T2>* front;
public:
	PriorityQ();
	bool isEmpty() const;
	bool enqueue(const T1& newItem, const T2& newPriority);
	bool dequeue(T1& frntEntry);
	bool peekFront(T1& frntEntry)  const;
	void print();
	const T1* toArray(int& count);
	~PriorityQ();
};

template <class T1, class T2>
PriorityQ<T1,T2>::PriorityQ() :front(nullptr) {}

template <class T1, class T2>
bool PriorityQ<T1, T2>::isEmpty() const
{
	if (front == nullptr)
		return true;
	else
		return false;
}

template <class T1, class T2>
bool PriorityQ<T1, T2>::enqueue(const T1& newItem, const T2& newPriority)
{
	PQ_Node<T1, T2>* newNode = new PQ_Node<T1, T2>(newItem, newPriority);
	if (isEmpty())
		front = newNode; 
	else if (newPriority > front->getPriority())
	{
		newNode->setNext(front);
		front = newNode;
	}
	else
	{
		PQ_Node<T1, T2>* temp = front;
		while (temp->getNext() != nullptr && temp->getNext()->getPriority() >= newPriority)
		{
			temp = temp->getNext();
		}
		newNode->setNext(temp->getNext());
		temp->setNext(newNode);
	}
	return true;
}

template <class T1, class T2>
bool PriorityQ<T1, T2>::dequeue(T1& frntEntry)
{
	if (isEmpty())
		return false;
	else
	{
		PQ_Node<T1, T2>* nodeToDeletePtr = front;
		frntEntry = front->getItem();
		front = front->getNext();
		delete nodeToDeletePtr;
	}
	return true;
}

template <class T1, class T2>
bool PriorityQ<T1, T2>::peekFront(T1& frntEntry)  const
{
	if (isEmpty())
		return false;

	frntEntry = front->getItem();
	return true;
}

template <class T1, class T2>
void PriorityQ<T1, T2>::print()
{
	if (isEmpty())
	{
		cout << "PriorityQ is empty";
	}
	else
	{
		PQ_Node<T1, T2>* temp = front;
		while (temp != nullptr)
		{
			cout << temp->getItem() << endl;
			temp = temp->getNext();
		}
	}
}

template <class T1, class T2>
const T1* PriorityQ<T1, T2>::toArray(int& count)
{
	count = 0;

	if (!front)
		return nullptr;
	//counting the no. of items in the Queue
	PQ_Node<T1, T2>* p = front;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T1* Arr = new T1[count];
	p = front;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

template <class T1, class T2>
PriorityQ<T1, T2>::~PriorityQ(){}
