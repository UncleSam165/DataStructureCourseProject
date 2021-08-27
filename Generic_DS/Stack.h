#pragma once
#include "Node.h"
template<typename T>
class Stack
{
private:
	Node<T>* top;

public:
	Stack();
	bool isEmpty() const;
	bool push(const T& newItem);
	bool pop(T& TopEntry);
	bool peek(T& topEntry);
	void print();
	const T* toArray(int& count);
};

template<typename T>
Stack<T>::Stack() :top(nullptr) {}

template<typename T>
bool Stack<T>::isEmpty() const
{
	if (top == nullptr)
		return true;
	else
		return false;
}

template<typename T>
bool Stack<T>::push(const T& newItem)
{
	Node<T>* newNode = new Node<T>(newItem);
	if (isEmpty())
	{
		top = newNode;
		newNode->setNext(nullptr);
	}
	else
	{
		newNode->setNext(top);
		top = newNode;
	}
	return true;
}

template<typename T>
bool Stack<T>::pop(T& TopEntry)
{
	if (isEmpty())
		return false;
	else
	{
		Node<T>* nodeToDeletePtr = top;
		TopEntry = top->getItem();
		top = top->getNext();
		delete nodeToDeletePtr;
	}
	return true;
}

template<typename T>
bool Stack<T>::peek(T& topEntry)
{
	if (isEmpty())
	{
		return false;
	}
	else
	{
		topEntry = top->getItem();
	}
	return true;
}

template<typename T>
void Stack<T>::print()
{
	if (isEmpty())
		cout << "Stack is empty";
	else
	{
		Node<T>* temp = top;
		while (temp != nullptr)
		{
			cout << temp->getItem() << endl;
			temp = temp->getNext();
		}
	}
}

template <typename T>
const T* Stack<T>::toArray(int& count)
{

	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

	count = 0;

	if (!top)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = top;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = top;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;

}
