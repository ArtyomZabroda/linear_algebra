#include <gtest/gtest.h>
#include "utility.h"
#include "vector.h"
#include <vector>
using namespace zabroda::math;

TEST(UtilityTest, FloatComparison)
{
	float f1{ 3.1f };
	float f2{ 3.1f };
	float f3{ 4.1f };
	float f4{ 3.10000001f };
	EXPECT_TRUE(compare_floats(f1, f2));
	EXPECT_FALSE(compare_floats(f1, f3));
	EXPECT_TRUE(compare_floats(f1, f4));
	compare_floats(f1, f4);
}

TEST(VectorTest, Initialization)
{
	Vector<4, float> v1;
	EXPECT_FLOAT_EQ(v1(0), 0.f);
	EXPECT_FLOAT_EQ(v1(1), 0.f);
	EXPECT_FLOAT_EQ(v1(2), 0.f);
	EXPECT_FLOAT_EQ(v1(3), 0.f);

	Vector<3, double> v2{ 1.,2.,3. };
	EXPECT_FLOAT_EQ(v2(0), 1.f);
	EXPECT_FLOAT_EQ(v2(1), 2.f);
	EXPECT_FLOAT_EQ(v2(2), 3.f);

	Vector<4, double> v3(32.);
	EXPECT_FLOAT_EQ(v3(0), 32.);
	EXPECT_FLOAT_EQ(v3(1), 32.);
	EXPECT_FLOAT_EQ(v3(2), 32.);

	std::vector<float> stdvec(4, 12.f);
	Vector<4, float> v4(stdvec.begin());	
	EXPECT_FLOAT_EQ(v4(0), 12.f);
	EXPECT_FLOAT_EQ(v4(1), 12.f);
	EXPECT_FLOAT_EQ(v4(2), 12.f);
	EXPECT_FLOAT_EQ(v4(3), 12.f);
}

TEST(VectorTest, Assignment)
{
	Vector<4> v{ 1.f, 2.f, 3.f, 4.f };
	v = { 2.f,3.f,4.f,5.f };
	EXPECT_EQ(v(0), 2.f);
	EXPECT_EQ(v(1), 3.f);
	EXPECT_EQ(v(2), 4.f);
	EXPECT_EQ(v(3), 5.f);
}

TEST(VectorTest, Equality)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v2{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v3{ 2.f, 3.f, 4.f, 5.f };
	EXPECT_TRUE(v1 == v2);
	EXPECT_TRUE(v1 != v3);
}

TEST(VectorTest, Adding)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v2{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v3{ 2.f, 4.f, 6.f, 8.f };
	EXPECT_EQ(v1 + v2, v3);
	EXPECT_EQ(v1 += v2, v3);
}

TEST(VectorTest, Subtracting)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v2{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v3{ 0, 0, 0, 0 };
	EXPECT_EQ(v1 - v2, v3);
	EXPECT_EQ(v1 -= v2, v3);
}

TEST(VectorTest, Multiplying)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v2{ 2.f, 4.f, 6.f, 8.f };
	EXPECT_EQ(v1 * 2, v2);
	EXPECT_EQ(v1 *= 2, v2);
}

TEST(VectorTest, Division)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v2{ 2.f, 4.f, 6.f, 8.f };
	EXPECT_EQ(v2 / 2, v1);
	EXPECT_EQ(v2 /= 2, v1);
}

TEST(VectorTest, Negating)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v2{ -1.f, -2.f, -3.f, -4.f };
	EXPECT_EQ(-v1, v2);
}

TEST(VectorTest, Length)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_FLOAT_EQ(length(v1), sqrt(30));
}

TEST(VectorTest, Normalize)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_EQ(normalize(v1), v1/sqrt(30));
}

TEST(VectorTest, DotProduct)
{
	Vector<4> v1{ 1.f, 2.f, 3.f, 4.f };
	Vector<4> v2{ 2.f, 3.f, 4.f, 5.f };
	EXPECT_EQ(dot(v1, v2), 2+6+12+20);
}

TEST(VectorTest, CrossProduct)
{
	Vector<3> v1{ 1,2,3 };
	Vector<3> v2{ 2,3,4 };
	Vector<3> res1{ -1, 2,-1 };
	Vector<3> res2{ 1, -2, 1 };
	EXPECT_EQ(cross(v1, v2), res1);
	EXPECT_EQ(cross(v2, v1), res2);
}