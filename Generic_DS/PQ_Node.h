#pragma once
template <class T1, class T2>
class PQ_Node
{
	T1 Item; 
	T2 Priority;
	PQ_Node<T1, T2>* next;
public:
	PQ_Node():next(nullptr){}
	PQ_Node(const T1& newItem, const T2& newPriority)
	{
		Item = newItem;
		Priority = newPriority;
		next = nullptr;
	}
	PQ_Node(const T1& newItem, const T2& newPriority, PQ_Node<T1, T2>* nodePtr)
	{
		Item = newItem;
		Priority = newPriority;
		next = nodePtr;
	}
	void setItem(const T1& newItem) { Item = newItem; }
	
	
	T1 getItem() const
	{
		return Item;
	}
	
	
	void setPriority(const T2& newPriority) { Priority = newPriority; }
	
	
	T2 getPriority() const
	{
		return Priority;
	}
	
	void setNext(PQ_Node<T1, T2>* nodePtr) { next = nodePtr; }
	
	PQ_Node<T1, T2>* getNext() const
	{
		return next;
	}
};
