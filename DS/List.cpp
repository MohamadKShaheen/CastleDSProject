#include "List.h"

template<class T>
List<T>::List()
{
	canMove = true;
	Head = NULL;
	Tail = NULL;
	ref = NULL;
	Count = 0;
}

template<class T>
int List<T>::getCurrentSize()
{
	return Count;
}

template<class T>
bool List<T>::isEmpty()
{
	return Head == NULL;
}

template<class T>
void List<T>::addItem(T V)
{
	if (!Head)		//case if the list is empty
	{
		Head = new Node<T>(V, NULL,NULL);
		Tail = Head;
		ref = Head;
	}
	else
	{		//general case
		Node<T>* temp = new Node<T>(V, NULL,Tail);
		Tail->changePtr(temp);
		Tail = Tail->getNext();
	}
	Count++;
}

template<class T>
bool List<T>::removeItem(T V)
{
	if (Head == NULL)		//case if list empty
		return false;
	if (ref->getValue() == V)		//if ref value equals to remove value
	{
		if (ref == Head)		//if ref equals to Head
		{
			if (Head == Tail)		//case there is one element in the list
			{
				delete Head;
				Head = NULL;
				Tail = NULL;
				ref = NULL;
				Count--;
				return true;
			}
			else
			{		//case more than one element but ref equals to Head
				Head = Head->getNext();		
				delete ref;
				ref = Head;
				canMove = false;			//for plus function
				Count--;
				return true;
			}
		}
		else if (ref == Tail)		//case if ref equals to Tail
		{
			ref = ref->getPrevious();
			ref->changePtr(NULL);
			delete Tail;
			Tail = ref;
			Count--;
			return true;
		}
		else
		{		//general case for ref value equals to remove value
			Node<T>* temp = ref;
			ref = ref->getPrevious();
			temp->getPrevious()->changePtr(temp->getNext());
			temp->getNext()->changePrv(temp->getPrevious());
			delete temp;
			Count--;
			return true;
		}
	}
	else
	{		//case if ref value not equals to remove value
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
			{		//case if there is more than one element and head value equals to remove value
				ref = Head;
				Head = Head->getNext();
				delete ref;
				ref = Head;
				canMove = false;			//for plus function
				Count--;
				return true;
			}
		}
		else if (Tail->getValue() == V)		//case if the tail value has the remove value
		{
			ref = Tail->getPrevious();
			ref->changePtr(NULL);
			delete Tail;
			Tail = ref;
			Count--;
			return true;
		}
		else
		{		//general case for the case of ref value not equals to remove value
			Node<T>* p = Head->getNext();
			while (p != NULL)	
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
void List<T>::clear()
{
	Node<T>* p = Head;
	while (p != NULL)
	{
		p = p->getNext();
		delete Head;
		Head = p;
	}
	Head = NULL;
	Tail = NULL;
	ref = NULL;
	Count = 0;
}

template<class T>
void List<T>::print()
{
	Node<T>* temp = Head;
	while (temp != NULL)
	{
		cout << temp->getValue() << endl;
		temp = temp->getNext();
	}
}

template<class T>
T List<T>::getref()
{
	if (ref != NULL) {
		return ref->getValue();
	}
	else
	{
		return NULL;
	}
}

template<class T>
void List<T>::plus()
{
	if (ref != nullptr) 
	{
		if (canMove)
		{
			ref = ref->getNext();
		}
		else
			canMove = true;
	}
}

template<class T>
void List<T>::AddToArr(T arr[], int& actSize, int maxSize)
{
	Node<T>*p = Head;
	while (p != nullptr && actSize != maxSize)
	{
		arr[actSize++] = p->getValue();
		p = p->getNext();
	}
}

template<class T>
void List<T>::startLoop()
{
	ref = Head;
	canMove = true;
}

template<class T>
void List<T>::addList(List<T> & add)
{
	Node<T> * p;
	p = add.Head;
	List<T> ad;
	while (p)
	{
		ad.addItem(p->getValue());
		p = p->getNext();
	}
	if (!ad.Head)
		return;
	ad.Head->changePrv(Tail);
	if (Head)
	{
		Tail->changePtr(ad.Head);
	}
	else
	{
		Head = ad.Head;
	}
	Tail = ad.Tail;
	Count += ad.Count;
}

template<class T>
List<T>::~List()
{
}