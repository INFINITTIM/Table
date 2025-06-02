#pragma once

#include <iostream>

template<class T>
struct TNode {
	T val;
	TNode<T>* pNext;
};

template<class T>
class LLStack {
	TNode<T>* pFirst; // указатель на верхний элемент стека. Он хранит адрес первого узла (верхнего элемента)
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
	TNode<T>* stmp = s.pFirst; // создаем временный указатель stmp, который указывает на первый элемент стека s
	if (stmp != nullptr) { // если стек не пустой (stmp != nullptr), мы создаем новый узел для первого элемента
		pFirst = new TNode<T>; // выделяем память для нового узла
		pFirst->val = stmp->val; // копируем значение из stmp->val
		pFirst->pNext = nullptr; // и устанавливаем pNext этого узла в nullptr, так как это будет последний элемент на данный момент

		stmp = stmp->pNext; // переходим к следующему узлу в исходном стеке

		TNode<T>* prev = pFirst; // создаем указатель prev, который будет использоваться для связывания новых узлов
		while (stmp != nullptr) { //  цикл while продолжается до тех пор, пока есть элементы для копирования
			Node<T>* newnode = new TNode<T>; // Внутри цикла создаем новый узел newnode
			newnode->val = stmp->val; // копируем значение из текущего узла stmp
			newnode->pNext = nullptr; // и устанавливаем его pNext в nullptr

			prev->pNext = newnode; // связываем предыдущий узел с новым узлом

			stmp = stmp->pNext; // переходим к следующему узлу в исходном стеке
			prev = prev->pNext; // и обновляем указатель prev на новый узел
		}
	}
	else {
		pFirst = nullptr; // если исходный стек пуст, устанавливаем pFirst в nullptr
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
	while (pFirst != nullptr) { //удаляем все звенья
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	TNode<T>* stmp = s.pFirst; //переносим значения из правого стека
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
		return false; // если выделение и освобождение прошло успешно то стек не заполнен 
	}
	catch (std::bad_alloc e) { // если же не успешно и система не может выделить память то выбрасывается вот эта ошибка 
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

