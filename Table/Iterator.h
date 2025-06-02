#pragma once

#include <iterator>

template <class T>
class List;

template <class T>
class ListIterator : public std::iterator<std::input_iterator_tag, T>
{
	friend class List<T>;
private:
	ListIterator(Node<T>* pCurr);
public:
	ListIterator() : pCurr(nullptr) {}
	ListIterator(const ListIterator<T>& it);

	bool operator!=(ListIterator<T> const& other) const;
	bool operator==(ListIterator<T> const& other) const;
	typename ListIterator<T>::reference operator*() const;
	//typename ListIterator<T>::pointer operator->() const;
	ListIterator<T>& operator++();
private:
	Node<T>* pCurr;
};

template <class T>
ListIterator<T>::ListIterator(Node<T>* pCurr)
{
	this->pCurr = pCurr;
}


template <class T>
ListIterator<T>::ListIterator(const ListIterator<T>& it)
{
	pCurr = it.pCurr;
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const& other) const
{
	return pCurr != other.pCurr;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const& other) const
{
	return pCurr == other.pCurr;
}

template<class T>
typename ListIterator<T>::reference ListIterator<T>::operator*() const
{
	return pCurr->val;
}

//template <class T>
//typename ListIterator<T>::pointer ListIterator<T>::operator->() const
//{
//
//}

template <class T>
ListIterator<T>& ListIterator<T>::operator++()
{
	pCurr = pCurr->pNext;
	return *this;

}