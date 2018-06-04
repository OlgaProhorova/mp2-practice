#include "gtest.h"
#include "sorted.h"

TEST(SortedTable, can_create_sortedtable)
{
	ASSERT_NO_THROW(SortedTable<int> T);
}

class EmptySortedTable : public testing::Test
{
	protected:
		SortedTable<int> Tab;
	public:
		EmptySortedTable() {};
		~EmptySortedTable() {};
};

TEST_F(EmptySortedTable, empty_sortedtab_is_empty)
{
	EXPECT_EQ(true, Tab.IsEnded());
}

TEST_F(EmptySortedTable, can_copy_empty_sortedtab)
{	
	ASSERT_NO_THROW(SortedTable<int> Tab1(Tab));
}

TEST_F(EmptySortedTable, copy_empty_sortedtab_correct)
{
	SortedTable<int> Tab1(Tab);
	EXPECT_EQ(true, Tab1.IsEnded());
}

TEST_F(EmptySortedTable, cant_delete_empty)
{
	ASSERT_ANY_THROW(Tab.Delete("d"));
}

TEST_F(EmptySortedTable, cant_search_empty)
{
	ASSERT_ANY_THROW(Tab.Search("s"));
}

TEST_F(EmptySortedTable, cant_getcurr_empty)
{
	ASSERT_ANY_THROW(Tab.GetCurr());
}

TEST_F(EmptySortedTable, can_reset_empty)
{
	ASSERT_NO_THROW(Tab.Reset());
	Tab.Reset();
	ASSERT_ANY_THROW(Tab.GetCurr());
}

TEST_F(EmptySortedTable, cant_setnext_empty)
{
	ASSERT_ANY_THROW(Tab.SetNext());
}

TEST_F(EmptySortedTable, can_insert_empty)
{
	ASSERT_NO_THROW(Tab.Insert("first", 1));
	EXPECT_EQ(1, Tab.GetCurr());
	EXPECT_EQ(1, Tab.Search("first"));
}

class FilledSortedTable : public testing::Test
{
	protected:
		SortedTable<int> Tab;
	public:
		FilledSortedTable() 
		{
			Tab.Insert("3", 3);
			Tab.Insert("2", 2);
			Tab.Insert("1", 1);
		};
		~FilledSortedTable() {};
};

TEST_F(FilledSortedTable, can_reset_filled)
{
	ASSERT_NO_THROW(Tab.Reset());
}

TEST_F(FilledSortedTable, can_getcurr_filled)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.GetCurr());
	EXPECT_EQ(1, Tab.GetCurr());
}


TEST_F(FilledSortedTable, can_search)
{
	ASSERT_NO_THROW(Tab.Search("2"));
	EXPECT_EQ(2, Tab.Search("2"));
}

TEST_F(FilledSortedTable, can_insret_exect)
{
	ASSERT_ANY_THROW(Tab.Insert("2", 2));
}

TEST_F(FilledSortedTable, can_setnext_filled)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.SetNext());
	EXPECT_EQ(2, Tab.GetCurr());
}

TEST_F(FilledSortedTable, can_copy)
{
	ASSERT_NO_THROW(SortedTable<int> Tab1(Tab));
}

TEST_F(FilledSortedTable, copy_and_correct)
{
	SortedTable<int> Tab1(Tab);
	Tab1.Reset();
	EXPECT_EQ(1, Tab1.GetCurr());
	Tab1.SetNext();
	EXPECT_EQ(2, Tab1.GetCurr());
	Tab1.SetNext();
	EXPECT_EQ(3, Tab1.GetCurr());
	Tab1.SetNext();
	EXPECT_EQ(1, Tab1.GetCurr());
}

TEST_F(FilledSortedTable, can_delete)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.Delete("1"));
}

TEST_F(FilledSortedTable, can_realloc)
{
	for (int i = 3; i < 10; i++)
		Tab.Insert(to_string(i + 1), i);
	ASSERT_NO_THROW(Tab.Insert("11", 11));
}