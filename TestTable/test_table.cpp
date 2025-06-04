#include "gtest.h"

#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Record.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Table.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ArrayTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ScanTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\SortTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Tree.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\TreeBalance.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedArray.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedList.h"

// =============================================
// Тесты для класса Record
// =============================================

TEST(RecordTest, EqualityOperator) {
    Record<int, int> r1{ 5, 10 };
    Record<int, int> r2{ 5, 10 };
    Record<int, int> r3{ 5, 20 };
    Record<int, int> r4{ 6, 10 };

    EXPECT_TRUE(r1 == r2);
    EXPECT_TRUE(r1 == r3);
    EXPECT_FALSE(r1 == r4);
}

TEST(RecordTest, InequalityOperator) {
    Record<int, int> r1{ 5, 10 };
    Record<int, int> r2{ 5, 10 };
    Record<int, int> r3{ 6, 10 };

    EXPECT_FALSE(r1 != r2);
    EXPECT_TRUE(r1 != r3);
}

TEST(RecordTest, ComparisonOperators) {
    Record<int, int> r1{ 5, 10 };
    Record<int, int> r2{ 10, 10 };
    Record<int, int> r3{ 5, 20 };

    EXPECT_TRUE(r1 < r2);
    EXPECT_FALSE(r2 < r1);
    EXPECT_TRUE(r1 <= r2);
    EXPECT_TRUE(r1 <= r1);
    EXPECT_TRUE(r2 > r1);
    EXPECT_TRUE(r2 >= r1);
    EXPECT_TRUE(r1 >= r1);
    EXPECT_FALSE(r1 > r2);
}

// =============================================
// Тесты для класса ScanTable
// =============================================
TEST(ScanTableTest, InsertAndFind) {
    ScanTable<int, int> table(10);
    EXPECT_TRUE(table.Insert({ 1, 10 }));
    EXPECT_TRUE(table.Insert({ 2, 20 }));
    EXPECT_EQ(table.getDataCount(), 2);

    EXPECT_TRUE(table.Find(1));
    EXPECT_EQ(table.getCurrVal(), 10);
    EXPECT_TRUE(table.Find(2));
    EXPECT_EQ(table.getCurrVal(), 20);
}

TEST(ScanTableTest, InsertDuplicate) {
    ScanTable<int, int> table(10);
    table.Insert({ 1, 10 });
    EXPECT_FALSE(table.Insert({ 1, 20 }));
    EXPECT_EQ(table.getDataCount(), 1);
    EXPECT_EQ(table.getCurrVal(), 10);
}

TEST(ScanTableTest, InsertToFullTable) {
    ScanTable<int, int> table(2);
    table.Insert({ 1, 10 });
    table.Insert({ 2, 20 });
    EXPECT_FALSE(table.Insert({ 3, 30 }));
    EXPECT_EQ(table.getDataCount(), 2);
}

TEST(ScanTableTest, DeleteExisting) {
    ScanTable<int, int> table(10);
    table.Insert({ 1, 10 });
    table.Insert({ 2, 20 });

    table.Delete(1);
    EXPECT_EQ(table.getDataCount(), 1);
    EXPECT_FALSE(table.Find(1));
    EXPECT_TRUE(table.Find(2));
}

TEST(ScanTableTest, DeleteNonExisting) {
    ScanTable<int, int> table(10);
    table.Insert({ 1, 10 });
    EXPECT_THROW(table.Delete(2), int);
}

TEST(ScanTableTest, DeleteFromEmpty) {
    ScanTable<int, int> table(10);
    EXPECT_THROW(table.Delete(1), int);
}

// =============================================
// Тесты для класса SortTable
// =============================================
TEST(SortTableTest, InsertInOrder) {
    SortTable<int, int> table(10);
    table.Insert({ 1, 10 });
    table.Insert({ 2, 20 });
    table.Insert({ 3, 30 });

    table.Reset();
    EXPECT_EQ(table.getCurrKey(), 1);
    table.GoNext();
    EXPECT_EQ(table.getCurrKey(), 2);
    table.GoNext();
    EXPECT_EQ(table.getCurrKey(), 3);
}

TEST(SortTableTest, InsertOutOfOrder) {
    SortTable<int, int> table(10);
    table.Insert({ 3, 30 });
    table.Insert({ 1, 10 });
    table.Insert({ 2, 20 });

    table.Reset();
    EXPECT_EQ(table.getCurrKey(), 1);
    table.GoNext();
    EXPECT_EQ(table.getCurrKey(), 2);
    table.GoNext();
    EXPECT_EQ(table.getCurrKey(), 3);
}

TEST(SortTableTest, BinarySearch) {
    SortTable<int, int> table(10);
    for (int i = 0; i < 10; i++) {
        table.Insert({ i, i * 10 });
    }

    EXPECT_TRUE(table.Find(5));
    EXPECT_EQ(table.getCurrVal(), 50);
    EXPECT_FALSE(table.Find(10));
}

TEST(SortTableTest, SelectionSort) {
    ScanTable<int, int> scanTable(10);
    scanTable.Insert({ 3, 30 });
    scanTable.Insert({ 1, 10 });
    scanTable.Insert({ 2, 20 });

    SortTable<int, int> sortTable(scanTable, SelectS);
    sortTable.Reset();
    EXPECT_EQ(sortTable.getCurrKey(), 1);
    sortTable.GoNext();
    EXPECT_EQ(sortTable.getCurrKey(), 2);
    sortTable.GoNext();
    EXPECT_EQ(sortTable.getCurrKey(), 3);
}

TEST(SortTableTest, MergeSort) {
    ScanTable<int, int> scanTable(10);
    for (int i = 9; i >= 0; i--) {
        scanTable.Insert({ i, i * 10 });
    }

    SortTable<int, int> sortTable(scanTable, MergeS);
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(sortTable.Find(i));
        EXPECT_EQ(sortTable.getCurrVal(), i * 10);
    }
}

TEST(SortTableTest, QuickSort) {
    ScanTable<int, int> scanTable(10);
    scanTable.Insert({ 5, 50 });
    scanTable.Insert({ 2, 20 });
    scanTable.Insert({ 8, 80 });
    scanTable.Insert({ 1, 10 });
    scanTable.Insert({ 9, 90 });

    SortTable<int, int> sortTable(scanTable, QuickS);
    sortTable.Reset();
    EXPECT_EQ(sortTable.getCurrKey(), 1);
    sortTable.GoNext();
    EXPECT_EQ(sortTable.getCurrKey(), 2);
    sortTable.GoNext();
    EXPECT_EQ(sortTable.getCurrKey(), 5);
}

TEST(SortTableTest, DeleteMiddle) {
    SortTable<int, int> table(10);
    table.Insert({ 1, 10 });
    table.Insert({ 2, 20 });
    table.Insert({ 3, 30 });

    table.Delete(2);
    EXPECT_EQ(table.getDataCount(), 2);
    table.Reset();
    EXPECT_EQ(table.getCurrKey(), 1);
    table.GoNext();
    EXPECT_EQ(table.getCurrKey(), 3);
}

// =============================================
// Тесты для класса HashTableUsedArray
// =============================================
TEST(HashTableUsedArrayTest, BasicInsertFind) {
    HashTableUsedArray<int, int> table(10, 1);
    EXPECT_TRUE(table.Insert({ 1, 10 }));
    EXPECT_TRUE(table.Insert({ 2, 20 }));

    EXPECT_TRUE(table.Find(1));
    EXPECT_EQ(table.getCurrVal(), 10);
    EXPECT_TRUE(table.Find(2));
    EXPECT_EQ(table.getCurrVal(), 20);
}

TEST(HashTableUsedArrayTest, CollisionResolution) {
    HashTableUsedArray<int, int> table(10, 1);
    // Ключи с одинаковым хешем
    int key1 = 0;
    int key2 = 10;

    EXPECT_TRUE(table.Insert({ key1, 100 }));
    EXPECT_TRUE(table.Insert({ key2, 200 }));

    EXPECT_TRUE(table.Find(key1));
    EXPECT_EQ(table.getCurrVal(), 100);
    EXPECT_TRUE(table.Find(key2));
    EXPECT_EQ(table.getCurrVal(), 200);
}

TEST(HashTableUsedArrayTest, DeleteAndReinsert) {
    HashTableUsedArray<int, int> table(10, 1);
    table.Insert({ 1, 10 });
    table.Insert({ 2, 20 });

    table.Delete(1);
    EXPECT_FALSE(table.Find(1));
    EXPECT_TRUE(table.Insert({ 1, 30 }));
    EXPECT_TRUE(table.Find(1));
    EXPECT_EQ(table.getCurrVal(), 30);
}

TEST(HashTableUsedArrayTest, FullTable) {
    HashTableUsedArray<int, int> table(3, 1);
    table.Insert({ 1, 10 });
    table.Insert({ 2, 20 });
    table.Insert({ 3, 30 });

    EXPECT_FALSE(table.Insert({ 4, 40 }));
    EXPECT_TRUE(table.IsFull());
}

// =============================================
// Тесты для класса HashTableUsedList
// =============================================
TEST(HashTableUsedListTest, BasicOperations) {
    HashTableUsedList<int, int> table(10);
    EXPECT_TRUE(table.Insert({ 1, 10 }));
    EXPECT_TRUE(table.Insert({ 2, 20 }));

    EXPECT_TRUE(table.Find(1));
    EXPECT_EQ(table.getCurrVal(), 10);
    EXPECT_TRUE(table.Find(2));
    EXPECT_EQ(table.getCurrVal(), 20);
}

TEST(HashTableUsedListTest, CollisionHandling) {
    HashTableUsedList<int, int> table(10);
    // Ключи с одинаковым хешем
    int key1 = 0;
    int key2 = 10;

    EXPECT_TRUE(table.Insert({ key1, 100 }));
    EXPECT_TRUE(table.Insert({ key2, 200 }));

    EXPECT_TRUE(table.Find(key1));
    EXPECT_EQ(table.getCurrVal(), 100);
    EXPECT_TRUE(table.Find(key2));
    EXPECT_EQ(table.getCurrVal(), 200);
}

TEST(HashTableUsedListTest, DeleteFromList) {
    HashTableUsedList<int, int> table(10);
    table.Insert({ 1, 10 });
    table.Insert({ 11, 110 }); // Коллизия

    table.Delete(1);
    EXPECT_FALSE(table.Find(1));
    EXPECT_TRUE(table.Find(11));
}

// =============================================
// Тесты для класса TreeTable
// =============================================
TEST(TreeTableTest, InsertAndFind) {
    TreeTable<int, int> tree;
    tree.Insert({ 5, 50 });
    tree.Insert({ 3, 30 });
    tree.Insert({ 7, 70 });

    EXPECT_TRUE(tree.Find(5));
    EXPECT_EQ(tree.getCurrVal(), 50);
    EXPECT_TRUE(tree.Find(3));
    EXPECT_EQ(tree.getCurrVal(), 30);
    EXPECT_TRUE(tree.Find(7));
    EXPECT_EQ(tree.getCurrVal(), 70);
    EXPECT_FALSE(tree.Find(10));
}

TEST(TreeTableTest, InsertDuplicate) {
    TreeTable<int, int> tree;
    tree.Insert({ 5, 50 });
    EXPECT_FALSE(tree.Insert({ 5, 100 }));
    EXPECT_EQ(tree.getCurrVal(), 50);
}

TEST(TreeTableTest, DeleteLeaf) {
    TreeTable<int, int> tree;
    tree.Insert({ 5, 50 });
    tree.Insert({ 3, 30 });
    tree.Insert({ 7, 70 });

    tree.Delete(3);
    EXPECT_FALSE(tree.Find(3));
    EXPECT_TRUE(tree.Find(5));
    EXPECT_TRUE(tree.Find(7));
}

TEST(TreeTableTest, DeleteNodeWithOneChild) {
    TreeTable<int, int> tree;
    tree.Insert({ 5, 50 });
    tree.Insert({ 3, 30 });
    tree.Insert({ 2, 20 });

    tree.Delete(3);
    EXPECT_FALSE(tree.Find(3));
    EXPECT_TRUE(tree.Find(2));
    tree.Reset();
    EXPECT_EQ(tree.getCurrKey(), 2);
    tree.GoNext();
    EXPECT_EQ(tree.getCurrKey(), 5);
}

TEST(TreeTableTest, DeleteNodeWithTwoChildren) {
    TreeTable<int, int> tree;
    tree.Insert({ 5, 50 });
    tree.Insert({ 3, 30 });
    tree.Insert({ 7, 70 });
    tree.Insert({ 6, 60 });
    tree.Insert({ 8, 80 });

    tree.Delete(7);
    EXPECT_FALSE(tree.Find(7));
    EXPECT_TRUE(tree.Find(6));
    EXPECT_TRUE(tree.Find(8));
    EXPECT_TRUE(tree.Find(5));
    EXPECT_TRUE(tree.Find(3));
}

TEST(TreeTableTest, DeleteRoot) {
    TreeTable<int, int> tree;
    tree.Insert({ 5, 50 });
    tree.Insert({ 3, 30 });
    tree.Insert({ 7, 70 });

    tree.Delete(5);
    EXPECT_FALSE(tree.Find(5));
    EXPECT_TRUE(tree.Find(3));
    EXPECT_TRUE(tree.Find(7));
}

TEST(TreeTableTest, InOrderIteration) {
    TreeTable<int, int> tree;
    tree.Insert({ 5, 50 });
    tree.Insert({ 3, 30 });
    tree.Insert({ 7, 70 });
    tree.Insert({ 2, 20 });
    tree.Insert({ 4, 40 });
    tree.Insert({ 6, 60 });
    tree.Insert({ 8, 80 });

    std::vector<int> keys;
    for (tree.Reset(); !tree.IsEnd(); tree.GoNext()) {
        keys.push_back(tree.getCurrKey());
    }

    EXPECT_EQ(keys, std::vector<int>({ 2, 3, 4, 5, 6, 7, 8 }));
}

// =============================================
// Тесты для класса TreeBalance
// =============================================
TEST(TreeBalanceTest, InsertAndBalance) {
    TreeBalance<int, int> tree;
    tree.Insert({ 10, 100 });
    tree.Insert({ 20, 200 });
    tree.Insert({ 30, 300 }); // Should trigger rotation

    // Check structure
    tree.Reset();
    EXPECT_EQ(tree.getCurrKey(), 10);
    tree.GoNext();
    EXPECT_EQ(tree.getCurrKey(), 20);
    tree.GoNext();
    EXPECT_EQ(tree.getCurrKey(), 30);
}

TEST(TreeBalanceTest, DeleteAndBalance) {
    TreeBalance<int, int> tree;
    tree.Insert({ 10, 100 });
    tree.Insert({ 5, 50 });
    tree.Insert({ 15, 150 });
    tree.Insert({ 20, 200 });

    tree.Delete(5);
    EXPECT_FALSE(tree.Find(5));

    // Check if tree remains balanced
    tree.Reset();
    EXPECT_EQ(tree.getCurrKey(), 10);
    tree.GoNext();
    EXPECT_EQ(tree.getCurrKey(), 15);
    tree.GoNext();
    EXPECT_EQ(tree.getCurrKey(), 20);
}

TEST(TreeBalanceTest, ComplexInsertSequence) {
    TreeBalance<int, int> tree;
    // Insert sequence that causes multiple rotations
    tree.Insert({ 30, 300 });
    tree.Insert({ 20, 200 });
    tree.Insert({ 10, 100 }); // LL rotation
    tree.Insert({ 25, 250 });
    tree.Insert({ 5, 50 });
    tree.Insert({ 15, 150 });

    // Expected in-order: 5,10,15,20,25,30
    std::vector<int> keys;
    for (tree.Reset(); !tree.IsEnd(); tree.GoNext()) {
        keys.push_back(tree.getCurrKey());
    }

    EXPECT_EQ(keys, std::vector<int>({ 5, 10, 15, 20, 25, 30 }));
}

TEST(TreeBalanceTest, ComplexDeleteSequence) {
    TreeBalance<int, int> tree;
    tree.Insert({ 30, 300 });
    tree.Insert({ 20, 200 });
    tree.Insert({ 40, 400 });
    tree.Insert({ 10, 100 });
    tree.Insert({ 25, 250 });
    tree.Insert({ 35, 350 });
    tree.Insert({ 50, 500 });

    tree.Delete(20);
    tree.Delete(40);

    // Check remaining elements
    EXPECT_TRUE(tree.Find(10));
    EXPECT_TRUE(tree.Find(25));
    EXPECT_TRUE(tree.Find(30));
    EXPECT_TRUE(tree.Find(35));
    EXPECT_TRUE(tree.Find(50));

    // Check in-order sequence
    std::vector<int> keys;
    for (tree.Reset(); !tree.IsEnd(); tree.GoNext()) {
        keys.push_back(tree.getCurrKey());
    }

    EXPECT_EQ(keys, std::vector<int>({ 10, 25, 30, 35, 50 }));
}

// =============================================
// Тесты производительности и пограничных случаев
// =============================================
TEST(PerformanceTest, LargeScanTableInsert) {
    ScanTable<int, int> table(10000);
    for (int i = 0; i < 10000; i++) {
        ASSERT_TRUE(table.Insert({ i, i * 10 }));
    }
    EXPECT_EQ(table.getDataCount(), 10000);
}

TEST(PerformanceTest, LargeSortTableFind) {
    SortTable<int, int> table(10000);
    for (int i = 0; i < 10000; i++) {
        table.Insert({ i, i * 10 });
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_TRUE(table.Find(i));
        EXPECT_EQ(table.getCurrVal(), i * 10);
    }
}

TEST(PerformanceTest, TreeTableBalancedInsert) {
    TreeTable<int, int> tree;
    // Insert in balanced way
    tree.Insert({ 500, 5000 });
    for (int i = 0; i < 500; i++) {
        tree.Insert({ i, i * 10 });
        tree.Insert({ 1000 - i, (1000 - i) * 10 });
    }
    EXPECT_EQ(tree.getDataCount(), 1001);
}

TEST(EdgeCaseTest, EmptyTableOperations) {
    ScanTable<int, int> table(10);
    EXPECT_FALSE(table.Find(1));
    EXPECT_THROW(table.Delete(1), int);
    EXPECT_TRUE(table.IsEmpty());

    table.Reset();
    EXPECT_TRUE(table.IsEnd());
}

TEST(EdgeCaseTest, MinMaxKeyOperations) {
    SortTable<int, int> table(10);
    table.Insert({ INT_MIN, 1 });
    table.Insert({ INT_MAX, 2 });

    EXPECT_TRUE(table.Find(INT_MIN));
    EXPECT_EQ(table.getCurrVal(), 1);
    EXPECT_TRUE(table.Find(INT_MAX));
    EXPECT_EQ(table.getCurrVal(), 2);
}

// =============================================
// Тесты для проверки эффективности
// =============================================
TEST(EfficiencyTest, ScanTableEfficiency) {
    ScanTable<int, int> table(1000);
    for (int i = 0; i < 1000; i++) {
        table.Insert({ i, i * 10 });
    }

    table.ClearEff();
    table.Find(999);
    EXPECT_GT(table.getEff(), 500); // O(n) efficiency
}

TEST(EfficiencyTest, SortTableEfficiency) {
    SortTable<int, int> table(1000);
    for (int i = 0; i < 1000; i++) {
        table.Insert({ i, i * 10 });
    }

    table.ClearEff();
    table.Find(500);
    EXPECT_LT(table.getEff(), 15); // O(log n) efficiency
}

TEST(EfficiencyTest, HashTableEfficiency) {
    HashTableUsedArray<int, int> table(1000, 1);
    for (int i = 0; i < 1000; i++) {
        table.Insert({ i, i * 10 });
    }

    table.ClearEff();
    table.Find(500);
    EXPECT_LT(table.getEff(), 5); // O(1) average case
}
/*
TEST(SortTableTests, OrderedIteration) {
    SortTable<int, std::string> table(10);
    table.Insert({ 1, "A" });
    table.Insert({ 3, "C" });
    table.Insert({ 2, "B" });
    table.QuickSort();

    std::vector<int> expectedKeys = { 1, 2, 3 };
    std::vector<int> actualKeys;

    table.Reset();
    while (!table.IsEnd()) {
        actualKeys.push_back(table.getKey());
        table.GoNext();
    }

    EXPECT_EQ(expectedKeys, actualKeys);
}
TEST(SortTableTest, InsertDeleteFind) {
    SortTable<int, std::string> table(10);
    table.Insert({ 3, "Three" });
    EXPECT_TRUE(table.Find(3));
    table.Delete(3);
    EXPECT_FALSE(table.Find(3));
}


//ArrayTable Tests
TEST(ArrayTableTests, DeepCopyAndEquality) {
    ScanTable<int, std::string> table1(10);
    table1.Insert({ 1, "One" });
    table1.Insert({ 2, "Two" });

    ScanTable<int, std::string> table2 = table1;
    table2.Insert({ 3, "Three" });

    EXPECT_TRUE(table1.Find(1));
    EXPECT_TRUE(table1.Find(2));
    EXPECT_FALSE(table1.Find(3)); // original не содержит нового ключа

    EXPECT_TRUE(table2.Find(3));  //копия содержит
}

// ArrayHashTable Tests
TEST(ArrayHashTableTest, BasicOperations) {
    ArrayHashTable<int, std::string> table(10);
    table.Insert({ 1, "One" });
    table.Insert({ 11, "Eleven" }); // collision
    EXPECT_TRUE(table.Find(1));
    EXPECT_TRUE(table.Delete(1));
    EXPECT_FALSE(table.Find(1));
}

TEST(ArrayHashTableTest, FullCheck) {
    ArrayHashTable<int, std::string> table(2);
    table.Insert({ 1, "A" });
    table.Insert({ 2, "B" });
    EXPECT_THROW(table.Insert({ 3, "C" }), const char*);
}

TEST(ArrayHashTableTests, InsertDeleteReinsertSameSlot) {
    ArrayHashTable<int, std::string> table(5, 1);
    table.Insert({ 1, "One" });
    EXPECT_TRUE(table.Find(1));
    table.Delete(1);
    EXPECT_FALSE(table.Find(1));

    EXPECT_NO_THROW(table.Insert({ 1, "Reinserted" }));
    EXPECT_TRUE(table.Find(1));
    EXPECT_EQ(table.getValue(), "Reinserted");
}

TEST(ArrayHashTableTests, InsertDeleteInsertAfterFull) {
    ArrayHashTable<int, std::string> table(2, 1);
    table.Insert({ 1, "One" });
    table.Insert({ 2, "Two" });
    EXPECT_THROW(table.Insert({ 3, "Three" }), const char*);

    table.Delete(1);
    EXPECT_NO_THROW(table.Insert({ 3, "Three" }));
    EXPECT_TRUE(table.Find(3));
}
TEST(ArrayHashTableTest, DeleteNonExistentThrows) {
    ArrayHashTable<int, std::string> table(10);
    EXPECT_THROW(table.Delete(404), const char*);
}

// ListHashTable Tests
TEST(ListHashTableTest, InsertFindDelete) {
    ListHashTable2<int, std::string> table(10);
    table.Insert({ 3, "Three" });
    table.Insert({ 13, "Thirteen" }); // same hash index
    EXPECT_TRUE(table.Find(3));
    EXPECT_TRUE(table.Delete(3));
    EXPECT_FALSE(table.Find(3));
}

TEST(ListHashTableTest, IteratorBehavior) {
    ListHashTable2<int, std::string> table(10);
    table.Insert({ 3, "A" });
    table.Insert({ 4, "B" });
    table.Reset();
    int count = 0;
    while (!table.IsEnd()) {
        count++;
        table.GoNext();
    }
    EXPECT_EQ(count, 2);
}

TEST(ListHashTable2Tests, CollisionChainInsertAndFind) {
    ListHashTable2<int, std::string> table(5); // маленький размер для коллизий
    table.Insert({ 1, "One" });
    table.Insert({ 6, "Six" }); // 1 % 5 == 1, 6 % 5 == 1

    EXPECT_TRUE(table.Find(1));
    EXPECT_EQ(table.getValue(), "One");

    EXPECT_TRUE(table.Find(6));
    EXPECT_EQ(table.getValue(), "Six");
}

TEST(TreeTableTest, InsertFindDelete) {
    TreeTable<int, std::string> tree;
    Record<int, std::string> rec1{ 5, "Five" };
    Record<int, std::string> rec2{ 3, "Three" };
    Record<int, std::string> rec3{ 7, "Seven" };

    EXPECT_TRUE(tree.Insert(rec1));
    EXPECT_TRUE(tree.Insert(rec2));
    EXPECT_TRUE(tree.Insert(rec3));

    EXPECT_TRUE(tree.Find(5));
    EXPECT_TRUE(tree.Find(3));
    EXPECT_TRUE(tree.Find(7));
    EXPECT_FALSE(tree.Find(10));

    EXPECT_TRUE(tree.Delete(3));
    EXPECT_FALSE(tree.Find(3));

    EXPECT_TRUE(tree.Delete(5));
    EXPECT_FALSE(tree.Find(5));

    EXPECT_TRUE(tree.Delete(7));
    EXPECT_TRUE(tree.IsEmpty());
}

TEST(TreeTableTest, DuplicateInsertThrows) {
    TreeTable<int, std::string> tree;
    tree.Insert({ 1, "One" });
    EXPECT_THROW(tree.Insert({ 1, "One Again" }), const char*);
}

TEST(TreeTableTest, DeleteNonExistentThrows) {
    TreeTable<int, std::string> tree;
    tree.Insert({ 2, "Two" });
    EXPECT_THROW(tree.Delete(999), const char*);
}*/