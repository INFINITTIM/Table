#pragma once

#include "Record.h"
#include "Table.h"
#include "HashTable.h"
#include "HashTableUsedArray.h"


template <typename TKey, typename TVal>
class HashTableUsedArray : public HashTable<TKey, TVal>
{
protected:
	Record<TKey, TVal>* pRec; // указатель на первый элемент массива
	Record<TKey, TVal> free, deleted; // свободна€ и удаленна€ €чейка
	int step; // шаг вторичного хэшировани€
	int current_element; // указывает на текущий элемент
public:
	HashTableUsedArray(int _size, int _step);

	HashTableUsedArray(const HashTableUsedArray<TKey, TVal>& ht);

	void Reset() override
	{
		current_element = 0;
		while ((pRec[current_element] == free || pRec[current_element] == deleted) && current_element < size)
		{
			current_element++;
		}
	}

	bool IsEnd() override { return current_element == size; }

	Record<TKey, TVal> getCurr() const override { return pRec[current_element]; }
	TKey getCurrKey() const override { return pRec[current_element].key; }
	TVal getCurrVal() const override { return pRec[current_element].val; }

	bool IsFull() const override { return DataCount == size; }

	void GoNext() override 
	{
		current_element++;
		while ((pRec[current_element] == free || pRec[current_element] == deleted) && current_element < size)
			current_element++;
	}

	bool Empty() { return DataCount == 0; }

	bool Find(TKey key) override
	{
		current_element = HashFunction(key);
		int tmp = -1;

		for (int i = 0; i < size; i++)
		{
			Eff++;
			if (pRec[current_element] == free)
				break;
			else
			{
				if (pRec[current_element] == deleted && tmp == -1)
					tmp = current_element;
				else
				{
					if (pRec[current_element].key == key)
						return true;
				}
			}
			current_element = (current_element + step) % size;
		}
		if (tmp != -1)
			current_element = tmp;
		return false;
	}

	bool Insert(Record<TKey, TVal> record) override
	{
		if (IsFull())
			return false;
		if (Find(record.key))
			return false;
		pRec[current_element] = record;
		DataCount++;
		Eff++;
		return true;
	}
	
	void Delete(TKey key) override
	{
		if (!Find(key))
			throw - 1;
		pRec[current_element] = deleted;
		DataCount--;
		Eff++;
	}
};


template <typename TKey, typename TVal>
HashTableUsedArray<TKey, TVal>::HashTableUsedArray(int _size, int _step)
{
	free.key = -1;
	deleted.key = -2;
	free.val = 0;
	deleted.val = 0;
	current_element = -1;
	size = _size;
	step = _step;
	pRec = new Record<TKey, TVal>[size];
	for (int i = 0; i < size; i++)
	{
		pRec[i] = free;
	}
}

template <typename TKey, typename TVal>
HashTableUsedArray<TKey, TVal>::HashTableUsedArray(const HashTableUsedArray<TKey, TVal>& ht)
{
	size = ht.size;
	current_element = ht.current_element;
	pRec = new Record<TKey, TVal>[size];
	for (int i = 0; i < size; i++)
	{
		pRec[i] = ht.pRec[i];
	}
	DataCount = ht.DataCount;
	Eff = ht.Eff;
}
