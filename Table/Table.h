#pragma once

#include <iostream>
#include "Record.h"

template<typename TKey, typename TVal>
class Table {
protected:
	int DataCount; // ���-�� ������ (�������)
	int Eff; // ������������� � ����� ����������� ��������
public:
	Table() : DataCount(0), Eff(0) {}; //f(1) {};
	virtual ~Table() {};

	// ������� ��� ����� ������ 
	int getDataCount() const { return DataCount; }
	int getEff() const { return Eff; }

	// ����� ��� ������� �������������
	void ClearEff() { Eff = 0; }

	// �������� ������� �� ������� 
	bool IsEmpty() const { return DataCount == 0; }

	// �������� ������� �� ������������� 
	virtual bool IsFull() const = 0; // ������ ������ ����� �� ����� ����� ���������� � ����� ���������� �����������

	// ������ ��� ������ � ���������
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(Record<TKey, TVal> rec) = 0;
	virtual bool Delete(TKey key) = 0;

	// ������ ��� ������������
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	// ������� ��� ������� � ����� �������
	virtual Record<TKey, TVal> getCurr() const = 0;
	virtual TKey getCurrKey() const = 0;
	virtual TVal getCurrVal() const = 0;

	// �������� ������
	friend std::ostream& operator<<(std::ostream& os, Table& t)
	{
		for (t.Reset(); !t.IsEnd(); t.GoNext())
		{
			os << t.getCurr() << std::endl;
		}
		return os;
	}
};
