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
		pList[curr_list].push_front(rec); // ������� � ������
		DataCount++;
		Eff++;
		return true;
	}

	void Delete(TKey _key) override {
		if (Find(_key))
		{
			pList[curr_list].erase(currI); // �������� ��������
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


	//isFull ������� ����� ��������� ������� �������� �� ������� - ����������� �������� �������, ���� ��� ���, �� false
	bool IsFull() const override {
		return false;
	}

	//����� ������������ ����� ������ ������� (����� ���� ������������� �� ����� � ������� ����������� ��� ��������
	// � ����� ���������� ������ ���������������
	// � ����� ������ ������ ������������ ������ �������� (n) - ���� ��� ������� ������
	// ���� � ������ ������ ������ �������� ���������������
	// insert() � ������ ������ - ������� ������ find, ����� ���������, ��� �������� ���
	// ������� ����� find() ���������� ����� ������ � ����� ������ ������� � ������ � ���� ������ (insert())
	// �������� �� ����� - > find () ������� ������� � ���� ��� ���, �� �����, � ���� ����,
	// �� �� ������ ����������� ������� ���� �������
	//find ��������� ���� � ������� ���� �� �� �����
	//����� ������������ ����������� ���� (������) �� ���������� (���� �������� ��� ����� List �� ������� ��������� ��������)
	//��������� � ��������� ��������� � ���� ��������� 
	//������� ������� - ����� ������ �� ����������� ������ (����� ����� �������� ������ 
	// � � ���� ������ ����� ����� �������� �� ������� - ��������� �� ����)
};



