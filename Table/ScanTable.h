#pragma once

#include "Record.h"
#include "Table.h"
#include "ArrayTable.h"

template<typename TKey, typename TVal>
class ScanTable : public ArrayTable <TKey, TVal> // отвечает за функции вставка удаление и тд 
{
public:
	// конструктор
	ScanTable(int _size) : ArrayTable <TKey, TVal>(_size) {};

	// методы для работы с таблицами
	bool Find(TKey key) override;
	bool Insert(Record<TKey, TVal> rec) override;
	bool Delete(TKey key) override ;

	// оператор вывода
	friend std::ostream& operator<<(std::ostream& out, ScanTable& m)
	{
		m.Reset();
		for (int i = 0; i < size; i++)
		{
			if (m.getCurrKey() == i)
			{
				os << m.getCurr() << std::endl;
				m.GoNext();
			}
			else
				os << "Key: ---- , Value : ---- " << std::endl;
		}
		return os;
	}
};

// реализация функции поиска данных в таблице по ключу
template<typename TKey, typename TVal>
bool ScanTable<TKey, TVal>::Find(TKey key)
{
	for (int i = 0; i < DataCount; i++)
	{
		Eff++;
		if (key == pRec[i].key) {
			curr_element = i;
			return true;
		}
	}
	curr_element = DataCount;
	return false;
}

// реализация функции добавления данных в таблицу
template<typename TKey, typename TVal>
bool ScanTable<TKey, TVal>::Insert(Record<TKey, TVal> record)
{
	if (IsFull()) // Добавляем проверку на полноту таблицы
		return false;
	if (Find(record.key))
		return false;
	// curr_element установлен в DataCount после Find
	pRec[curr_element] = record;
	//pRec[curr_element].status = Used;
	DataCount++;
	Eff++;
	return true;
}

// реализация функции удаления данных из таблицы по ключу
template<typename TKey, typename TVal>
bool ScanTable<TKey, TVal>::Delete(TKey key)
{
	if (!Find(key))
		throw - 1;
	DataCount--;
	pRec[curr_element] = pRec[DataCount];
	Eff++;
	return true;
}
