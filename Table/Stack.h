#pragma once

#include <iostream>

template<class T>
struct TNode {
	T val;
	TNode<T>* pNext;
};

template<class T>
class LLStack {
	TNode<T>* pFirst; // ��������� �� ������� ������� �����. �� ������ ����� ������� ���� (�������� ��������)
public:
	LLStack();
	LLStack(const LLStack<T>& s);
	~LLStack();

	LLStack<T>& operator=(const LLStack<T>& s);
	bool operator==(const LLStack<T>& s) const;
	bool operator!=(const LLStack<T>& s) const;

	bool isEmpty() const;
	bool isFull() const;

	void push(T val);
	T pop();
	void clr();
	T top();
};

template<class T>
LLStack<T>::LLStack() {
	pFirst = nullptr;
}

template<class T>
LLStack<T>::LLStack(const LLStack<T>& s) {
	TNode<T>* stmp = s.pFirst; // ������� ��������� ��������� stmp, ������� ��������� �� ������ ������� ����� s
	if (stmp != nullptr) { // ���� ���� �� ������ (stmp != nullptr), �� ������� ����� ���� ��� ������� ��������
		pFirst = new TNode<T>; // �������� ������ ��� ������ ����
		pFirst->val = stmp->val; // �������� �������� �� stmp->val
		pFirst->pNext = nullptr; // � ������������� pNext ����� ���� � nullptr, ��� ��� ��� ����� ��������� ������� �� ������ ������

		stmp = stmp->pNext; // ��������� � ���������� ���� � �������� �����

		TNode<T>* prev = pFirst; // ������� ��������� prev, ������� ����� �������������� ��� ���������� ����� �����
		while (stmp != nullptr) { //  ���� while ������������ �� ��� ���, ���� ���� �������� ��� �����������
			Node<T>* newnode = new TNode<T>; // ������ ����� ������� ����� ���� newnode
			newnode->val = stmp->val; // �������� �������� �� �������� ���� stmp
			newnode->pNext = nullptr; // � ������������� ��� pNext � nullptr

			prev->pNext = newnode; // ��������� ���������� ���� � ����� �����

			stmp = stmp->pNext; // ��������� � ���������� ���� � �������� �����
			prev = prev->pNext; // � ��������� ��������� prev �� ����� ����
		}
	}
	else {
		pFirst = nullptr; // ���� �������� ���� ����, ������������� pFirst � nullptr
	}
}

template<class T>
LLStack<T>::~LLStack() {
	while (pFirst != nullptr) {
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
}

template<class T>
bool LLStack<T>::operator==(const LLStack<T>& s) const {
	if (this == &s) return true;

	TNode<T>* tmp = pFirst;
	TNode<T>* stmp = s.pFirst;

	while (stmp != nullptr && tmp != nullptr) {
		if (tmp->val != stmp->val)
			return false;
		tmp = tmp->pNext;
		stmp = stmp->pNext;
	}

	return tmp == stmp;
}

template<class T>
bool LLStack<T>::operator!=(const LLStack<T>& s) const {
	return (!(*this == s));
}

template<class T>
LLStack<T>& LLStack<T>::operator=(const LLStack<T>& s) {
	if (this == &s) return *this;
	while (pFirst != nullptr) { //������� ��� ������
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	TNode<T>* stmp = s.pFirst; //��������� �������� �� ������� �����
	if (stmp != nullptr) {
		pFirst = new TNode<T>;
		pFirst->val = stmp->val;
		pFirst->pNext = nullptr;

		stmp = stmp->pNext;

		TNode<T>* prev = pFirst;
		while (stmp != nullptr) {
			TNode<T>* newnode = new TNode<T>;
			newnode->val = stmp->val;
			newnode->pNext = nullptr;

			prev->pNext = newnode;

			stmp = stmp->pNext;
			prev = prev->pNext;
		}
	}
	else {
		pFirst = nullptr;
	}
}

template<class T>
bool LLStack<T>::isEmpty() const {
	return pFirst == nullptr;
}

template<class T>
bool LLStack<T>::isFull() const {
	try {
		TNode<T>* tmp = new TNode<T>;
		delete tmp;
		return false; // ���� ��������� � ������������ ������ ������� �� ���� �� �������� 
	}
	catch (std::bad_alloc e) { // ���� �� �� ������� � ������� �� ����� �������� ������ �� ������������� ��� ��� ������ 
		return true;
	}
}

template<class T>
void LLStack<T>::push(T val) {
	TNode<T>* tmp = new TNode<T>;
	tmp->val = val;
	tmp->pNext = pFirst;
	pFirst = tmp;
}

template<class T>
T LLStack<T>::pop() {
	T res;
	if (pFirst != nullptr) {
		T res = pFirst->val;
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
		return res;
	}
	else {
		throw - 1;
	}
}

template<class T>
T LLStack<T>::top() {
	if (pFirst != nullptr)
		return pFirst->val;
	else
		throw - 1;
}

template<class T>
void LLStack<T>::clr() {
	while (pFirst != nullptr) {
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
}

