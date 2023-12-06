#include "PQueue.h"
#include <iostream>

template<class T>
PQueue<T>::PQueue()
{
	Head = NULL;
	Tail = NULL;
	ref = NULL;
	Count = 0;
}

template<class T>
int PQueue<T>::getCurrentSize()
{
	return Count;
}

template<class T>
bool PQueue<T>::isEmpty()
{
	return Head == NULL;
}

template<class T>
void PQueue<T>::addItem(T V,int p)
{
	if (!Head)
	{
		Head = new PNode<T>(V, p, NULL,NULL);
		Tail = Head;
		ref = Head;
	}
	else
	{
		PNode<T>* temp = new PNode<T>(V, p, NULL,Tail);
		Tail->changePtr(temp);
		Tail = Tail->getNext();
	}
	Count++;
}

template<class T>
bool PQueue<T>::removeItem(T V)
{
	if (Head == NULL)
		return false;
	if (ref->getValue() == V)
	{
		if (ref == Head)
		{
			if (Head == Tail)
			{
				delete Head;
				Head = NULL;
				Tail = NULL;
				ref = NULL;
				Count--;
				return true;
			}
			else
			{
				Head = Head->getNext();
				Count--;
				return true;
			}
		}
		else if (ref == Tail)
		{
			ref = ref->getPrevious();
			ref->changePtr(NULL);
			delete Tail;
			Tail = ref;
			Count--;
			return true;
		}
		else
		{
			PNode<T>* temp = ref;
			ref = ref->getPrevious();
			temp->getPrevious()->changePtr(temp->getNext());
			temp->getNext()->changePrv(temp->getPrevious());
			delete temp;
			Count--;
			return true;
		}
	}
	else
	{
		if (Head->getValue() == V) //case if the head has the value
		{
			if (Head == Tail)	//case there is one element in the list
			{
				delete Head;
				Tail = NULL;
				ref = NULL;
				Head = NULL;
				Count--;
				return true;
			}
			else
			{
				ref = Head;
				Head = Head->getNext();
				Count--;
				return true;
			}
		}
		else if (Tail->getValue() == V)
		{
			ref = Tail->getPrevious();
			ref->changePtr(NULL);
			delete Tail;
			Tail = ref;
			Count--;
			return true;
		}
		else
		{
			PNode<T>* p = Head->getNext();
			while (p != NULL)	//general case
			{
				if (p->getValue() == V)
				{
					ref = p->getPrevious();
					p->getPrevious()->changePtr(p->getNext());
					p->getNext()->changePrv(p->getPrevious());
					delete p;
					Count--;
					return true;
				}
				else
					p = p->getNext();
			}
		}
	}
	return false;
}

template<class T>
void PQueue<T>::clear()
{
	PNode<T>* p = Head;
	while (p != NULL)
	{
		p = p->getNext();
		delete Head;
		Head = p;
	}
	Count = 0;
}

template<class T>
void PQueue<T>::print()
{
	PNode<T>* temp = Head;
	while (temp != NULL)
	{
		cout << temp->getValue() << endl;
		temp = temp->getNext();
	}
}

template<class T>
void PQueue<T>::AddToArr(T arr[], int& actSize, int maxSize)
{
	PNode<T>*p = Head;
	while (p != NULL && actSize != maxSize)
	{
		arr[actSize++] = p->getValue();
		p = p->getNext();
	}
}

template<class T>
void PQueue<T>::startLoop()
{
	ref = Head;
}

template<class T>
PNode<T>* PQueue<T>::sort(PNode<T>* a, PNode<T>* b)
{
	PNode<T>* final1 = NULL;
	//the base case
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (a->getPriorty() >= b->getPriorty())		//sorting with refernce to proirty
	{
		final1 = a;
		final1->changePtr(sort(a->getNext(), b));
	}
	else
	{
		final1 = b;
		final1->changePtr(sort(a, b->getNext()));
	}

	return final1;
}

template<class T>
void PQueue<T>::split(PNode<T>* src, PNode<T>* &first, PNode<T>* &second)
{
	PNode<T>* fast;
	PNode<T>* slow;
	if (src == NULL || src->getNext() == NULL)		//if the src of the list or its next equals to null
	{
		first = src;
		second = NULL;
	}
	else
	{
		slow = src;
		fast = src->getNext();
		while (fast != NULL)
		{
			fast = fast->getNext();
			if (fast != NULL)
			{
				slow = slow->getNext();
				fast = fast->getNext();
			}
		}
		first = src;
		second = slow->getNext();
		slow->changePtr(NULL);
	}//make the fast go two times and the slow one time every time to split the list into tow lists
}

template<class T>
void PQueue<T>::mergeSort(PNode<T>* &ptr)
{
	PNode<T>* head = ptr;
	PNode<T>* a;
	PNode<T>* b;

	if (head == NULL || head->getNext() == NULL)		//the base case
		return;

	split(head, a, b);

	mergeSort(a);
	mergeSort(b);

	ptr = sort(a, b);
}

template<class T>
void PQueue<T>::Sort()
{
	mergeSort(Head);
	if (Tail != NULL)
	{
		while (Tail->getNext() != NULL)
		{
			Tail = Tail->getNext();
		}
	}
	if (Head != NULL)
	{
		Head->changePrv(NULL);
		PNode<T>* P = Head->getNext();
		while (P&&P->getNext())
		{
			P->getNext()->changePrv(P);
			P = P->getNext();
		}
	}
}

template<class T>
PQueue<T>::~PQueue()
{
}

template<class T>
T PQueue<T>::getref()
{
	if (ref != NULL) {
		return ref->getValue();
	}
	else
	{
		return nullptr;
	}
}
template<class T>
void PQueue<T>::plus()
{
	if (ref != nullptr)
	{
		if (ref->getNext() == Head)
		{
			PNode<T>* temp = ref;
			ref = ref->getNext();
			delete temp;
			Head->changePrv(NULL);
		}
		else
			ref = ref->getNext();
	}
	else
	{
		ref = nullptr;
	}
}