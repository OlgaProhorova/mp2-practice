#include "gtest.h"
#include "polinom.h"

#include <vector>

using namespace std;

TEST(TMonom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom m);
}

TEST(TPolinome, can_create_polinom)
{
	ASSERT_NO_THROW(TPolinome p);
}

TEST(TPolinome, can_copy_polinoms)
{
	TPolinome a("x^4");
	ASSERT_NO_THROW(TPolinome b(a));
}

TEST(TPolinome, copy_polinoms_correct)
{
	TPolinome a("x^4");
	TPolinome b(a);
	EXPECT_EQ(a, b);
}

TEST(TPolinome, can_assign_polinoms)
{
	TPolinome a("x^2");
	TPolinome b;
	ASSERT_NO_THROW(b = a);
}

TEST(TPolinome, assign_polinoms_correct)
{
	TPolinome a("x^2");
	TPolinome b = a;
	EXPECT_EQ(a, b);
}

TEST(TPolinome, can_sum_polinoms)
{
	TPolinome a("x^2+z-1");
	TPolinome b("x^2-z-1");
	TPolinome c("2x^2-2");
	EXPECT_EQ(c, a + b);
}

TEST(TPolinome, can_dif_polinoms)
{
	TPolinome a("x^2+y^3+z-2");
	TPolinome b("x^2-y^3+z-1");
	TPolinome c("2y^3-1");
	EXPECT_EQ(c, a - b);
}

TEST(TPolinome, can_mul_polinoms)
{
	TPolinome a("x^2+y^1-1");
	TPolinome b("z^2");
	TPolinome c("x^2*z^2+y^1*z^2-z^2");
	EXPECT_EQ(c, a * b);
}

TEST(TPolinome, can_mul_polinom_on_const)
{
	TPolinome a("x^2-1");
	int k = 10;
	TPolinome c("10x^2-10");
	EXPECT_EQ(c, a*k);
	EXPECT_EQ(c, k*a);
}

TEST(TPolinome, degree_not_more_than_9)    
{
	TPolinome a("x^5"), b("x^5");
	ASSERT_ANY_THROW(a*b);
}