#include <gtest.h>
#include "scan.h"

TEST(ScanTable, can_create_ScanTable)
{
	ASSERT_NO_THROW(ScanTable<int> T);
}

class EmptyScanTable : public testing::Test
{
	protected:
		ScanTable<int> Tab;
	public:
		EmptyScanTable() {};
		~EmptyScanTable() {};
};

TEST_F(EmptyScanTable, empty_ScanTable_is_empty)
{
	EXPECT_EQ(true, Tab.IsEnded());
}

TEST_F(EmptyScanTable, copy_empty_ScanTable)
{
	ASSERT_NO_THROW(ScanTable<int> Tab1(Tab));
}

TEST_F(EmptyScanTable, copy_empty_ScanTable_correct)
{
	ScanTable<int> Tab1(Tab);
	EXPECT_EQ(true, Tab1.IsEnded());
}

TEST_F(EmptyScanTable, cant_getcurr_empty)
{
	ASSERT_ANY_THROW(Tab.GetCurr());
}

TEST_F(EmptyScanTable, can_reset_empty)
{
	ASSERT_NO_THROW(Tab.Reset());
	Tab.Reset();
	ASSERT_ANY_THROW(Tab.GetCurr());
}

TEST_F(EmptyScanTable, can_insert_empty)
{
	ASSERT_NO_THROW(Tab.Insert("first", 1));
}

TEST_F(EmptyScanTable, cant_setnext_empty)
{
	ASSERT_ANY_THROW(Tab.SetNext());
}

TEST_F(EmptyScanTable, cant_delete_empty)
{
	ASSERT_ANY_THROW(Tab.Delete("d"));
}

TEST_F(EmptyScanTable, cant_search_empty)
{
	ASSERT_ANY_THROW(Tab.Search("s"));
}

class FilledScanTable : public testing::Test
{
	protected:
		ScanTable<int> Tab;
	public:
		FilledScanTable() 
		{
			Tab.Insert("1", 1);
			Tab.Insert("2", 2);
			Tab.Insert("3", 3);
		};
		~FilledScanTable() {};
};

TEST_F(FilledScanTable, can_reset_filled)
{
	ASSERT_NO_THROW(Tab.Reset());
}

TEST_F(FilledScanTable, can_getcurr_filled)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.GetCurr());
	EXPECT_EQ(1, Tab.GetCurr());
}

TEST_F(FilledScanTable, can_setnext_filled)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.SetNext());
	EXPECT_EQ(2, Tab.GetCurr());
}

TEST_F(FilledScanTable, can_copy)
{
	ASSERT_NO_THROW(ScanTable<int> Tab1(Tab));
}

TEST_F(FilledScanTable, copy_correct)
{
	ScanTable<int> Tab1(Tab);
	Tab1.Reset();
	EXPECT_EQ(1, Tab1.GetCurr());
	Tab1.SetNext();
	EXPECT_EQ(2, Tab1.GetCurr());
	Tab1.SetNext();
	EXPECT_EQ(3, Tab1.GetCurr());
	Tab1.SetNext();
	EXPECT_EQ(1, Tab1.GetCurr());
}

TEST_F(FilledScanTable, can_delete)
{
	Tab.Reset();
	ASSERT_NO_THROW(Tab.Delete("1"));
}

TEST_F(FilledScanTable, can_realloc)
{
	for (int i = 3; i < 10; i++)
		Tab.Insert(to_string(i + 1), (i + 1));
	ASSERT_NO_THROW(Tab.Insert("11", 11));
}

TEST_F(FilledScanTable, can_search)
{
	ASSERT_NO_THROW(Tab.Search("2"));
	EXPECT_EQ(2, Tab.Search("2"));
}

TEST_F(FilledScanTable, cant_insret_exist)
{
	ASSERT_ANY_THROW(Tab.Insert("2", 2));
}