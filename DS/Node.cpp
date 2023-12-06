#include "Node.h"

template<class T>
Node<T>::Node(T &V,Node<T>* P,Node<T>* P2)
{
	Value = V;
	Ptr = P;
	Prv = P2;
}

template<class T>
Node<T>* Node<T>::getNext()
{
	return Ptr;
}

template<class T>
Node<T>* Node<T>::getPrevious()
{
	return Prv;
}

template<class T>
T& Node<T>::getValue()
{
	return Value;
}

template<class T>
void Node<T>::changePtr(Node<T>* P)
{
	Ptr = P;
}

template<class T>
void Node<T>::changePrv(Node<T>* P)
{
	Prv = P;
}

template<class T>
Node<T>::~Node()
{
}
