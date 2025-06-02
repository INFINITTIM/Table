#include "gtest.h"

#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Record.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Table.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ArrayTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ScanTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\SortTable.h"

TEST(RecordTest, Operator1) {
    Record<int, int> r1{ 1, 1 };
    Record<int, int> r2{ 1, 1 };

    EXPECT_TRUE(r1 == r2);
}

TEST(RecordTest, Operator2) {
    Record<int, int> r1{ 1, 234567 };
    Record<int, int> r2{ 2, 234567 };

    EXPECT_TRUE(r1 != r2);
}

TEST(RecordTest, Operator3) {
    Record<int, int> r1{ 1, 1 };
    Record<int, int> r2{ 4, 4 };

    EXPECT_TRUE(r2 > r1);
}

TEST(RecordTest, Operator4) {
    Record<int, int> r1{ 3, 1 };
    Record<int, int> r2{ 1, 4 };

    EXPECT_TRUE(r1 > r2);
}

TEST(RecordTest, Operator5) {
    Record<int, int> r1{ 1, 1 };
    Record<int, int> r2{ 1, 4 };

    EXPECT_TRUE(r1 >= r2);
    EXPECT_TRUE((r1 == r2) || (r1 > r2));
}

TEST(RecordTest, Operator6) {
    Record<int, int> r1{ 1, 1 };
    Record<int, int> r2{ 3, 4 };

    EXPECT_TRUE(r1 <= r2);
    EXPECT_TRUE((r1 == r2) || (r2 > r1));
}

TEST(ScanTableTest, Insert) {
    ScanTable<int, int> table(10);
    Record<int, int> rec1{ 1, 1 };
    Record<int, int> rec2{ 2, 2 };

    EXPECT_TRUE(table.Insert(rec1));
    EXPECT_TRUE(table.Insert(rec2));
}

TEST(ScanTableTest, Find) {
    ScanTable<int, int> table(10);
    Record<int, int> rec1{ 1, 1 };
    Record<int, int> rec2{ 2, 2 };

    table.Insert(rec1);
    table.Insert(rec2);

    EXPECT_TRUE(table.Find(1));
    EXPECT_EQ(table.getCurrVal(), 1);
}

TEST(ScanTableTest, Delete) {
    ScanTable<int, int> table(10);
    Record<int, int> rec1{ 1, 1 };
    Record<int, int> rec2{ 2, 2 };

    table.Insert(rec1);
    table.Insert(rec2);

    EXPECT_TRUE(table.Delete(1));
    EXPECT_FALSE(table.Find(1));
}

TEST(ScanTableTest, Copy) {
    ScanTable<int, int> t1(10);
    t1.Insert({ 1, 2 });
    ScanTable<int, int> t2 = t1;
    EXPECT_TRUE(t2.Find(1));
}

TEST(ScanTableTest, IsEmpty1) {
    ScanTable<int, int> table(10);
    EXPECT_TRUE(table.IsEmpty());
}
TEST(ScanTableTest, IsEmpty2) {
    ScanTable<int, int> table(10);
    table.Insert({ 1, 1 });
    EXPECT_FALSE(table.IsEmpty());
}
TEST(ScanTableTest, IsEmpty3) {
    ScanTable<int, int> table(10);
    table.Insert({ 1, 1 });
    table.Delete(1);
    EXPECT_TRUE(table.IsEmpty());
}
TEST(ScanTableTest, FindAbsentElement) {
    ScanTable<int, int> table(10);
    table.Insert({ 1, 1 });
    table.Delete(1);
    EXPECT_FALSE(table.Find(1));
}

TEST(ScanTableTest, SSort) {
    Table<int, int>* table;
    table = new ScanTable<int, int>(10);
    table->Insert({ 5, 5 });
    table->Insert({ 2, 2 });
    table->Insert({ 8, 8 });
    table = new SortTable<int, int>(*((ScanTable<int, int>*)table), SelectS);
    table->Reset();
    EXPECT_EQ(table->getCurrKey(), 2);
}

TEST(ScanTableTest, MSort) {
    Table<int, int>* table;
    table = new ScanTable<int, int>(10);
    table->Insert({ 5, 5 });
    table->Insert({ 2, 2 });
    table->Insert({ 8, 8 });
    table = new SortTable<int, int>(*((ScanTable<int, int>*)table), MergeS);
    table->Reset();
    EXPECT_EQ(table->getCurrKey(), 2);
}

TEST(ScanTableTest, QSort) {
    Table<int, int>* table;
    table = new ScanTable<int, int>(10);
    table->Insert({ 5, 5 });
    table->Insert({ 2, 2 });
    table->Insert({ 8, 8 });
    table = new SortTable<int, int>(*((ScanTable<int, int>*)table), QuickS);
    table->Reset();
    EXPECT_EQ(table->getCurrKey(), 2);
}

TEST(SortTableTest, Sort) {
    SortTable<int, int> table(10);
    table.Insert({ 5, 5 });
    table.Insert({ 2, 2 });
    table.Insert({ 8, 8 });
    table.Reset();
    EXPECT_EQ(table.getCurrKey(), 2);
}

TEST(SortTableTest, Sort)
{

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