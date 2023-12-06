#include "PList.h"

template<class T>
PList<T>::PList()
{
	canMove = true;
	Head = NULL;
	Tail = NULL;
	ref = NULL;
	Count = 0;
}

template<class T>
int PList<T>::getCurrentSize()
{
	return Count;
}

template<class T>
bool PList<T>::isEmpty()
{
	return Head == NULL;
}

template<class T>
void PList<T>::addItem(T V,int p)
{
	if (!Head)			//case if list is empty
	{
		Head = new PNode<T>(V, p, NULL,NULL);
		Tail = Head;
		ref = Head;
	}
	else
	{		//general case
		PNode<T>* temp = new PNode<T>(V, p, NULL,Tail);
		Tail->changePtr(temp);
		Tail = Tail->getNext();
	}
	Count++;
}

template<class T>
bool PList<T>::removeItem(T V)
{
	if (Head == NULL)		//case if list empty
		return false;
	if (ref->getValue() == V)		//if ref value equals to remove value
	{
		if (ref == Head)				//if ref equals to Head
		{
			if (Head == Tail)				//case there is one element in the list
			{
				delete Head;
				Head = NULL;
				Tail = NULL;
				ref = NULL;
				Count--;
				return true;
			}
			else
			{			//case more than one element but ref equals to Head
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
	{		//case if ref value not equals to remove value
		if (Head->getValue() == V) //case if the head has the value of remove value
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
			PNode<T>* p = Head->getNext();
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
void PList<T>::clear()
{
	PNode<T>* p = Head;
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
void PList<T>::print()
{
	PNode<T>* temp = Head;
	while (temp != NULL)
	{
		cout << temp->getValue() << endl;
		temp = temp->getNext();
	}
}

template<class T>
void PList<T>::AddToArr(T arr[], int& actSize, int maxSize)
{
	PNode<T>*p = Head;
	while (p != NULL && actSize != maxSize)		//stop in two case if the list finished or the array is filled
	{
		arr[actSize++] = p->getValue();
		p = p->getNext();
	}
}

template<class T>
void PList<T>::startLoop()
{
	ref = Head;
	canMove = true;
}

template<class T>
PNode<T>* PList<T>::sort(PNode<T>* a, PNode<T>* b)
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
void PList<T>::split(PNode<T>* src, PNode<T>* &first, PNode<T>* &second)
{
	PNode<T>* fast;
	PNode<T>* slow;
	if (src == NULL || src->getNext() == NULL)		//if the src of the list or its next equals to null will return
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
void PList<T>::mergeSort(PNode<T>* &ptr)
{
	PNode<T>* head = ptr;
	PNode<T>* a;
	PNode<T>* b;

	if (head == NULL || head->getNext() == NULL)		//the base case
		return;

	split(head, a, b);		//split the list into two lists

	mergeSort(a);			//sort every list
	mergeSort(b);

	ptr = sort(a, b);		//sort the tow list and merge them into one sorted list
}

template<class T>
void PList<T>::Sort()
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
		PNode<T>* P = Head;
		while (P&&P->getNext())
		{
			P->getNext()->changePrv(P);
			P = P->getNext();
		}
	}
}

template<class T>
T PList<T>::getref()
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
void PList<T>::plus()
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
	else
	{
		ref = nullptr;
	}
}

template<class T>
void PList<T>::addList(PList<T> & add)
{
	PNode<T> * p;
	p = add.Head;
	PList<T> ad;
	while (p)
	{
		ad.addItem(p->getValue(), p->getPriorty());
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
PList<T>::~PList()
{
}