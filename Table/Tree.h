#pragma once

#include "Record.h"
#include "Table.h"
#include "Stack.h"

enum Balansir
{
	LEFTUNBALANC = -1,
	NOUNBALANC = 0 ,
	RIGHTUNBALANC = 1
};


//число потомков у левой и правой части дерева должно отличаться не более чем на 1
//тогда это дерево будет являться сбалансированным и если глубина дерева будет отличаться
//не более чем на 1 

template <typename TKey, typename TVal> 
struct TTreeNode
{
	Record<TKey, TVal> rec; // запись в одном звене дерева
	TTreeNode* pLeft; // указатель на левого потомка
	TTreeNode* pRight; // указатель на правого потомка
	Balansir balansir = Balansir::NOUNBALANC; // проверка сбалансированности
};

template <typename TKey, typename TVal>
class TreeTable : public Table<TKey, TVal>
{
protected:
	TTreeNode<TKey, TVal>* pRoot; // указатель на корень 
	TTreeNode<TKey, TVal>* pCurr; // указатель на текущий узел
	TTreeNode<TKey, TVal>* pPrev; // указатель на предыдущий узел
	LLStack<TTreeNode<TKey, TVal>*> stack; // стек для 
	int pos; //кол-во просмотренных элементов объявим счетчик
	int level; //уровень дерева , на котором располагаются элементы дерева (глубина дерева)
public:
	TreeTable();
	TreeTable(const TreeTable& tree_table);
	~TreeTable();
	void DelNode(TTreeNode<TKey, TVal>* node);

	bool Find(TKey key) override;
	bool Insert(Record<TKey, TVal> rec) override;
	void Delete(TKey key) override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() override;

	void printRec(std::ostream& out, TTreeNode<TKey, TVal>* node, const std::string& prefix, bool isLeft);
	void printTree(std::ostream& os);

	bool IsFull() const override { return false; }

	Record<TKey, TVal> getCurr() const override { return pCurr->rec; }
	TKey getCurrKey() const override { return pCurr->rec.key; }
	TVal getCurrVal() const override { return pCurr->rec.val; }

	//переопредили оператор вывода для дерева
	friend std::ostream& operator<<(std::ostream& os, TreeTable& tree) {
		tree.printTree(os);
		return os;
	}
};
template <typename TKey, typename TVal>
TreeTable<TKey, TVal>::TreeTable() :
	pRoot(nullptr),
	pCurr(nullptr),
	pPrev(nullptr),
	pos(0),
	level(0)
{
}

template <typename TKey, typename TVal>
TreeTable<TKey, TVal>::~TreeTable()
{
	DelNode(pRoot);
}

template <typename TKey, typename TVal>
TreeTable<TKey, TVal>::TreeTable(const TreeTable& tree_table)
{
}

template<class TKey, class TVal>
void TreeTable<TKey, TVal>::DelNode(TTreeNode<TKey, TVal>* node)
{
	if (node == nullptr) return;
	DelNode(node->pLeft);
	DelNode(node->pRight);
	delete node;
}

template <typename TKey, typename TVal>
bool TreeTable<TKey, TVal>::Find(TKey key)
{
	pCurr = pRoot;
	pPrev = nullptr;

	while (pCurr != nullptr)
	{
		Eff++;
		if (pCurr->rec.key == key)
			return true;
		pPrev = pCurr;
		if (key < pCurr->rec.key) // Исправлено условие
			pCurr = pCurr->pLeft; // Двигаемся влево, если искомый ключ меньше
		else
			pCurr = pCurr->pRight; // Иначе вправо
	}
	pCurr = pPrev;
	return false;
}

template <typename TKey, typename TVal>
bool TreeTable<TKey, TVal>::Insert(Record<TKey, TVal> rec) // функция вставки элемента
{
	if (Find(rec.key)) // если такой ключ уже есть в дереве
		return false; // то тогда мы не можем вставить такой элемент
	TTreeNode<TKey, TVal>* new_element = new TTreeNode<TKey, TVal>{ rec, nullptr, nullptr, NOUNBALANC };
	//создаём новое звено с нужными нам параметрами
	DataCount++; // увеличивает кол-во элементов в дереве
	Eff++; // увеличиваем эффективность
	if (pCurr == nullptr) // если дерево пустое то
		pRoot = new_element; // новый элемент становится корнем
	else // иначе если дерево не пустое
	{
		if (rec.key < pCurr->rec.key) 
			pCurr->pLeft = new_element;
		if (rec.key > pCurr->rec.key)
			pCurr->pRight = new_element;
	}
	return true;
}

template<class TKey, class TVal>
void TreeTable<TKey, TVal>::Delete(TKey key) {
	if (!Find(key)) {
		throw -1;
	}
	TTreeNode<TKey, TVal>* nodeToDelete = pCurr;
	//Один потомок слева
	if (pCurr->pRight == nullptr && pCurr->pLeft != nullptr) { //На практике без !=
		Eff++;
		TTreeNode<TKey, TVal>* child = pCurr->pLeft;
		if (nodeToDelete == pRoot) {
			pRoot = child;
		}
		else {
			if (pPrev->pLeft == nodeToDelete) {
				pPrev->pLeft = child;
			}
			else {
				pPrev->pRight = child;
			}
		}
	}
	//Один потомок справа
	else if (pCurr->pLeft == nullptr && pCurr->pRight != nullptr) { //На практике без !=
		Eff++;
		TTreeNode<TKey, TVal>* child = pCurr->pRight;
		if (nodeToDelete == pRoot) {
			pRoot = child;
		}
		else {
			if (pPrev->pLeft == nodeToDelete) {
				pPrev->pLeft = child;
			}
			else {
				pPrev->pRight = child;
			}
		}
	}
	//Нет потомков - Лист
	else if (pCurr->pLeft == nullptr && pCurr->pRight == nullptr) { // На практике не реализовывали
		Eff++;
		if (nodeToDelete == pRoot) {
			pRoot = nullptr;
		}
		else {
			if (pPrev->pLeft == nodeToDelete) {
				pPrev->pLeft = nullptr;
			}
			else {
				pPrev->pRight = nullptr;
			}
		}
	}
	//Оба потомка
	else {
		TTreeNode<TKey, TVal>* beforeMaxLeft = nodeToDelete;
		TTreeNode<TKey, TVal>* maxLeft = nodeToDelete->pLeft;
		while (maxLeft->pRight != nullptr) {
			Eff++;
			beforeMaxLeft = maxLeft;
			maxLeft = maxLeft->pRight;
		}
		nodeToDelete->rec = maxLeft->rec;
		if (nodeToDelete->pLeft == maxLeft) {
			nodeToDelete->pLeft = maxLeft->pLeft;
		}
		else {
			beforeMaxLeft->pRight = maxLeft->pLeft;
		}
		Eff++;
		nodeToDelete = maxLeft;
	}
	delete nodeToDelete;
	DataCount--;
}

template <typename TKey, typename TVal>
void TreeTable<TKey, TVal>::Reset()
{
	//самый маленький элемент - самый первый элемент (так как дерево рисуем по возрастанию его вершин)
	//в стек кладем элементы - потомки от этого маленького элемента, далее извлекаем элементы стека
	//начинаем от корня и идем максимально налево
	pCurr = pRoot;
	// очистка стека
	while (!stack.isEmpty())
		stack.pop();
	while (pCurr->pLeft != nullptr)
	{
		stack.push(pCurr);
		pCurr = pCurr->pLeft;
	}
	stack.push(pCurr);
	pos = 0;
}

template <typename TKey, typename TVal>
void TreeTable<TKey, TVal>::GoNext()
{
	if (stack.isEmpty())
	{
		pCurr = nullptr;
		return;
	}

	stack.pop();
	pCurr = pCurr ? pCurr->pRight : nullptr;
	if (pCurr == nullptr && !stack.isEmpty()) {
		pCurr = stack.top();
	}
	else if (pCurr != nullptr) {
		while (pCurr->pLeft != nullptr) {
			stack.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		stack.push(pCurr);
	}
	pos++;
}

template <typename TKey, typename TVal>
bool TreeTable<TKey, TVal>::IsEnd() 
{
	return pos == this->DataCount;
}

//рекурсиваная функция печати элементов
template <typename TKey, typename TVal>
void TreeTable<TKey, TVal>::printRec(std::ostream& out,
	TTreeNode<TKey, TVal>* node,
	const std::string& prefix,
	bool isLast) {
	if (!node) return;

	out << prefix;
	out << (isLast ? "|- " : "|- "); // Ветвление для текущего узла
	out << node->rec.key << "\n";

	// Собираем новый префикс для дочерних элементов
	std::string new_prefix = prefix + (isLast ? "   " : "|  ");

	// Рекурсивно выводим потомков
	if (node->pLeft || node->pRight) {
		printRec(out, node->pLeft, new_prefix, false); // Левый потомок не последний
		printRec(out, node->pRight, new_prefix, true); // Правый потомок последний
	}
}

template <typename TKey, typename TVal>
void TreeTable<TKey, TVal>::printTree(std::ostream& os) {
	printRec(os, pRoot, "", true);
}


//Пусть у нас есть заранее зафиксированная область памяти из которой мы можем выделять вершины для удаления
/*
	pRoot - самый первый (считаем так)
	  /---|
		  ^           если 90 это лист то он выглядит как |90|0|0|
	|50.|30.|80.|70.|90.|...|...|...|...|.........................|...|...|...|...|...|...|...|...|
			  ^                               FREE ячейки
	  \-------| и тд
													   ^
													   |
	{--------------------------------------------100 вершин-------------------------------------------}
			 pRoot                 |50 и два указателя плефт и прайт|
			  50
		  /       \
		 30        80
	  /     \         \
	20       40        90

	переопределение оператора new

	mem.pFirst                                                          mem.pFree            mem.pLast
	  |                                                                     |                   |
	|...|...|...|...|...|...|...|...|...|.........................|...|...|...|...|...|...|...|...|
	  |   pRight  pLeft
	tree.pRoot

*/


/*
template <typename TKey, typename TVal>
struct TMem
{
	TNode* pFirst;
	TNode* pLast;
	bool flag_for_garbage;
	TNode* pFree;
};

typedef int TKeyForTNode;
template <typename TKey, typename TVal>
struct TTTTTNode
{
	TKeyForTNode key;
	TTTTTNode* pLeft;
	TTTTTNode* pRight;
	bool flag_for_garbage; // является ли мусорным звено или нет
	static TMem mem; // статическое поле не принадлежит и не является полем какого-то конкретного объекта класса
					 // статическое поле будет единым для всех то есть область памяти будет сущ. в ед. экземпляре
	static void InitMem(int size = 100) // инициализация памяти
					 // статический метод соответствует классу всему а не соответствующему объекту
					 // то есть он может вызываться не у конкретного объекта
					 // так как статический метод не привязан ни к какому объекту то он
					 // может работать только со статическими данными
	{
		mem.pFirst = (TNode*)new char[sizeof(TNode) * size];
		mem.pFree = mem.pFirst;
		mem.PLast = mem.pFirst + size - 1;
		TNode* pCurrent = mem.pFirst;
		for (int i = 0; i < size - 1; i++)
		{
			pCurrent->pLeft = pCurrent + 1;
			pCurrent = pCurrent++;
		}
		mem.pLast->pLeft = nullptr;
		mem.pLast->key = -1;
	}
	static void ClearMem(TreeTable<TKey, TVal>* tree) // статический метод для сборки мусора
	{
		// сначала проход по списку свободных потом проход по дереву и финальный прохоод со сборкой мусора
		TTTTTNode* tmp = mem.pFirst;
		while (tmp != nullptr)
		{
			tmp->flag_for_garbage = false;
			tmp = tmp->pLeft
		}
		for (tree->Reset(); !tree->IsEnd(); tree->GoNext())
		{
			tree->getCurr()->flag_for_garbage = false;
		}
		tmp = mem.pFirst;
		while (tmp == mem.pLast)
		{
			if (tmp->flag_for_garbage)
			{
				delete tmp;
			}
			tmp++;
		}
	}
	static void PrintFree(); // отрисовка(печать) свободных ячеек
	// рассмотрим использование new
	// new принимает на вход кол-во выделяемых элементов
	// int* p = new int[10];
	// double* pp = new double[10];
	// а возвращает он указатель на void так как мы заранее
	// не знаем какой именно тип данных мы запросим
	void* operator new(size_t size) // new должен сдвинуть указатель pFree и вернуть состояние указателя
	{
		TNode* result = mem.pFree;
		if (mem.pFree != nullptr)
		{
			mem.pFree = mem.pFree->pLeft;
			return result;
		}
	}
	// оператор delete принимает указатель - void* на память и ничего не возвращает
	// delete p;
	void operator delete(void* deleted_element)
	{
		TNode* tmp = p;
		tmp->pLeft = mem.pFree;
		mem.pFree = tmp;
	}


	TNode() : pLeft(nullptr), pRight(nullptr), flag(false) {}
};

template <typename TKey, typename TVal>
class TreeUnballansirBinFindNewVersion
{
	TTreeNode* pRoot;
	TTreeNode* pCurr;
	TTreeNode* pPrev;
	LLStack<Node*> st;
	int level;

	void PrintTreeOnScreen(Node* p)
	{

	}
public:
	TreeUnballansirBinFindNewVersion();
	TreeUnballansirBinFindNewVersion(const TreeUnballansirBinFindNewVersion& t);
	~TreeUnballansirBinFindNewVersion();

	bool FindElement(TKey key);
	void InsertElement(Record<TKey, TVal> record);
	void DeleteElement(TKey key);

	void Reset()
	{
		while (!st.isEmpty())
			st.pop();
		pCurr = pRoot;
		while (pCurr->pLeft)
		{
			st.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		st.push(pCurr);
	}
	void GoNext()
	{
		st.pop();
		pCurr = pCurr->pRight;
		if(pCurr)
		{
			while(pCurr->pLeft)
			{
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
		}
		else
		{
			if (!st.isEmpty())
				pCurr = st.top();
		}
	}
	bool IsEnd()
	{
		return st.isEmpty();
	}

	//
	// узел который мы хотим удалит мы находим файндом и там
	// устанавливается пкаррент и перед ним ппрев и что мы можем сделать
	// мы можем разорвать у ппрев указатель на пкаррент
	// а все остальное поддерево становится мусором
	//
	// проблема в том что после удаления мы можем не отследить кол-во звеньев
	// в связи с этим нам потребуется модификация иттерационных методов
	//
	// ресет должен установится на самый левый элемент то есть это переход налево до упора
	// модификация ис энд будет строится на том что пустота стека будет являться
	// выполненной функцией ис энд
	//
};

// статическое поле должно быть объявлено до мэина как глобальная статическая переменная
// переменная вне мэина по  правилам является глобал. статик.
// Node::TMem mem;
// void main() {
// .........
// .........
// .........
// Node::InitMem(2000000000000000);
//
										   13
									   /        \
									  8          17
								   /     \      /  \
								  1       11  15    23
							  null  \   ... ... .../  \
									 6           22     27
								 null null   null null null null
		считаем что все листья null считаются чёрными изначально
		так же черный цвет назначается чёрным
		с введением таких вершин у каждого 2 потомка
		у красной вершины обязательно должно быть 2 потомка чёрные
		любой путь от листовой вершины до любой другой вершины содержит одинаковое количество чёрных узлов
*/