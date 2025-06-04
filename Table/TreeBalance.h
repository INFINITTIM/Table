#pragma once
#include "Tree.h"

enum HeightChange {
    HEIGHT_OK = 0,
    HEIGHT_INC = 1,
    HEIGHT_DEC = -1
};

enum BalanceMode {
    MODE_INSERT,
    MODE_DELETE
};

template <typename TKey, typename TVal>
class TreeBalance : public TreeTable<TKey, TVal>
{
protected:
    int InsBalTree(TTreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec) {
        int res = HEIGHT_OK;
        if (pNode == nullptr) {
            pNode = new TTreeNode<TKey, TVal>{ rec, nullptr, nullptr, NOUNBALANC };
            res = HEIGHT_INC;
            this->DataCount++;
        }
        else {
            if (rec.key < pNode->rec.key) {
                int tmp = InsBalTree(pNode->pLeft, rec);
                if (tmp == HEIGHT_INC) {
                    res = BalTreeLeft(pNode, MODE_INSERT);
                }
            }
            else if (rec.key > pNode->rec.key) {
                int tmp = InsBalTree(pNode->pRight, rec);
                if (tmp == HEIGHT_INC) {
                    res = BalTreeRight(pNode, MODE_INSERT);
                }
            }
            else {
                throw -1;
            }
        }
        return res;
    }

    int BalTreeLeft(TTreeNode<TKey, TVal>*& pNode, BalanceMode mode) {
        int res = HEIGHT_OK;
        if (mode == MODE_INSERT) {
            if (pNode->balansir == RIGHTUNBALANC) {
                pNode->balansir = NOUNBALANC;
                res = HEIGHT_OK;
            }
            else if (pNode->balansir == NOUNBALANC) {
                pNode->balansir = LEFTUNBALANC;
                res = HEIGHT_INC;
            }
            else { // LEFTUNBALANC
                if (pNode->pLeft == nullptr) {
                    pNode->balansir = NOUNBALANC;
                    return HEIGHT_DEC;
                }

                TTreeNode<TKey, TVal>* p1 = pNode->pLeft;
                if (p1->balansir == LEFTUNBALANC) { // LL
                    pNode->pLeft = p1->pRight;
                    p1->pRight = pNode;
                    pNode = p1;
                    pNode->balansir = NOUNBALANC;
                    pNode->pRight->balansir = NOUNBALANC;
                    res = HEIGHT_OK;
                }
                else { // LR
                    if (p1->pRight == nullptr) {
                        pNode->balansir = NOUNBALANC;
                        return HEIGHT_DEC;
                    }

                    TTreeNode<TKey, TVal>* p2 = p1->pRight;
                    p1->pRight = p2->pLeft;
                    p2->pLeft = p1;
                    pNode->pLeft = p2->pRight;
                    p2->pRight = pNode;

                    if (p2->balansir == LEFTUNBALANC) {
                        pNode->balansir = RIGHTUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    else if (p2->balansir == RIGHTUNBALANC) {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = LEFTUNBALANC;
                    }
                    else {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    pNode = p2;
                    pNode->balansir = NOUNBALANC;
                    res = HEIGHT_OK;
                }
            }
        }
        else { // MODE_DELETE
            if (pNode->balansir == RIGHTUNBALANC) {
                pNode->balansir = NOUNBALANC;
                res = HEIGHT_DEC;
            }
            else if (pNode->balansir == NOUNBALANC) {
                pNode->balansir = LEFTUNBALANC;
                res = HEIGHT_OK;
            }
            else { // LEFTUNBALANC
                if (pNode->pLeft == nullptr) {
                    pNode->balansir = NOUNBALANC;
                    return HEIGHT_DEC;
                }

                TTreeNode<TKey, TVal>* p1 = pNode->pLeft;
                if (p1->balansir != RIGHTUNBALANC) { // LL
                    pNode->pLeft = p1->pRight;
                    p1->pRight = pNode;
                    if (p1->balansir == NOUNBALANC) {
                        pNode->balansir = LEFTUNBALANC;
                        p1->balansir = RIGHTUNBALANC;
                        res = HEIGHT_OK;
                    }
                    else {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = NOUNBALANC;
                        res = HEIGHT_DEC;
                    }
                    pNode = p1;
                }
                else { // LR
                    if (p1->pRight == nullptr) {
                        pNode->balansir = NOUNBALANC;
                        return HEIGHT_DEC;
                    }

                    TTreeNode<TKey, TVal>* p2 = p1->pRight;
                    p1->pRight = p2->pLeft;
                    p2->pLeft = p1;
                    pNode->pLeft = p2->pRight;
                    p2->pRight = pNode;

                    if (p2->balansir == LEFTUNBALANC) {
                        pNode->balansir = RIGHTUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    else if (p2->balansir == RIGHTUNBALANC) {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = LEFTUNBALANC;
                    }
                    else {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    pNode = p2;
                    pNode->balansir = NOUNBALANC;
                    res = HEIGHT_DEC;
                }
            }
        }
        return res;
    }

    int BalTreeRight(TTreeNode<TKey, TVal>*& pNode, BalanceMode mode) {
        int res = HEIGHT_OK;
        if (mode == MODE_INSERT) {
            if (pNode->balansir == LEFTUNBALANC) {
                pNode->balansir = NOUNBALANC;
                res = HEIGHT_OK;
            }
            else if (pNode->balansir == NOUNBALANC) {
                pNode->balansir = RIGHTUNBALANC;
                res = HEIGHT_INC;
            }
            else { // RIGHTUNBALANC
                if (pNode->pRight == nullptr) {
                    pNode->balansir = NOUNBALANC;
                    return HEIGHT_DEC;
                }

                TTreeNode<TKey, TVal>* p1 = pNode->pRight;
                if (p1->balansir == RIGHTUNBALANC) { // RR
                    pNode->pRight = p1->pLeft;
                    p1->pLeft = pNode;
                    pNode = p1;
                    pNode->balansir = NOUNBALANC;
                    pNode->pLeft->balansir = NOUNBALANC;
                    res = HEIGHT_OK;
                }
                else { // RL
                    if (p1->pLeft == nullptr) {
                        pNode->balansir = NOUNBALANC;
                        return HEIGHT_DEC;
                    }

                    TTreeNode<TKey, TVal>* p2 = p1->pLeft;
                    p1->pLeft = p2->pRight;
                    p2->pRight = p1;
                    pNode->pRight = p2->pLeft;
                    p2->pLeft = pNode;

                    if (p2->balansir == RIGHTUNBALANC) {
                        pNode->balansir = LEFTUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    else if (p2->balansir == LEFTUNBALANC) {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = RIGHTUNBALANC;
                    }
                    else {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    pNode = p2;
                    pNode->balansir = NOUNBALANC;
                    res = HEIGHT_OK;
                }
            }
        }
        else { // MODE_DELETE
            if (pNode->balansir == LEFTUNBALANC) {
                pNode->balansir = NOUNBALANC;
                res = HEIGHT_DEC;
            }
            else if (pNode->balansir == NOUNBALANC) {
                pNode->balansir = RIGHTUNBALANC;
                res = HEIGHT_OK;
            }
            else { // RIGHTUNBALANC
                if (pNode->pRight == nullptr) {
                    pNode->balansir = NOUNBALANC;
                    return HEIGHT_DEC;
                }

                TTreeNode<TKey, TVal>* p1 = pNode->pRight;
                if (p1->balansir != LEFTUNBALANC) { // RR
                    pNode->pRight = p1->pLeft;
                    p1->pLeft = pNode;
                    if (p1->balansir == NOUNBALANC) {
                        pNode->balansir = RIGHTUNBALANC;
                        p1->balansir = LEFTUNBALANC;
                        res = HEIGHT_OK;
                    }
                    else {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = NOUNBALANC;
                        res = HEIGHT_DEC;
                    }
                    pNode = p1;
                }
                else { // RL
                    if (p1->pLeft == nullptr) {
                        pNode->balansir = NOUNBALANC;
                        return HEIGHT_DEC;
                    }

                    TTreeNode<TKey, TVal>* p2 = p1->pLeft;
                    p1->pLeft = p2->pRight;
                    p2->pRight = p1;
                    pNode->pRight = p2->pLeft;
                    p2->pLeft = pNode;

                    if (p2->balansir == RIGHTUNBALANC) {
                        pNode->balansir = LEFTUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    else if (p2->balansir == LEFTUNBALANC) {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = RIGHTUNBALANC;
                    }
                    else {
                        pNode->balansir = NOUNBALANC;
                        p1->balansir = NOUNBALANC;
                    }
                    pNode = p2;
                    pNode->balansir = NOUNBALANC;
                    res = HEIGHT_DEC;
                }
            }
        }
        return res;
    }

    TTreeNode<TKey, TVal>* FindMin(TTreeNode<TKey, TVal>* pNode) {
        while (pNode && pNode->pLeft) {
            pNode = pNode->pLeft;
        }
        return pNode;
    }

    int ExcludeMin(TTreeNode<TKey, TVal>*& pNode) {
        int res = HEIGHT_OK;
        if (pNode == nullptr) return HEIGHT_OK;

        if (pNode->pLeft == nullptr) {
            TTreeNode<TKey, TVal>* temp = pNode->pRight;
            delete pNode;
            pNode = temp;
            res = HEIGHT_DEC;
        }
        else {
            res = ExcludeMin(pNode->pLeft);
            if (res != HEIGHT_OK) {
                res = BalTreeLeft(pNode, MODE_DELETE);
            }
        }
        return res;
    }

    int DeleteRec(TTreeNode<TKey, TVal>*& pNode, TKey key) {
        int res = HEIGHT_OK;
        if (pNode == nullptr) {
            return res;
        }

        if (key < pNode->rec.key) {
            int tmp = DeleteRec(pNode->pLeft, key);
            if (tmp != HEIGHT_OK) {
                res = BalTreeRight(pNode, MODE_DELETE);
            }
        }
        else if (key > pNode->rec.key) {
            int tmp = DeleteRec(pNode->pRight, key);
            if (tmp != HEIGHT_OK) {
                res = BalTreeLeft(pNode, MODE_DELETE);
            }
        }
        else {
            this->DataCount--;
            if (pNode->pLeft == nullptr || pNode->pRight == nullptr) {
                TTreeNode<TKey, TVal>* temp = pNode->pLeft ? pNode->pLeft : pNode->pRight;
                if (temp == nullptr) {
                    delete pNode;
                    pNode = nullptr;
                    res = HEIGHT_DEC;
                }
                else {
                    *pNode = *temp;
                    delete temp;
                    res = HEIGHT_DEC;
                }
            }
            else {
                TTreeNode<TKey, TVal>* minNode = FindMin(pNode->pRight);
                pNode->rec = minNode->rec;
                int tmp = ExcludeMin(pNode->pRight);
                if (tmp != HEIGHT_OK) {
                    res = BalTreeLeft(pNode, MODE_DELETE);
                }
            }
        }
        return res;
    }

public:
    TreeBalance() : TreeTable<TKey, TVal>() {}

    bool Insert(Record<TKey, TVal> rec) override {
        if (this->Find(rec.key)) {
            throw -1;
        }
        InsBalTree(this->pRoot, rec);
        return true;
    }

    void Delete(TKey key) override {
        if (this->pRoot == nullptr) {
            throw -1;
        }
        if (!this->Find(key)) {
            throw -1;
        }
        DeleteRec(this->pRoot, key);
    }
};