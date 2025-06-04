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


//����� �������� � ����� � ������ ����� ������ ������ ���������� �� ����� ��� �� 1
//����� ��� ������ ����� �������� ���������������� � ���� ������� ������ ����� ����������
//�� ����� ��� �� 1 

template <typename TKey, typename TVal> 
struct TTreeNode
{
	Record<TKey, TVal> rec; // ������ � ����� ����� ������
	TTreeNode* pLeft; // ��������� �� ������ �������
	TTreeNode* pRight; // ��������� �� ������� �������
	Balansir balansir = Balansir::NOUNBALANC; // �������� ������������������
};

template <typename TKey, typename TVal>
class TreeTable : public Table<TKey, TVal>
{
protected:
	TTreeNode<TKey, TVal>* pRoot; // ��������� �� ������ 
	TTreeNode<TKey, TVal>* pCurr; // ��������� �� ������� ����
	TTreeNode<TKey, TVal>* pPrev; // ��������� �� ���������� ����
	LLStack<TTreeNode<TKey, TVal>*> stack; // ���� ��� 
	int pos; //���-�� ������������� ��������� ������� �������
	int level; //������� ������ , �� ������� ������������� �������� ������ (������� ������)
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

	//������������ �������� ������ ��� ������
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
		if (key < pCurr->rec.key) // ���������� �������
			pCurr = pCurr->pLeft; // ��������� �����, ���� ������� ���� ������
		else
			pCurr = pCurr->pRight; // ����� ������
	}
	pCurr = pPrev;
	return false;
}

template <typename TKey, typename TVal>
bool TreeTable<TKey, TVal>::Insert(Record<TKey, TVal> rec) // ������� ������� ��������
{
	if (Find(rec.key)) // ���� ����� ���� ��� ���� � ������
		return false; // �� ����� �� �� ����� �������� ����� �������
	TTreeNode<TKey, TVal>* new_element = new TTreeNode<TKey, TVal>{ rec, nullptr, nullptr, NOUNBALANC };
	//������ ����� ����� � ������� ��� �����������
	DataCount++; // ����������� ���-�� ��������� � ������
	Eff++; // ����������� �������������
	if (pCurr == nullptr) // ���� ������ ������ ��
		pRoot = new_element; // ����� ������� ���������� ������
	else // ����� ���� ������ �� ������
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
	//���� ������� �����
	if (pCurr->pRight == nullptr && pCurr->pLeft != nullptr) { //�� �������� ��� !=
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
	//���� ������� ������
	else if (pCurr->pLeft == nullptr && pCurr->pRight != nullptr) { //�� �������� ��� !=
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
	//��� �������� - ����
	else if (pCurr->pLeft == nullptr && pCurr->pRight == nullptr) { // �� �������� �� �������������
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
	//��� �������
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
	//����� ��������� ������� - ����� ������ ������� (��� ��� ������ ������ �� ����������� ��� ������)
	//� ���� ������ �������� - ������� �� ����� ���������� ��������, ����� ��������� �������� �����
	//�������� �� ����� � ���� ����������� ������
	pCurr = pRoot;
	// ������� �����
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

//������������ ������� ������ ���������
template <typename TKey, typename TVal>
void TreeTable<TKey, TVal>::printRec(std::ostream& out,
	TTreeNode<TKey, TVal>* node,
	const std::string& prefix,
	bool isLast) {
	if (!node) return;

	out << prefix;
	out << (isLast ? "|- " : "|- "); // ��������� ��� �������� ����
	out << node->rec.key << "\n";

	// �������� ����� ������� ��� �������� ���������
	std::string new_prefix = prefix + (isLast ? "   " : "|  ");

	// ���������� ������� ��������
	if (node->pLeft || node->pRight) {
		printRec(out, node->pLeft, new_prefix, false); // ����� ������� �� ���������
		printRec(out, node->pRight, new_prefix, true); // ������ ������� ���������
	}
}

template <typename TKey, typename TVal>
void TreeTable<TKey, TVal>::printTree(std::ostream& os) {
	printRec(os, pRoot, "", true);
}


//����� � ��� ���� ������� ��������������� ������� ������ �� ������� �� ����� �������� ������� ��� ��������
/*
	pRoot - ����� ������ (������� ���)
	  /---|
		  ^           ���� 90 ��� ���� �� �� �������� ��� |90|0|0|
	|50.|30.|80.|70.|90.|...|...|...|...|.........................|...|...|...|...|...|...|...|...|
			  ^                               FREE ������
	  \-------| � ��
													   ^
													   |
	{--------------------------------------------100 ������-------------------------------------------}
			 pRoot                 |50 � ��� ��������� ����� � �����|
			  50
		  /       \
		 30        80
	  /     \         \
	20       40        90

	��������������� ��������� new

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
	bool flag_for_garbage; // �������� �� �������� ����� ��� ���
	static TMem mem; // ����������� ���� �� ����������� � �� �������� ����� ������-�� ����������� ������� ������
					 // ����������� ���� ����� ������ ��� ���� �� ���� ������� ������ ����� ���. � ��. ����������
	static void InitMem(int size = 100) // ������������� ������
					 // ����������� ����� ������������� ������ ����� � �� ���������������� �������
					 // �� ���� �� ����� ���������� �� � ����������� �������
					 // ��� ��� ����������� ����� �� �������� �� � ������ ������� �� ��
					 // ����� �������� ������ �� ������������ �������
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
	static void ClearMem(TreeTable<TKey, TVal>* tree) // ����������� ����� ��� ������ ������
	{
		// ������� ������ �� ������ ��������� ����� ������ �� ������ � ��������� ������� �� ������� ������
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
	static void PrintFree(); // ���������(������) ��������� �����
	// ���������� ������������� new
	// new ��������� �� ���� ���-�� ���������� ���������
	// int* p = new int[10];
	// double* pp = new double[10];
	// � ���������� �� ��������� �� void ��� ��� �� �������
	// �� ����� ����� ������ ��� ������ �� ��������
	void* operator new(size_t size) // new ������ �������� ��������� pFree � ������� ��������� ���������
	{
		TNode* result = mem.pFree;
		if (mem.pFree != nullptr)
		{
			mem.pFree = mem.pFree->pLeft;
			return result;
		}
	}
	// �������� delete ��������� ��������� - void* �� ������ � ������ �� ����������
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
	// ���� ������� �� ����� ������ �� ������� ������� � ���
	// ��������������� �������� � ����� ��� ����� � ��� �� ����� �������
	// �� ����� ��������� � ����� ��������� �� ��������
	// � ��� ��������� ��������� ���������� �������
	//
	// �������� � ��� ��� ����� �������� �� ����� �� ��������� ���-�� �������
	// � ����� � ���� ��� ����������� ����������� ������������� �������
	//
	// ����� ������ ����������� �� ����� ����� ������� �� ���� ��� ������� ������ �� �����
	// ����������� �� ��� ����� �������� �� ��� ��� ������� ����� ����� ��������
	// ����������� �������� �� ���
	//
};

// ����������� ���� ������ ���� ��������� �� ����� ��� ���������� ����������� ����������
// ���������� ��� ����� ��  �������� �������� ������. ������.
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
		������� ��� ��� ������ null ��������� ������� ����������
		��� �� ������ ���� ����������� ������
		� ��������� ����� ������ � ������� 2 �������
		� ������� ������� ����������� ������ ���� 2 ������� ������
		����� ���� �� �������� ������� �� ����� ������ ������� �������� ���������� ���������� ������ �����
*/