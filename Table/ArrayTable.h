#pragma once

#include "Record.h"
#include "Table.h"

template<typename TKey, typename TVal>
class ArrayTable : public Table<TKey, TVal> // таблица в которой данные хранятся в массиве (отвечает за хранение)
{
protected:
	Record<TKey, TVal>* pRec; // массив для хранения записей таблицы
	size_t size; // размер таблицы 
	int curr_element; //текущий элемент
public:
	// конструкторы и деструктор
	ArrayTable(int _size = 100);
	ArrayTable(const ArrayTable<TKey, TVal>& at);
	~ArrayTable();

	// проверка на полноту таблицы
	bool IsFull() const override { return (DataCount >= size); }

	// методы для итерирования
	void Reset() override { curr_element = 0; }
	void GoNext() override { curr_element++; }
	bool IsEnd() override { return (DataCount == curr_element); }

	// геттеры для записей и полей записей
	Record<TKey, TVal> getCurr() const override { return pRec[curr_element]; }
	TKey getCurrKey() const override { return pRec[curr_element].key; }
	TVal getCurrVal() const override { return pRec[curr_element].val; }
};

// реализация конструкторов и деструктора
template<typename TKey, typename TVal>
ArrayTable<TKey, TVal>::ArrayTable(int _size = 10) : Table<TKey, TVal>()
{
	size = _size;
	curr_element = -1;
	pRec = new Record<TKey, TVal>[size];
}

template<typename TKey, typename TVal>
ArrayTable<TKey, TVal>::ArrayTable(const ArrayTable<TKey, TVal>& at) : Table<TKey, TVal>()
{
	size = at.size;
	curr_element = at.curr_element;
	pRec = new Record<TKey, TVal>[size];
	for (int i = 0; i < size; i++)
	{
		pRec[i] = at.pRec[i];
	}
	DataCount = at.DataCount;
	Eff = at.Eff;
}

template<typename TKey, typename TVal>
ArrayTable<TKey, TVal>::~ArrayTable()
{
	delete[] pRec;
}
