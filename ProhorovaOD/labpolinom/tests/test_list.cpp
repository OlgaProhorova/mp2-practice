#include "gtest.h"
#include "list.h"

class TestList : public ::testing::Test 
{
	protected:
		TRingList<int> list1;
		TRingList<int> list2;
	public:
		TestList() { list2.Insert(6); list2.Insert(1);}
		~TestList() {}
};

TEST(lists, can_create_empty_list)
{
	ASSERT_NO_THROW(TRingList<int> list);
}

TEST_F(TestList, empty_list_is_empty)
{
	EXPECT_EQ(true, !list1.IsNotEnded());
}

TEST_F(TestList, can_copy_empty_list)
{
	ASSERT_NO_THROW(TRingList<int> list(list1));
}

TEST_F(TestList, empty_list_copy_is_correct)
{
	TRingList<int> list(list1);
	EXPECT_NE(list1.GetCurr(), list.GetCurr());
}

TEST_F(TestList, can_assign_empty_list)
{
	ASSERT_NO_THROW(TRingList<int> list = list1);
}

TEST_F(TestList, two_empty_lists_are_eq)
{
	TRingList<int> list,list2;
	EXPECT_EQ(true, list == list2);
}

TEST_F(TestList, assigned_empty_list_is_correct)
{
	TRingList<int> list = list1;
	EXPECT_NE(list1.GetCurr(), list.GetCurr());                                  
}

TEST_F(TestList, can_compare_empty_list_with_itself)
{
	EXPECT_EQ(true, list1 == list1);
}

TEST_F(TestList, can_compare_list_with_itself)
{
	EXPECT_EQ(true, list2 == list2);
}

TEST_F(TestList, can_insert_in_empty_list)
{
	list1.Insert(4);
	list1.Reset();
	EXPECT_EQ(list1.GetCurr(), list1.GetCurr() -> next -> next );
}

TEST_F(TestList, insert_in_empty_list_is_correct)
{
	list1.Insert(4);
	list1.Reset();
	EXPECT_EQ(4, list1.GetCurr() -> data);
}

TEST_F(TestList, can_copy_not_empty_list)
{
	ASSERT_NO_THROW(TRingList<int> list(list2));
}

TEST_F(TestList, not_empty_list_is_copied_correctly_1)
{
	TRingList<int> list(list2);
	EXPECT_NE(list2.GetCurr(), list.GetCurr());
}

TEST_F(TestList, not_empty_list_is_copied_correctly_2)
{
	TRingList<int> list(list2);
	EXPECT_EQ(list.GetCurr(), list.GetCurr()->next->next->next);
}

TEST_F(TestList, not_empty_list_is_copied_correctly_3)
{
	TRingList<int> list(list2);
	list.Reset();
	EXPECT_EQ(1, list.GetCurr()->data);
	EXPECT_EQ(6, list.GetCurr()->next->data);
}

TEST_F(TestList, can_assign_not_empty_list)
{
	ASSERT_NO_THROW(TRingList<int> list = list2);
}

TEST_F(TestList, assigned_not_empty_list_is_correct_1)
{
	TRingList<int> list = list2;
	EXPECT_NE(list.GetCurr(), list2.GetCurr());
}

TEST_F(TestList, assigned_not_empty_list_is_correct_2)
{
	TRingList<int> list = list2;
	EXPECT_EQ(list.GetCurr(), list.GetCurr()->next->next->next);
}

TEST_F(TestList, assigned_not_empty_list_is_correct_3)
{
	TRingList<int> list = list2;
	list.Reset();
	EXPECT_EQ(1, list.GetCurr()->data);
	EXPECT_EQ(6, list.GetCurr()->next->data);
}

TEST_F(TestList, not_empty_lists_are_equal)
{
	TRingList<int> list(list2);
	EXPECT_EQ(true, list == list2);
}

TEST_F(TestList, not_empty_and_empty_lists_are_not_equal)
{
	EXPECT_EQ(false, list2 == list1);
}

TEST_F(TestList, insert_to_the_beginning_1)
{
	list2.Insert(0);
	EXPECT_EQ(list2.GetCurr()->next->next->next->next, list2.GetCurr());
}

TEST_F(TestList, insert_to_the_beginning_2)
{
	list2.Insert(0);
	list2.Reset();
	EXPECT_EQ(0, list2.GetCurr()->data);
	EXPECT_EQ(1, list2.GetCurr()->next->data);
	EXPECT_EQ(6, list2.GetCurr()->next->next->data);
}

TEST_F(TestList, insert_in_the_middle_1)
{
	list2.Insert(3);
	EXPECT_EQ(list2.GetCurr()->next->next->next->next, list2.GetCurr());
}

TEST_F(TestList, insert_in_the_middle_2)
{
	list2.Insert(3);
	list2.Reset();
	EXPECT_EQ(1, list2.GetCurr()->data);
	EXPECT_EQ(3, list2.GetCurr()->next->data);
	EXPECT_EQ(6, list2.GetCurr()->next->next->data);
}

TEST_F(TestList, insert_in_the_end_1)
{
	list2.Insert(8);
	EXPECT_EQ(list2.GetCurr()->next->next->next->next, list2.GetCurr());
}

TEST_F(TestList, insert_in_the_end_2)
{
	list2.Insert(8);
	list2.Reset();
	EXPECT_EQ(1, list2.GetCurr()->data);
	EXPECT_EQ(6, list2.GetCurr()->next->data);
	EXPECT_EQ(8, list2.GetCurr()->next->next->data);
}