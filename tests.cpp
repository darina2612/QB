#include <gtest/gtest.h>
#include "RecordCollection.h"

TEST(RecordCollectionTest, EmptyCollectionTest)
{
    RecordCollection rc;
    EXPECT_EQ(rc.Size(), 0);
}

TEST(RecordCollectionTest, AddTest)
{
    RecordCollection rc;

    for(uint i = 0; i < 10; ++i)
    {
       rc.Add({i, "str1", i % 3, "str2"});
    }

    EXPECT_EQ(rc.Size(), 10);
}

TEST(RecordCollectionTest, IdUniquenessOnAddingTest)
{
    RecordCollection rc;

    EXPECT_TRUE(rc.Add({0, "v1", 2, "v3"}));
    EXPECT_FALSE(rc.Add({0, "v12", 0, "v32"}));

    RecordCollection rc2;
    for(uint i = 0; i < 10; ++i)
    {
       rc.Add({i % 5, "str1", i % 3, "str2"});
    }

    EXPECT_EQ(rc.Size(), 5);
}

TEST(RecordCollectionTest, FetchIdValueTest)
{
    RecordCollection rc;

    for(uint i = 0; i < 10; ++i)
    {
       rc.Add({i, "str1", i % 3, "str2"});
    }

    auto result = rc.FindMatchingRecords("column0", "0");
    EXPECT_EQ(result.Size(), 1);
}

TEST(RecordCollectionTest, FetchNumberValueTest)
{
    RecordCollection rc;

    for(uint i = 0; i < 10; ++i)
    {
       rc.Add({i, "str1", i % 3, "str2"});
    }

    auto result = rc.FindMatchingRecords("column2", "0");
    EXPECT_EQ(result.Size(), 4);
}

TEST(RecordCollectionTest, FetchStringValueTest)
{
    RecordCollection rc;

    for(uint i = 0; i < 10; ++i)
    {
       rc.Add({i, "str" + std::to_string(i % 3), i % 3, "str2"});
    }

    auto result = rc.FindMatchingRecords("column1", "str1");
    EXPECT_EQ(result.Size(), 3);
}

TEST(RecordCollectionTest, FetchMixedColumnValueTest)
{
    RecordCollection rc;

    for(uint i = 0; i < 10; ++i)
    {
       rc.Add({i, "str" + std::to_string(i % 3), i % 3, "str2"});
    }

    auto result = rc.FindMatchingRecords("column1", "1");
    EXPECT_EQ(result.Size(), 0);

    result = rc.FindMatchingRecords("column2", "str1");
    EXPECT_EQ(result.Size(), 0);
}

TEST(RecordCollectionTest, RemoveTest)
{
    RecordCollection rc;
    rc.Add({1, "aa", 10000, "bb"});

    rc.DeleteRecordByID(1);
    EXPECT_EQ(rc.Size(), 0);
}

TEST(RecordCollectionTest, RemoveNonExistentIdTest)
{
    RecordCollection rc;
    rc.Add({1, "aa", 10000, "bb"});

    rc.DeleteRecordByID(0);
    EXPECT_EQ(rc.Size(), 1);
}

TEST(RecordCollectionTest, RemoveAndFetchTest)
{
    RecordCollection rc;

    for(uint i = 0; i < 10; ++i)
    {
       rc.Add({i, "str" + std::to_string(i), i % 3, "str2"});
    }

    rc.DeleteRecordByID(0);

    auto result = rc.FindMatchingRecords("column1", "str0");
    EXPECT_EQ(result.Size(), 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
