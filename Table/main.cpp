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
        if (i == 0)
        {
            table = new ScanTable<int, int>(size);
            type = 0;
        }
        if (i == 1)
        {
            table = new SortTable<int, int>(size);
            type = 1;
        }
        if (i == 2)
        {
            table = new HashTableUsedArray<int, int>(size, 2);
            type = 2;
        }
        if (i == 3)
        {
            table = new HashTableUsedList<int, int>(size);
            type = 3;
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


int main()
{
    setlocale(LC_ALL, "Russian");


    //Program* m = new Program;
    //m->CreateTable(0, 100);
    //m->Insert(3, 5);
    //m->Insert(9, 5);
    //m->Insert(1, 5);
    //m->FillRandom(10, 1000);
    //std::cout << *m;

    TreeBalance<int, int>* ttable = new TreeBalance<int, int>();

    ttable->Insert(Record<int, int>{5, 4});
    ttable->Insert(Record<int, int>{10, 4});
    ttable->Insert(Record<int, int>{2, 4});
    ttable->Insert(Record<int, int>{4, 4});
    ttable->Insert(Record<int, int>{7, 4});
    ttable->Insert(Record<int, int>{8, 4});
    ttable->Insert(Record<int, int>{9, 4});
    //ttable->Delete(5);
    //ttable->Delete(7);
    ttable->Insert(Record<int, int>{6, 4});
    ttable->Insert(Record<int, int>{12, 4});
    ttable->Insert(Record<int, int>{11, 4});

    ttable->Delete(8);
    ttable->Delete(9);
    ttable->Delete(10);
    /*for (int i = 1; i <= 100; i++)
    {
        ttable->Insert(Record<int, int>{i, 4});
    }*/
    //ttable->Insert(Record<int, int>{2, 5});
    std::cout << *ttable;

    return 0;
}

