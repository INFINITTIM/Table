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
		Eff++; // ���� ��������� � �������
		if (pList[curr_list].IsEmpty()) {
			return false;
		}
		for (curr_iterator = pList[curr_list].begin(); curr_iterator != pList[curr_list].end(); ++curr_iterator) {
			Eff++; // ���� �������� ��������
			if ((*curr_iterator).key == _key) return true;
		}
		return false;
	}

	bool Insert(Record<TKey, TVal> rec) override {
		if (Find(rec.key)) {
			return false;
		}
		pList[curr_list].InsFirst(rec); // ������� � ������
		DataCount++;
		Eff++;
		return true;
	}

	bool Delete(TKey _key) override {
		if (!Find(_key)) 
			return false;
		pList[curr_list].DelCurr(); // �������� ��������
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


	//isFull ������� ����� ��������� ������� �������� �� ������� - ����������� �������� �������, ���� ��� ���, �� false
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



