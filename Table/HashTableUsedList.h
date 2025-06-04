#pragma once

#include "Record.h"
#include "Table.h"
#include "HashTable.h"
#include<list>
#include<iterator>

template <typename TKey, typename TVal>
class HashTableUsedList : public HashTable<TKey, TVal>
{
protected:
	std::list<Record<TKey, TVal>>* pList;
	int curr_list;
	typename std::list<Record<TKey, TVal>>::iterator currI;
public:
	HashTableUsedList(int _size = 100) : HashTable<TKey, TVal>(_size)
	{
		pList = new std::list<Record<TKey, TVal>>[_size];
		curr_list = -1;
	}

	~HashTableUsedList()
	{
		delete[] pList;
	}

	bool Find(TKey _key) override {
		curr_list = HashFunction(_key);
		Eff++;
		bool res = false;
		for (currI = pList[curr_list].begin(); currI != pList[curr_list].end(); currI++) {
			Eff++;
			if (currI->key == _key)
			{
				res = true;
				break;
			}
		}
		return res;
	}

	bool Insert(Record<TKey, TVal> rec) override {
		if (IsFull())
			return false;
		if (Find(rec.key)) {
			return false;
		}
		pList[curr_list].push_front(rec); // вставка в начало
		DataCount++;
		Eff++;
		return true;
	}

	void Delete(TKey _key) override {
		if (Find(_key))
		{
			pList[curr_list].erase(currI); // удаление текущего
			DataCount--;
			Eff++;
		}
		else
			return;
	}

	void Reset() override {
		for (curr_list = 0; curr_list < size; curr_list++) {
			if (!pList[curr_list].empty()) {
				currI = pList[curr_list].begin();
				return;
			}
		}
		curr_list = size;
	}

	void GoNext() override {
		++currI;
		while (curr_list < size && currI == pList[curr_list].end()) {
			++curr_list;
			if (curr_list < size) {
				currI = pList[curr_list].begin();
			}
		}
	}

	bool IsEnd() override {
		return curr_list >= size;
	}

	TKey getCurrKey() const override {
		return (*currI).key;
	}

	TVal getCurrVal() const override {
		return (*currI).val;
	}

	Record<TKey, TVal> getCurr() const override {
		return *currI;
	}


	//isFull функци€ будет повтор€ть функцию проверки на полноту - попробовать выделить элемент, если его нет, то false
	bool IsFull() const override {
		return false;
	}

	//класс представл€ет собой массив списков (может быть упор€доченным по ключу в пор€дке возрастани€ или убывани€
	// в нашей реализации список неупор€доченный
	// в самом плохом случае трудоемкость поиска линейна€ (n) - если хэш функци€ плоха€
	// если в рамках одного списка элементы неупор€доченные
	// insert() в начало списка - сначала делаем find, чтобы убедитьс€, что элемента нет
	// сначала через find() определ€ем номер списка и затем делаем вставку в начало в этот список (insert())
	// удаление по ключу - > find () находим элемент и если его нет, то ладно, и если есть,
	// то из списка конкретного убираем этот элемент
	//find принимает ключ и смотрим есть ли он здесь
	//можно использовать стандартный лист (список) из библиотеки (либо добавить наш класс List из прошлой программы полинома)
	//сложность с перебором элементов в этой структуре 
	//текущий элемент - номер €чейки из конкретного списка (будет номер текущего списка 
	// и в этом списке будет номер элемента на текущий - указатель на него)
};



