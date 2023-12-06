#include "PNode.h"


template<class T>
PNode<T>::PNode(T &V, int P, PNode<T>* Pointer,PNode<T>* Previous)
{
	Value = V;
	Priorty = P;
	Ptr = Pointer;
	Prv = Previous;
}

template<class T>
PNode<T> * PNode<T>::getNext()
{
	return Ptr;
}

template<class T>
PNode<T>* PNode<T>::getPrevious()
{
	return Prv;
}

template<class T>
const T & PNode<T>::getValue()
{
	return Value;
}

template<class T>
void PNode<T>::changePtr(PNode<T>* P)
{
	Ptr = P;
}

template<class T>
void PNode<T>::changePrv(PNode<T>* P)
{
	Prv = P;
}

template<class T>
int PNode<T>::getPriorty()
{
	return Priorty;
}

template<class T>
void PNode<T>::setPriorty(int P)
{
	Priorty = P;
}

template<class T>
PNode<T>::~PNode()
{

}
