#pragma once
#include "Node.cpp"
#include <iostream>


using namespace std;
template<class T>
class List
{
	bool canMove;
	Node<T>* Head;		//pointer for the first element in the list
	Node<T>* Tail;		//pointer for the last element in the list
	Node<T>* ref;		//pointer  to loop the list without starting from the first element every time
	int Count;			//number of elements

public:
	List();					//default constructor set all pointers to NULL & Count = 0
	int getCurrentSize();	//get the size of the list
	bool isEmpty();			//check if the list is empty
	void addItem(T V);		//add new item to the list
	bool removeItem(T V);	//remove a specific item (in most cases it will be the ref value)
	void clear();			//remove all elements
	void print();			//print the values of the elements in the list				
	T getref();				//return the value of the ref
	void plus();			//make the ref points to its next node
	void AddToArr(T arr[], int &actSize, int maxSize);		//add the values to array and return it
	void startLoop();		//make the ref points to head
	void addList(List<T>& add);
	~List();				//default destructor
};

