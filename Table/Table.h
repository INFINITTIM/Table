#pragma once

#include <iostream>
#include "Record.h"

template<typename TKey, typename TVal>
class Table {
protected:
	int DataCount; // кол-во данных (записей)
	int Eff; // эффективность в числе выполненных операций
public:
	Table() : DataCount(0), Eff(0) {}; //f(1) {};
	virtual ~Table() {};

	// геттеры для полей класса 
	int getDataCount() const { return DataCount; }
	int getEff() const { return Eff; }

	// метод для очистки эффективности
	void ClearEff() { Eff = 0; }

	// проверка таблицы на пустоту 
	bool IsEmpty() const { return DataCount == 0; }

	// проверка таблицы на заполненность 
	virtual bool IsFull() const = 0; // значит данный метод не имеет здесь реализации а класс становится абстрактным

	// методы для работы с таблицами
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(Record<TKey, TVal> rec) = 0;
	virtual bool Delete(TKey key) = 0;

	// методы для итерирования
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	// геттеры для записей и полей записей
	virtual Record<TKey, TVal> getCurr() const = 0;
	virtual TKey getCurrKey() const = 0;
	virtual TVal getCurrVal() const = 0;

	// оператор вывода
	friend std::ostream& operator<<(std::ostream& os, Table& t)
	{
		for (t.Reset(); !t.IsEnd(); t.GoNext())
		{
			os << t.getCurr() << std::endl;
		}
		return os;
	}
};
