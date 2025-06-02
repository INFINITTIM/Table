#pragma once

#include "Tree.h"

enum height
{
	HEIGHT_OK = 0,
	HEIGHT_INC = 1,
	HEIGHT_DEC = -1
};

enum Balance
{
	BalanceForDelete,
	BalanceForIns
};

template <typename TKey, typename TVal>
class TreeBalance : public TreeTable<TKey, TVal>
{
protected:
	//рекурсивная функция вставки - результат вставки изменение высоты дерева
	int InsBalTree(TTreeNode<TKey, TVal>*& pNode, Record <TKey, TVal> rec) //принимаем ссылку на указатель, так как сам указатель может измениться (вставка в поддереве, указатель на поддерево куда мы добавляем запись и сама запись для добавления)
	{
		Eff++;
		int res = HEIGHT_OK;
		//если у нашего узла значение ключа больше, чем у текущей записи, то есть текущую запись надо вставить в левую ветвь дерева
		if (pNode == nullptr) {
			pNode = new TTreeNode<TKey, TVal>{ rec, nullptr, nullptr, 0 };
			res = HEIGHT_INC;
			DataCount++;
		}
		//перебалансировка надо делать в той в ветви, когда ее глубина увеличилась
		else
		{
			if (pNode->rec.key > rec.key) {
				int tmp = InsBalTree(pNode->pLeft, rec);
				if (tmp == HEIGHT_INC) {
					//надо запустить балансировку слева
					res = BalTreeLeft(pNode, BalanceForIns);
				}
			}
			else {
				//запускаем балансировку справа
				int tmp = InsBalTree(pNode->pRight, rec);
				if (tmp == HEIGHT_INC) {
					res = BalTreeRight(pNode, BalanceForIns);
				}
			}
		}
		return res; //результатом будет изменением высоты дерева
	}
	//функция балансировки слева
	int BalTreeLeft(TTreeNode<TKey, TVal>*& pNode, Balance balans) {
		int res = HEIGHT_OK;

		if (balans == BalanceForIns) {

			if (pNode->balansir == 1) {
				pNode->balansir = 0;
				res = HEIGHT_OK;
			}
			else if (pNode->balansir == 0) {
				pNode->balansir = -1;
				res = HEIGHT_INC;
			}
			else {
				TTreeNode<TKey, TVal>* p1 = pNode->pLeft;
				if (p1->balansir == -1) {

					pNode->pLeft = p1->pRight;
					p1->pRight = pNode;
					pNode = p1;
					pNode->balansir = 0;
					pNode->pRight->balansir = 0;
					res = HEIGHT_OK;
				}
				else {
					TTreeNode<TKey, TVal>* p2 = p1->pRight;
					p1->pRight = p2->pLeft;
					p2->pLeft = p1;
					pNode->pLeft = p2->pRight;
					p2->pRight = pNode;

					if (p2->balansir == -1) {
						pNode->balansir = 1;
						p1->balansir = 0;
					}
					else if (p2->balansir == 1) {
						pNode->balansir = 0;
						p1->balansir = -1;
					}
					else {
						pNode->balansir = 0;
						p1->balansir = 0;
					}
					pNode = p2;
					pNode->balansir = 0;
					res = HEIGHT_OK;
				}
			}
		}
		else if (balans == BalanceForDelete) {

			if (pNode->balansir == 1) {
				pNode->balansir = 0;
				res = HEIGHT_DEC;
			}
			else if (pNode->balansir == 0) {
				pNode->balansir = -1;
				res = HEIGHT_OK;
			}
			else {
				TTreeNode<TKey, TVal>* p1 = pNode->pLeft;
				if (p1->balansir != 1) {

					pNode->pLeft = p1->pRight;
					p1->pRight = pNode;
					if (p1->balansir == 0) {
						pNode->balansir = -1;
						p1->balansir = 1;
						res = HEIGHT_OK;
					}
					else {
						pNode->balansir = 0;
						p1->balansir = 0;
						res = HEIGHT_DEC;
					}
					pNode = p1;
				}
				else {

					TTreeNode<TKey, TVal>* p2 = p1->pRight;
					p1->pRight = p2->pLeft;
					p2->pLeft = p1;
					pNode->pLeft = p2->pRight;
					p2->pRight = pNode;

					if (p2->balansir == -1) {
						pNode->balansir = 1;
						p1->balansir = 0;
					}
					else if (p2->balansir == 1) {
						pNode->balansir = 0;
						p1->balansir = -1;
					}
					else {
						pNode->balansir = 0;
						p1->balansir = 0;
					}
					pNode = p2;
					pNode->balansir = 0;
					res = HEIGHT_DEC;
				}
			}
		}
		return res;
	}

	//функция балансировки справа
	int BalTreeRight(TTreeNode<TKey, TVal>*& pNode, Balance balans) {
		int res = HEIGHT_OK;

		if (balans == BalanceForIns) {
			if (pNode->balansir == -1) {
				pNode->balansir = 0;
				res = HEIGHT_OK;
			}
			else if (pNode->balansir == 0) {
				pNode->balansir = 1;
				res = HEIGHT_INC;
			}
			else {
				TTreeNode<TKey, TVal>* p1 = pNode->pRight;
				if (p1->balansir == 1) {
					pNode->pRight = p1->pLeft;
					p1->pLeft = pNode;
					pNode = p1;
					pNode->balansir = 0;
					pNode->pLeft->balansir = 0;
					res = HEIGHT_OK;
				}
				else {
					TTreeNode<TKey, TVal>* p2 = p1->pLeft;
					p1->pLeft = p2->pRight;
					p2->pRight = p1;
					pNode->pRight = p2->pLeft;
					p2->pLeft = pNode;

					if (p2->balansir == 1) {
						pNode->balansir = -1;
						p1->balansir = 0;
					}
					else if (p2->balansir == -1) {
						pNode->balansir = 0;
						p1->balansir = 1;
					}
					else {
						pNode->balansir = 0;
						p1->balansir = 0;
					}
					pNode = p2;
					pNode->balansir = 0;
					res = HEIGHT_OK;
				}
			}
		}
		else if (balans == BalanceForDelete) {
			if (pNode->balansir == -1) {
				pNode->balansir = 0;
				res = HEIGHT_DEC;
			}
			else if (pNode->balansir == 0) {
				pNode->balansir = 1;
				res = HEIGHT_OK;
			}
			else {
				TTreeNode<TKey, TVal>* p1 = pNode->pRight;
				if (p1->balansir != -1) {
					pNode->pRight = p1->pLeft;
					p1->pLeft = pNode;
					if (p1->balansir == 0) {
						pNode->balansir = 1;
						p1->balansir = -1;
						res = HEIGHT_OK;
					}
					else {
						pNode->balansir = 0;
						p1->balansir = 0;
						res = HEIGHT_DEC;
					}
					pNode = p1;
				}
				else {
					TTreeNode<TKey, TVal>* p2 = p1->pLeft;
					p1->pLeft = p2->pRight;
					p2->pRight = p1;
					pNode->pRight = p2->pLeft;
					p2->pLeft = pNode;

					if (p2->balansir == 1) {
						pNode->balansir = -1;
						p1->balansir = 0;
					}
					else if (p2->balansir == -1) {
						pNode->balansir = 0;
						p1->balansir = 1;
					}
					else {
						pNode->balansir = 0;
						p1->balansir = 0;
					}
					pNode = p2;
					pNode->balansir = 0;
					res = HEIGHT_DEC;
				}
			}
		}
		return res;
	}
public:
	//стандратная вставка
	bool Insert(Record <TKey, TVal> rec) { //функция оболочка для вызова функции рекурсивной вставки с передачей ей корня и текущей записи
		if (this->Find(rec.key)) throw "Record is exist";
		//если записи нет, то вызываем рекурсивную функцию вставки
		InsBalTree(this->pRoot, rec); //корень дерева обязательно будет меняться при каждой вставки
	}

	bool Delete(TKey key) override // оболочка которая вызывает рекурсивную функцию удаления
	{
		if (pRoot == nullptr) return false;
		DeleteRec(pRoot, key);
		return true;
	}
	int DeleteRec(TTreeNode<TKey, TVal>*& pNode, TKey k) //ключ запрошенный на удаление
	{
		int res = HEIGHT_OK;
		Eff++;
		if (pNode == nullptr)
			return res;
		else
		{
			if (pNode->rec.key < k)
			{
				int tmp = DeleteRec(pNode->pRight, k);
				if (tmp == HEIGHT_DEC)
					res = BalTreeLeft(pNode, BalanceForDelete); // вторым параметром нужно передавать флаг который работает при вставке или при удалении
			}
			else if (pNode->rec.key > k)
			{
				int tmp = DeleteRec(pNode->pLeft, k);
				if (tmp == HEIGHT_DEC) ////////////////////////// INC
					res = BalTreeRight(pNode, BalanceForDelete);
			}
			else
			{
				DataCount--;
				if (pNode->pLeft == nullptr && pNode->pRight == nullptr)
				{
					delete pNode;
					pNode = nullptr;
					res = HEIGHT_DEC;
				}
				else if (pNode->pLeft == nullptr)
				{
					TTreeNode<TKey, TVal>* temp = pNode;
					pNode = pNode->pRight;
					delete temp;
					res = HEIGHT_DEC;
				}
				else if (pNode->pRight == nullptr)
				{
					TTreeNode<TKey, TVal>* temp = pNode;
					pNode = pNode->pLeft;
					delete temp;
					res = HEIGHT_DEC;
				}
				else // Оба потомка - КЛЮЧЕВОЕ ИСПРАВЛЕНИЕ
				{
					// Находим минимальный в правом поддереве
					TTreeNode<TKey, TVal>* minNode = pNode->pRight;
					while (minNode->pLeft != nullptr) {
						minNode = minNode->pLeft;
					}

					// Копируем данные
					Record<TKey, TVal> minRec = minNode->rec;

					// Рекурсивно удаляем дубликат
					int tmpRes = DeleteRec(pNode->pRight, minRec.key);
					pNode->rec = minRec;

					// Балансировка
					if (tmpRes == HEIGHT_DEC) {
						res = BalTreeRight(pNode, BalanceForDelete);
					}
				}
			}
		}
		return res;
	}

	TTreeNode<TKey, TVal>* FindMinElementInCurrSubTree(TTreeNode<TKey, TVal>* pNode)
	{
		while (pNode->pLeft != nullptr)
		{
			Eff++;
			pNode = pNode->pLeft;
		}
		return pNode;
	}

	int RemoveMinElementInCurrSubTree(TTreeNode<TKey, TVal>*& pNode)
	{
		Eff++;
		int res = HEIGHT_OK;
		if (pNode->pLeft == nullptr)
		{
			TTreeNode<TKey, TVal>* right_child = pNode->pRight;
			delete pNode;
			pNode = right_child; // Простая замена
			res = HEIGHT_DEC;
		}
		else
		{
			res = RemoveMinElementInCurrSubTree(pNode->pLeft); // Рекурсивный вызов
			if (res != HEIGHT_OK)
				res = BalTreeRight(pNode, BalanceForDelete); // Балансировка правого
		}
		return res;
	}
};