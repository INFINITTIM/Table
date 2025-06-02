#pragma once

#include "Node.h"
#include "iterator.h"

template <class T>
class List
{
protected:
	Node<T>* pFirst;
	Node<T>* pLast;
	Node<T>* pCurr;
	Node<T>* pPrev;
	int size;
public:

	typedef ListIterator<T> iterator;

	iterator begin() { return iterator(pFirst); }
	iterator end() { return iterator(nullptr); }

	List();
	List(const List<T>& p);
	~List();

	List<T>& operator=(const List<T>& p);
	bool operator==(const List<T>& p) const;
	bool operator!=(const List<T>& p) const;

	void InsFirst(T element);
	void InsLast(T element);
	void InsCurr(T element);

	void DelFirst();
	void DelLast();
	void DelCurr();

	void Reset();
	bool IsEnd() const;
	void GoNext();

	T getCurr();

	void Clear();
	bool IsEmpty();
	int Size();
};

template <class T>
List<T>::List() : pFirst(nullptr), pLast(nullptr), pCurr(nullptr), pPrev(nullptr), size(0)
{
}

template <class T>
List<T>::List(const List<T>& p)
{
	Node<T>* stmp = p.pFirst;
	if (stmp != nullptr)
	{
		pFirst = new Node<T>;
		pFirst->val = stmp->val;
		pFirst->pNext = nullptr;

		stmp = stmp->pNext;

		Node<T>* gtmp = pFirst;

		while (stmp != nullptr)
		{
			Node<T>* newNode = new Node<T>;
			newNode->val = stmp->val;
			newNode->pNext = nullptr;

			gtmp->pNext = newNode;

			stmp = stmp->pNext;
			gtmp = gtmp->pNext;
		}
		pLast = gtmp;
		Reset();
		size = p.size;
	}
	else
	{
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		pPrev = nullptr;
		size = 0;
	}
}

template <class T>
List<T>::~List()
{
	while (pFirst != nullptr) {
		Node<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
}

template <class T>
List<T>& List<T>::operator=(const List<T>& p)
{
	if (this == &p)
		return *this;
	if (size == p.size)
	{
		Node<T>* tmp = p.pFirst;
		Node<T>* stmp = pFirst;
		for (int i = 0; i < size; i++)
		{
			stmp->val = tmp->val;
			tmp = tmp->pNext;
			stmp = stmp->pNext;
		}
		Reset();
	}
	else
	{
		Clear();
		Node<T>* stmp = p.pFirst;
		if (stmp != nullptr)
		{
			pFirst = new Node<T>;
			pFirst->val = stmp->val;
			pFirst->pNext = nullptr;

			stmp = stmp->pNext;

			Node<T>* gtmp = pFirst;

			while (stmp != nullptr)
			{
				Node<T>* newNode = new Node<T>;
				newNode->val = stmp->val;
				newNode->pNext = nullptr;

				gtmp->pNext = newNode;

				stmp = stmp->pNext;
				gtmp = gtmp->pNext;
			}
			pLast = gtmp;
			Reset();
			size = p.size;
		}
		else
		{
			pFirst = nullptr;
			pLast = nullptr;
			pCurr = nullptr;
			pPrev = nullptr;
			size = 0;
		}
	}
	return *this;
}

template <class T>
bool List<T>::operator==(const List<T>& p) const
{
	if (size != p.size)
		return false;
	Node<T>* node = pFirst;
	Node<T>* pnode = p.pFirst;
	while (node != nullptr)
	{
		if (node->val != pnode->val)
			return false;
		node = node->pNext;
		pnode = pnode->pNext;
	}
	return true;
}

template <class T>
bool List<T>::operator!=(const List<T>& p) const
{
	return (!(*this == p));
}

template <class T>
void List<T>::InsFirst(T element)
{
	Node<T>* newNode = new Node<T>;
	newNode->val = element;
	newNode->pNext = pFirst;
	if (pFirst == nullptr)
	{
		pLast = newNode;
		pFirst = newNode;
		Reset();
	}
	else
		if (pCurr == pFirst)
			pPrev = newNode;
	pFirst = newNode;
	size++;
}

template <class T>
void List<T>::InsLast(T element)
{
	Node<T>* newNode = new Node<T>;
	newNode->val = element;
	newNode->pNext = nullptr;
	if (pFirst == nullptr)
	{
		pFirst = newNode;
		pLast = newNode;
		Reset();
	}
	else
	{
		if (pPrev == pLast)
			pCurr = newNode;
		pLast->pNext = newNode;
		pLast = newNode;
	}
	size++;
}

template <class T>
void List<T>::InsCurr(T element)
{
	if (pCurr == pFirst)
		InsFirst(element);
	else if (pPrev == pLast)
		InsLast(element);
	else
	{
		Node<T>* tmp = new Node<T>;
		tmp->val = element;
		tmp->pNext = pCurr;
		pPrev->pNext = tmp;
		pPrev = pPrev->pNext;
		size++;
	}
}

template <class T>
void List<T>::DelFirst()
{
	if (pFirst == nullptr)
		return;
	Node<T>* tmp = pFirst;
	if (pCurr == pFirst)
		pCurr = pFirst->pNext;
	pFirst = pFirst->pNext;
	delete tmp;
	if (pFirst == nullptr)
		pLast = nullptr;
	size--;
}

template <class T>
void List<T>::DelLast()
{
	if (pFirst == nullptr)
		return;
	Node<T>* tmp = pFirst;
	while (tmp->pNext != pLast)
	{
		tmp = tmp->pNext;
	}
	Node<T>* last_node = tmp->pNext;
	if (pCurr == tmp->pNext)
		pCurr = nullptr;
	delete last_node;
	tmp->pNext = nullptr;
	pLast = tmp;
	size--;
}

template <class T>
void List<T>::DelCurr()
{
	if (pCurr == nullptr) {
		return;
	}
	else if (pCurr == pFirst)
	{
		DelFirst();
	}
	else if (pCurr == pLast)
	{
		DelLast();
	}
	else
	{
		Node<T>* tmp = pCurr;
		pCurr = pCurr->pNext;
		Node<T>* prevNode = pFirst;
		while (prevNode != nullptr && prevNode->pNext != tmp) {
			prevNode = prevNode->pNext;
		}
		pPrev = prevNode;
		if (prevNode != nullptr) {
			prevNode->pNext = pCurr;
		}
		delete tmp;
		size--;
	}
}

template <class T>
void List<T>::Reset()
{
	pPrev = nullptr;
	pCurr = pFirst;
}

template <class T>
T List<T>::getCurr()
{
	Node<T>* current_node = pCurr;
	return current_node->val;

}

template <class T>
bool List<T>::IsEnd() const
{
	if (pCurr == nullptr)
		return true;
	else
		return false;
}

template <class T>
void List<T>::GoNext()
{
	if (!IsEnd())
	{
		pPrev = pCurr;
		pCurr = pCurr->pNext;
	}
}

template <class T>
void List<T>::Clear()
{
	while (pFirst != nullptr) {
		Node<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	size = 0;
}

template<class T>
bool List<T>::IsEmpty()
{
	if (pFirst == nullptr)
		return true;
	return false;
}

template<class T>
int List<T>::Size() {
	int count = 0;
	Node<T>* tmp = pFirst;
	while (tmp != nullptr) {
		tmp = tmp->pNext;
		count++;
	}
	return count;
}