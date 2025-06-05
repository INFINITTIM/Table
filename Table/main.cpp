#include <iostream>
#include <string>
#include <random>
#include <ctime>

#include "Record.h"
#include "HashTableUsedList.h"
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "HashTable.h"
#include "HashTableUsedArray.h"
#include "HashTableUsedList.h"
#include "Tree.h"
#include "TreeBalance.h"
#include "GC.h"


class Program
{
    Table<int, int>* table;
    int type = -1;
    bool tableCreated = false;
public:
    int GetType()
    {
        return type;
    }
    int GetEff()
    {
        return table->getEff();
    }
    int GetDC()
    {
        return table->getDataCount();
    }
    bool IsCreateTable() {
        return tableCreated;
    }
    void RemoveElementByKey(int key)
    {
        if (!table)
            return;

        table->Delete(key);
    }
    bool FindElementByKey(int key)
    {
        if (!table)
            return false;

        if (table->Find(key))
        {
            return true;
        }
        return false;
    }
    void CreateTable(int i, int size)
    {
        tableCreated = true;
        if (i == 0) {
            table = new ScanTable<int, int>(size);
            type = 0;
        }
        else if (i == 1) {
            table = new SortTable<int, int>(size);
            type = 1;
        }
        else if (i == 2) {
            table = new HashTableUsedArray<int, int>(size, 3);
            type = 2;
        }
        else if (i == 3) {
            table = new HashTableUsedList<int, int>(size);
            type = 3;
        }
        else if (i == 4) {  // Дерево
            table = new TreeTable<int, int>();
            type = 4;
        }
        else if (i == 5) {  // Сбалансированное дерево
            table = new TreeBalance<int, int>();
            type = 5;
        }
    }
    void Insert(int i, int j)
    {
        if (!table)
            return;
        table->Insert(Record<int, int>{i, j});
    }
    /*void FillRandom(int count, int maxKey)
    {
        // Инициализация генератора случайных чисел
        std::srand(std::time(nullptr));

        for (int i = 0; i < count; i++)
        {
            // Генерация случайного ключа от 1 до maxKey
            int randomKey = 1 + (std::rand() % maxKey);
            // Значение можно сделать таким же как ключ или другое - здесь оставляем 5 как в примере
            //Insert(randomKey, 5);
            table->Insert(Record<int, int>{randomKey, 5});
            if (table->Insert(Record<int, int>{randomKey, 5}) == false)
            {
            }
        }
    }*/

    void FillRandom(int count, int maxKey)
    {
        // Инициализация генератора случайных чисел
        std::srand(std::time(nullptr));

        for(int i = 0; i < count; i++)
        {
            // Генерация случайного ключа от 1 до maxKey
            int randomKey = 1 + (std::rand() % maxKey);

            // Попытка вставить запись
            bool inserted = table->Insert(Record<int, int>{randomKey, 5});
        }
    }
    void Sort(SortType s)
    {
        if (type == 0)
        {
            if(s == SelectS)
                table = new SortTable<int, int>(*((ScanTable<int, int>*)table), SelectS);
            if (s == MergeS)
                table = new SortTable<int, int>(*((ScanTable<int, int>*)table), MergeS);
            if (s == QuickS)
                table = new SortTable<int, int>(*((ScanTable<int, int>*)table), QuickS);

        }
    }
    std::vector<Record<int, int>> GetAllRecords()
    {
        std::vector<Record<int, int>> records;

        if (table)
        {
            table->Reset(); // возвращаемся к началу таблицы
            while (!table->IsEnd()) // продолжаем, пока не достигнем конца
            {
                auto rec = table->getCurr(); // получаем текущую запись
                records.push_back(rec);
                table->GoNext(); // переходим к следующей записи
            }
        }

        return records;
    }

    ~Program()
    {
        delete table;
    }
    friend std::ostream& operator<<(std::ostream& os, Program& t)
    {
        os << *t.table;
        return os;
    }
};

TMem TTNode::mem;

int main() {
    setlocale(LC_ALL, "Russian");

    TTNode::InitMem();

    TreeUnballansirBinFindNewVersion tree;

    tree.InsertElement(50);
    tree.InsertElement(30);
    tree.InsertElement(70);
    tree.InsertElement(20);
    tree.InsertElement(40);
    tree.InsertElement(60);
    tree.InsertElement(80);
    tree.InsertElement(10);
    tree.InsertElement(25);
    tree.InsertElement(35);
    tree.InsertElement(45);
    tree.InsertElement(55);
    tree.InsertElement(65);
    tree.InsertElement(75);
    tree.InsertElement(90);

    std::cout << "Начальная структура дерева:\n";
    tree.Print(std::cout);
    std::cout << "\nОбход:\n";
    tree.PrintIterator(std::cout);

    TTNode::PrintFree();

    std::cout << "\nУдаление узла 30\n";
    tree.DeleteElement(30);
    std::cout << "\nОбновлённая структура дерева:\n";
    tree.Print(std::cout);
    std::cout << "\nОбход:\n";
    tree.PrintIterator(std::cout);

    TTNode::PrintFree();
    std::cout << "\nОчистка памяти\n\n";
    TTNode::ClearMem(&tree);
    TTNode::PrintFree();

    std::cout << "\nВставка нового значения 85\n\n";
    tree.InsertElement(99);
    TTNode::PrintFree();

    std::cout << "\nФинальная структура дерева:\n";
    tree.Print(std::cout);
    std::cout << "\nФинальный обход:\n";
    tree.PrintIterator(std::cout);
}
