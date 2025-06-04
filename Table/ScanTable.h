#pragma once

#include "Record.h"
#include "Table.h"
#include "ArrayTable.h"

template<typename TKey, typename TVal>
class ScanTable : public ArrayTable <TKey, TVal> // �������� �� ������� ������� �������� � �� 
{
public:
	// �����������
	ScanTable(int _size) : ArrayTable <TKey, TVal>(_size) {};

	// ������ ��� ������ � ���������
	bool Find(TKey key) override;
	bool Insert(Record<TKey, TVal> rec) override;
	void Delete(TKey key) override;
};

// ���������� ������� ������ ������ � ������� �� �����
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

// ���������� ������� ���������� ������ � �������
template<typename TKey, typename TVal>
bool ScanTable<TKey, TVal>::Insert(Record<TKey, TVal> record)
{
	if (IsFull()) // ��������� �������� �� ������� �������
		return false;
	if (Find(record.key))
		return false;
	// curr_element ���������� � DataCount ����� Find
	pRec[curr_element] = record;
	//pRec[curr_element].status = Used;
	DataCount++;
	Eff++;
	return true;
}

// ���������� ������� �������� ������ �� ������� �� �����
template<typename TKey, typename TVal>
void ScanTable<TKey, TVal>::Delete(TKey key)
{
	if (!Find(key))
		throw - 1;
	DataCount--;
	pRec[curr_element] = pRec[DataCount];
	Eff++;
}
