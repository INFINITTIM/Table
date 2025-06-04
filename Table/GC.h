#include <iostream>
#include <stack>
#include <string>

typedef int TKey;

// Предварительные объявления для взаимосвязанных структур
struct TTNode;
class TreeUnballansirBinFindNewVersion;

// Структура управления памятью
struct TMem {
    TTNode* pFirst = nullptr;
    TTNode* pLast = nullptr;
    TTNode* pFree = nullptr;
};

// Узел бинарного дерева
struct TTNode {
    TKey key;
    TTNode* pLeft = nullptr;
    TTNode* pRight = nullptr;
    bool flag_for_garbage = true; // Флаг "мусора" для сборщика (true = доступен для удаления)

    // Статический член - единый менеджер памяти для всех узлов
    static TMem mem;

    // Методы управления памятью
    static void InitMem(int size = 100) { // Инициализация пула памяти
        mem.pFirst = (TTNode*)new char[sizeof(TTNode) * size];
        mem.pFree = mem.pFirst;
        mem.pLast = mem.pFirst + size - 1;
        TTNode* pCurrent = mem.pFirst;
        for (int i = 0; i < size - 1; i++) {
            pCurrent->key = -1;
            pCurrent->pLeft = pCurrent + 1;
            pCurrent = pCurrent + 1;
        }
        mem.pLast->pLeft = nullptr;
        mem.pLast->key = -1;
    }

    static void ClearMem(TreeUnballansirBinFindNewVersion* tree); // Сборка мусора

    static void PrintFree() { // Печать списка свободных узлов
        if (mem.pFree == nullptr) 
            return;
        TTNode* iterator = mem.pFree;
        std::cout << "Свободные ячейки: ";
        while (iterator != nullptr) { 
            if (iterator->key > -1) {
                std::cout << iterator->key << " ";
            }
            iterator = iterator->pLeft;
        }
        std::cout << std::endl;
    }

    // Перегрузка операторов управления памятью
    void* operator new(size_t size) { // Выделение из пула
        TTNode* result = mem.pFree;
        if (mem.pFree != nullptr) {
            mem.pFree = mem.pFree->pLeft;
        }
        return result;
    }

    // Возврат в пул
    void operator delete(void* deleted_element) {
        TTNode* result = (TTNode*)deleted_element;
        result->pLeft = mem.pFree;
        mem.pFree = result;
    }
};

class TreeUnballansirBinFindNewVersion {
    TTNode* pRoot = nullptr;
    TTNode* pCurr = nullptr;
    TTNode* pPrev = nullptr;
    std::stack<TTNode*> st;
    int level = 0;

    void PrintTreeOnScreen(std::ostream& os, TTNode* p) {
        if (p == nullptr) return;
        level++;
        PrintTreeOnScreen(os, p->pRight);
        for (int i = 0; i < level - 1; i++) os << "     ";
        os << p->key << std::endl;
        PrintTreeOnScreen(os, p->pLeft);
        level--;
    }

    void DestroyTree(TTNode* p) {
        if (!p) return;
        DestroyTree(p->pLeft);
        DestroyTree(p->pRight);
        delete p;
    }

public:
    TreeUnballansirBinFindNewVersion() = default;
    ~TreeUnballansirBinFindNewVersion() { Clear(); }

    void Clear() {
        DestroyTree(pRoot);
        pRoot = nullptr;
        pCurr = nullptr;
        pPrev = nullptr;
        level = 0;
        while (!st.empty()) st.pop();
    }

    bool FindElement(TKey key) {
        pCurr = pRoot;
        pPrev = nullptr;
        while (pCurr != nullptr) {
            if (key == pCurr->key) return true;
            pPrev = pCurr;
            if (key < pCurr->key) pCurr = pCurr->pLeft;
            else pCurr = pCurr->pRight;
        }
        pCurr = pPrev;
        return false;
    }

    void InsertElement(TKey key) {
        if (FindElement(key)) throw - 1;
        TTNode* ChildNode = new TTNode();
        ChildNode->key = key;

        if (pRoot == nullptr) pRoot = ChildNode;
        else if (pCurr->key > key) pCurr->pLeft = ChildNode;
        else pCurr->pRight = ChildNode;
    }

    void DeleteElement(TKey key) {
        if (!FindElement(key)) throw - 1;
        if (pPrev != nullptr) {
            if (pPrev->pLeft == pCurr) pPrev->pLeft = nullptr;
            else pPrev->pRight = nullptr;
        }
        delete pCurr;
    }

    void Reset() {
        while (!st.empty()) st.pop();
        pCurr = pRoot;
        while (pCurr != nullptr) {
            st.push(pCurr);
            pCurr = pCurr->pLeft;
        }
        if (!st.empty()) {
            pCurr = st.top();
        }
    }

    void GoNext() {
        if (st.empty()) {
            pCurr = nullptr;
            return;
        }
        TTNode* node = st.top();
        st.pop();
        if (node->pRight != nullptr) {
            node = node->pRight;
            while (node != nullptr) {
                st.push(node);
                node = node->pLeft;
            }
        }
        if (!st.empty()) pCurr = st.top();
        else pCurr = nullptr;
    }

    bool IsEnd() const { return pCurr == nullptr; }
    TTNode* GetCurr() const { return pCurr; }

    void PrintIterator(std::ostream& os) {
        os << "Звенья дерева: ";
        for (Reset(); !IsEnd(); GoNext()) {
            os << GetCurr()->key << " ";
        }
        os << std::endl;
    }

    void Print(std::ostream& os) {
        level = 0;
        PrintTreeOnScreen(os, pRoot);
    }
};

// Реализация ClearMem после определения класса TreeUnballansirBinFindNewVersion
void TTNode::ClearMem(TreeUnballansirBinFindNewVersion* tree) {
    TTNode* tmp = mem.pFree;
    while (tmp != nullptr) {
        tmp->flag_for_garbage = false;
        tmp = tmp->pLeft;
    }
    for (tree->Reset(); !tree->IsEnd(); tree->GoNext()) {
        tree->GetCurr()->flag_for_garbage = false;
    }
    tmp = mem.pFirst;
    while (tmp != mem.pLast) {
        if (tmp->flag_for_garbage) {
            delete tmp;
        }
        tmp->flag_for_garbage = true;
        tmp++;
    }
}