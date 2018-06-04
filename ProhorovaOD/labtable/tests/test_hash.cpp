#include <gtest.h>
#include "hash.h"
#include "polinom.h"

TEST(HashTable, can_create_HashTable)
{
	ASSERT_NO_THROW(HashTable<int> T);
}

class EmptyHashTable : public testing::Test
{
	protected:
		HashTable<int> Tab;
	public:
		EmptyHashTable() {};
		~EmptyHashTable() {};
};

TEST_F(EmptyHashTable, empty_HashTable_is_empty)
{
	EXPECT_EQ(true, Tab.IsEnded());
}

TEST_F(EmptyHashTable, copy_empty_HashTable)
{
	ASSERT_NO_THROW(HashTable<int> Tab1(Tab));
}

TEST_F(EmptyHashTable, copy_empty_HashTable_correct)
{
	HashTable<int> Tab1(Tab);
	EXPECT_EQ(true, Tab1.IsEnded());
}

TEST_F(EmptyHashTable, can_insert_empty)
{
	ASSERT_NO_THROW(Tab.Insert("first", 1));
	EXPECT_EQ(1, Tab.GetCurr());
	EXPECT_EQ(1, Tab.Search("first"));
}

TEST_F(EmptyHashTable, can_reset_empty)
{
	ASSERT_NO_THROW(Tab.Reset());
}

TEST_F(EmptyHashTable, cant_setnext_empty)
{
	ASSERT_ANY_THROW(Tab.SetNext());
}

TEST_F(EmptyHashTable, cant_delete_empty)
{
	ASSERT_ANY_THROW(Tab.Delete("d"));
}

TEST_F(EmptyHashTable, cant_search_empty)
{
	ASSERT_ANY_THROW(Tab.Search("s"));
}

TEST_F(EmptyHashTable, cant_getcurr_empty)
{
	ASSERT_ANY_THROW(Tab.GetCurr());
}

TEST(HashTable, HASH)
{
	HashTable<TPolinome> Tab;
	TPolinome p;
	p = TPolinome("x+1");
	Tab.Insert("x+1", p);
	p = TPolinome("1+x");
	Tab.Insert("1+x", p);
	p = TPolinome("x^2");
	Tab.Insert("x^2", p);
	p = TPolinome("xyz");
	Tab.Insert("xyz", p);
	p = TPolinome("yx^2");
	Tab.Insert("yx^2", p);
	Tab.Delete("1+x");
	Tab.Delete("xyz");
 //   ASSERT_ANY_THROW(Tab.Delete("xy"));
	ASSERT_ANY_THROW(Tab.Search("xyz"));
}

class FilledHashTable : public testing::Test
{
	protected:
		HashTable<int> Tab;
	public:
		FilledHashTable()
		{
			Tab.Insert("1", 1);
			Tab.Insert("2", 2);
			Tab.Insert("3", 3);
		};
		~FilledHashTable() {};
};

TEST_F(FilledHashTable, can_reset_filled)
{
	ASSERT_NO_THROW(Tab.Reset());
}

TEST_F(FilledHashTable, can_getcurr_filled)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.GetCurr());
}

TEST_F(FilledHashTable, can_setnext_filled)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.SetNext());
}

TEST_F(FilledHashTable, can_search_correct)
{
	ASSERT_NO_THROW(Tab.Search("3"));
	EXPECT_EQ(3, Tab.Search("3"));
}

TEST_F(FilledHashTable, cant_insert_exist)
{
	ASSERT_ANY_THROW(Tab.Insert("2", 2));
}

TEST_F(FilledHashTable, can_copy)
{
	ASSERT_NO_THROW(HashTable<int> Tab1(Tab));
}

TEST_F(FilledHashTable, copy_correct)
{
	HashTable<int> Tab1(Tab);
	Tab1.Reset();
	EXPECT_EQ(1, Tab1.Search("1"));
	EXPECT_EQ(2, Tab1.Search("2"));
	EXPECT_EQ(3, Tab1.Search("3"));
}

TEST_F(FilledHashTable, can_delete)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.Delete("1"));
}