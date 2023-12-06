#pragma once
template<class T>
class PNode
{
	T Value;			//value of the node
	int Priorty;		//priorty of the node
	PNode<T>* Ptr;		//pointer to the next node
	PNode<T>* Prv;		//pointer to the previous node
public:
	PNode(T &V, int P, PNode<T>* Pointer, PNode<T>* Previous);	//non-default constructor
	PNode<T>* getNext();					//return the next pointer
	PNode<T>* getPrevious();				//return the previous pointer
	const T & getValue();					//return the value of the node
	void changePtr(PNode<T>* P);			//change the next pointer
	void changePrv(PNode<T>* P);			//change the previous pointer
	int getPriorty();						//return the priorty of the node
	void setPriorty(int P);					//change the pointer
	~PNode();								//default destructor
};

