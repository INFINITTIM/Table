#pragma once

#include "Record.h"
#include "Table.h"
#include "HashTable.h"
#include "List.h"
#include "iterator.h"

template <typename TKey, typename TVal>
class HashTableUsedList : public HashTable<TKey, TVal>
{
protected:
	List<Record<TKey, TVal>>* pList;
	int curr_list;
	typename List<Record<TKey, TVal>>::iterator curr_iterator;
public:
	HashTableUsedList(int _size = 100) : HashTable<TKey, TVal>(_size)
	{
		pList = new List<Record<TKey, TVal>>[_size];
		curr_list = -1;
	}

	~HashTableUsedList()
	{
		delete[] pList;
	}

	bool Find(TKey _key) override {
		curr_list = HashFunction(_key);
		Eff++; // Учет обращения к цепочке
		if (pList[curr_list].IsEmpty()) {
			return false;
		}
		for (curr_iterator = pList[curr_list].begin(); curr_iterator != pList[curr_list].end(); ++curr_iterator) {
			Eff++; // Учет проверки элемента
			if ((*curr_iterator).key == _key) return true;
		}
		return false;
	}

	bool Insert(Record<TKey, TVal> rec) override {
		if (Find(rec.key)) {
			return false;
		}
		pList[curr_list].InsFirst(rec); // вставка в начало
		DataCount++;
		Eff++;
		return true;
	}

	bool Delete(TKey _key) override {
		if (!Find(_key)) 
			return false;
		pList[curr_list].DelCurr(); // удаление текущего
		DataCount--;
		Eff++;
		return true;
	}

	void Reset() override {
		curr_list = 0;
		while (curr_list < size && pList[curr_list].IsEmpty()) {
			curr_list++;
		}
		if (curr_list < size) {
			curr_iterator = pList[curr_list].begin();
		}
	}

	void GoNext() override {
		++curr_iterator;
		while (curr_list < size && curr_iterator == pList[curr_list].end()) {
			curr_list++;
			if (curr_list < size) {
				curr_iterator = pList[curr_list].begin();
			}
		}
	}

	bool IsEnd() override {
		return curr_list >= size;
	}

	TKey getCurrKey() const override {
		return (*curr_iterator).key;
	}

	TVal getCurrVal() const override {
		return (*curr_iterator).val;
	}

	Record<TKey, TVal> getCurr() const override {
		return *curr_iterator;
	}


	//isFull функция будет повторять функцию проверки на полноту - попробовать выделить элемент, если его нет, то false
	bool IsFull() const override {
		try {
			pList[0].InsFirst(Record<TKey, TVal>());
			pList[0].DelFirst();
			return false;
		}
		catch (...) {
			return true;
		}
	}

	//класс представляет собой массив списков (может быть упорядоченным по ключу в порядке возрастания или убывания
	// в нашей реализации список неупорядоченный
	// в самом плохом случае трудоемкость поиска линейная (n) - если хэш функция плохая
	// если в рамках одного списка элементы неупорядоченные
	// insert() в начало списка - сначала делаем find, чтобы убедиться, что элемента нет
	// сначала через find() определяем номер списка и затем делаем вставку в начало в этот список (insert())
	// удаление по ключу - > find () находим элемент и если его нет, то ладно, и если есть,
	// то из списка конкретного убираем этот элемент
	//find принимает ключ и смотрим есть ли он здесь
	//можно использовать стандартный лист (список) из библиотеки (либо добавить наш класс List из прошлой программы полинома)
	//сложность с перебором элементов в этой структуре 
	//текущий элемент - номер ячейки из конкретного списка (будет номер текущего списка 
	// и в этом списке будет номер элемента на текущий - указатель на него)
};



