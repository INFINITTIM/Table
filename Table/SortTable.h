#pragma once

#include "Record.h"
#include "Table.h"
#include "ArrayTable.h"
#include "ScanTable.h"

enum SortType
{
	SelectS, MergeS, QuickS
};

template <typename TKey, typename TVal>
class SortTable : public ScanTable<TKey, TVal> // отвечает за функции вставка удаление и тд (но уже сортированная)
{
protected:
	Record<TKey, TVal>* pTmp;
public:
	// конструктор
	SortTable(int _size) : ScanTable <TKey, TVal>(_size) {};

	// конструктор приведения типа 
	// (из неотсортированной таблицы в отсортированную путем сортировки одним из возможных вариантов)
	SortTable(ScanTable<TKey, TVal> &scan_table, SortType s) : ScanTable <TKey, TVal>(scan_table) {
		if (s == SelectS)
			SelectSort();
		else if (s == MergeS)
		{
			MergeSort(0, DataCount - 1);
		}
		else if (s == QuickS)
		{
			QuickSort();
		}
	};
	bool Find(TKey key) override;
	bool Insert(Record<TKey, TVal> rec) override;
	bool Delete(TKey key) override;

	// сортировка выбором
	void SelectSort();
	// быстрая сортировка
	void QuickSort();
	// рекурсивная функция для быстрой сортировки
	void QuickSortRec(int start, int finish);
	// сортировка слиянием
	void Merge(int left, int middle, int right);
	// рекурсивная функция для сортировки слиянием
	void MergeSort(int left, int right);
};

template <typename TKey, typename TVal>
bool SortTable<TKey, TVal>::Find(TKey key)
{
	int start = 0;
	int end = DataCount - 1; // последняя ячейка
	while (start <= end)
	{
		Eff++;
		int ind = (start + end) / 2;
		if (pRec[ind].key > key)
			end = ind - 1;
		else if (pRec[ind].key < key)
			start = ind + 1;
		else
		{
			curr_element = ind;
			return true;
		}
	}
	curr_element = start;
	return false;
}

template <typename TKey, typename TVal>
bool SortTable<TKey, TVal>::Insert(Record<TKey, TVal> rec) {
	if (DataCount >= size)
		return false;

	if (Find(rec.key)) {
		return false;
	}

	for (int i = DataCount; i > curr_element; i--) {
		pRec[i] = pRec[i - 1];
		Eff++;
	}
	pRec[curr_element] = rec;
	DataCount++;
	return true;
}

template <typename TKey, typename TVal>
bool SortTable<TKey, TVal>::Delete(TKey key) {
	if (!Find(key)) {
		return false;
	}
	else {
		for (int i = curr_element; i < DataCount - 1; i++) {
			pRec[i] = pRec[i + 1];
			Eff++;
		}
		DataCount--;
		return true;
	}
}


/*template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::SelectSort() // сортировка выбором 
{
	int i = 0, j = 0;
	while (i < DataCount)
	{
		int k;
		j = i;
		int min_i = pRec[i].key;
		while (j < DataCount)
		{
			Eff++;
			if (min_i < pRec[j].key)
			{
				min_i = pRec[j].key;
				k = j;
			}
			j++;
		}
		Record<TKey, TVal> rec = pRec[k];
		pRec[k] = pRec[i];
		pRec[i] = rec;
	}
	i++;
}*/

template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::SelectSort()
{
	for (int i = 0; i < DataCount - 1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < DataCount; j++)
		{
			Eff++;
			if (pRec[j].key < pRec[min_idx].key)
			{
				min_idx = j;
			}
		}
		if (min_idx != i)
		{
			std::swap(pRec[i], pRec[min_idx]);
		}
	}
}

template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::QuickSort() // быстрая сортировка
{
	// принцип работы: 
	// k - опорный элемент 
	// s - начало
	// f - конец
	// left                            right
	// ---->                           <----
	//   s                               f
	// [... ... ... ... ... ... ... ... ...]
	//               ^
	//               |
	//               k
	//      <                 < 
	//   s       f       s               f 
	// [... ... ...]   [... ... ... ... ...]

	QuickSortRec(0, DataCount - 1); //рекурсивная сортировка
}

/*template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::QuickSortRec(int start, int finish) // рекурсивная быстрая сортировка 
{
	int left = start;
	int right = finish;
	Record<TKey, TVal> k = pRec[(start + finish) / 2];
	while (left < right)
	{
		while (pRec[left] < k)
			left++;
		while (pRec[right] > k)
			right--;
		if (left <= right)
		{
			swap(pRec[left], pRec[right]);
			left++;
			right--;
		}
	}
	if (start < left)
		QuickSortRec(start, left);
	if (right < finish)
		QuickSortRec(right, finish);
}*/

template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::QuickSortRec(int start, int finish)
{
	if (start >= finish) return;

	int left = start;
	int right = finish;
	Record<TKey, TVal> pivot = pRec[(start + finish) / 2];

	while (left <= right)
	{
		while (pRec[left].key < pivot.key)
		{
			left++;
			Eff++;
		}
		while (pRec[right].key > pivot.key)
		{
			right--;
			Eff++;
		}
		if (left <= right)
		{
			std::swap(pRec[left], pRec[right]);
			left++;
			right--;
		}
	}
	if (start < right)
		QuickSortRec(start, right);
	if (left < finish)
		QuickSortRec(left, finish);
}

//в классе сорт тейбл помимо массива прекорд нужно объявить еще и временный массив для складирования записей при сортировке

/*template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::Merge(int left, int middle, int right)
{
	int i = left;
	int k = left;
	int j = middle + 1;
	while (i <= middle && j <= right)
	{
		if (pRec[i].key <= pRec[j].key)
			pTmp[k] = pRec[i]; i++;
		else
			pTmp[k] = pRec[j]; j++; k++;
	}
	if (i <= middle)
		while (i <= middle)
		{
			pTmp[k] = pRec[i];
			i++;
			j++;
		}
	else
		while (j <= right)
		{
			pTmp[k] = pRec[j];
			j++;
			k++;
		}
	for (int i = left; i <= right; i++)
	{
		pRec[i] = pTmp[i];
	}
}

template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::MergeSort(int left, int right)
{
	if (left == right)
		return;
	int middle = (left + right) / 2;
	MergeSort(left, middle);
	MergeSort(middle + 1; right);
	Merge(left, middle, right);
}*/

template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::Merge(int left, int middle, int right)
{
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::vector<Record<TKey, TVal>> leftPart(n1);
	std::vector<Record<TKey, TVal>> rightPart(n2);

	for (int i = 0; i < n1; i++)
		leftPart[i] = pRec[left + i];
	for (int j = 0; j < n2; j++)
		rightPart[j] = pRec[middle + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2)
	{
		Eff++;
		if (leftPart[i].key <= rightPart[j].key)
		{
			pRec[k] = leftPart[i];
			i++;
		}
		else
		{
			pRec[k] = rightPart[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		pRec[k] = leftPart[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		pRec[k] = rightPart[j];
		j++;
		k++;
	}
}

template <typename TKey, typename TVal>
void SortTable<TKey, TVal>::MergeSort(int left, int right)
{
	if (left >= right) return;
	int middle = (left + right) / 2;
	MergeSort(left, middle);
	MergeSort(middle + 1, right);
	Merge(left, middle, right);
}

// отличие от быстрой в том что она расходует доп память а то есть в два раза больше но трудоемкость всегда одинаковая NlogN;

// задание сделать неупорядоченную таблицу и отсортировать ее с помощью этих сортировок

// создание упорядоченной таблицы двумя способами 
// создание таблицы через инсёрты или берем неупорядоченную таблицу берем все элементы и сортируем

