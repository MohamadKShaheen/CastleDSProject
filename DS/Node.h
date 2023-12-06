#pragma once
template<class T>
class Node
{
	T Value;			//the value of the node
	Node<T>* Ptr;		//pointer to next node
	Node<T>* Prv;
public:
	Node(T &V, Node<T>* P,Node<T>* P2);	//non-default constructor 
	Node<T>* getNext();					//get the next pointer
	Node<T>* getPrevious();				//get the previous pointer
	T& getValue();						//get the value of the node
	void changePtr(Node<T>* P);			//change the next pointer
	void changePrv(Node<T>* P);			//change the previous pointer
	~Node();							//default destructor
};

	