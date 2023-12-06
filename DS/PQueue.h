#pragma once
#include"PNode.cpp"

template<class T>
class PQueue
{
	PNode<T>* Head;
	PNode<T>* Tail;
	PNode<T>* ref;
	int Count;

public:
	PQueue();					//default constructor
	int getCurrentSize();		//get the size of the list
	bool isEmpty();				//check if the list is empty
	void addItem(T V,int p);	//add new item to the list
	bool removeItem(T V);		//remove a specific item or the first item
	void clear();				//delete all elements
	void print();				//print all values of the nodes
	void AddToArr(T arr[], int &actSize, int maxSize);		//add the elements to array and return it
	void startLoop();			//make the ref pionts to head
	PNode<T>* sort(PNode<T>* a, PNode<T>* b);		//sort to lists with reference to proirty
	void split(PNode<T>* src, PNode<T>* &first, PNode<T>* &second);		//split a list to two lists
	void mergeSort(PNode<T>*& ptr);		//sort a list
	void Sort();				//sort a list  (without parameters)
	~PQueue();					//default destructor
	T getref();					//return the value of the ref
	void plus();				//make the ref points to its next node
};

