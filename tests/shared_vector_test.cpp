#include <shared_vector.hpp>

#include <gtest/gtest.h>

TEST(SharedVectorTest, DefaultConstructor)
{
    unstd::shared_vector<int> v;

    EXPECT_EQ(v.size(), 0)     << "Default constructor should create a vector with size 0";
    EXPECT_EQ(v.capacity(), 4) << "Default constructor should create a vector with capacity 4";
    EXPECT_EQ(v.empty(), true) << "Default constructor should create a vector that is empty";
}

TEST(SharedVectorTest, PushBackThree)
{
    unstd::shared_vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 3)      << "Push back three elements should increase the size of the vector";
    EXPECT_EQ(v.capacity(), 4)  << "Push back three elements should not change the capacity of the vector";
    EXPECT_EQ(v.empty(), false) << "Push back three elements should not make the vector empty";
    EXPECT_EQ(v[0], 1)          << "Push back three elements should add the correct element to the vector";
    EXPECT_EQ(v[1], 2)          << "Push back three elements should add the correct element to the vector";
    EXPECT_EQ(v[2], 3)          << "Push back three elements should add the correct element to the vector";
}

TEST(SharedVectorTest, CopyConstructor)
{
    unstd::shared_vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    unstd::shared_vector<int> v2(v1);

    EXPECT_EQ(v2.size(), 3)      << "Copy constructor should create a vector with size 3";
    EXPECT_EQ(v2.capacity(), 4)  << "Copy constructor should create a vector with capacity 4";
    EXPECT_EQ(v2.empty(), false) << "Copy constructor should create a vector that is not empty";
    EXPECT_EQ(v2[0], 1)          << "Copy constructor should create a vector with the correct elements";
    EXPECT_EQ(v2[1], 2)          << "Copy constructor should create a vector with the correct elements";
    EXPECT_EQ(v2[2], 3)          << "Copy constructor should create a vector with the correct elements";
}

TEST(SharedVectorTest, CopyAssignment)
{
    unstd::shared_vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    unstd::shared_vector<int> v2;
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);

    v2 = v1;

    EXPECT_EQ(v2.size(), 3)      << "Copy assignment should create a vector with size 3";
    EXPECT_EQ(v2.capacity(), 4)  << "Copy assignment should create a vector with capacity 4";
    EXPECT_EQ(v2.empty(), false) << "Copy assignment should create a vector that is not empty";
    EXPECT_EQ(v2[0], 1)          << "Copy assignment should create a vector with the correct elements";
    EXPECT_EQ(v2[1], 2)          << "Copy assignment should create a vector with the correct elements";
    EXPECT_EQ(v2[2], 3)          << "Copy assignment should create a vector with the correct elements";
}

TEST(SharedVectorTest, MoveConstructor)
{
    unstd::shared_vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    unstd::shared_vector<int> v2(std::move(v1));

    EXPECT_EQ(v2.size(), 3)      << "Move constructor should create a vector with size 3";
    EXPECT_EQ(v2.capacity(), 4)  << "Move constructor should create a vector with capacity 4";
    EXPECT_EQ(v2.empty(), false) << "Move constructor should create a vector that is not empty";
    EXPECT_EQ(v2[0], 1)          << "Move constructor should create a vector with the correct elements";
    EXPECT_EQ(v2[1], 2)          << "Move constructor should create a vector with the correct elements";
    EXPECT_EQ(v2[2], 3)          << "Move constructor should create a vector with the correct elements";
}

TEST(SharedVectorTest, MoveAssignment)
{
    unstd::shared_vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    unstd::shared_vector<int> v2;
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);

    v2 = std::move(v1);

    EXPECT_EQ(v2.size(), 3)      << "Move assignment should create a vector with size 3";
    EXPECT_EQ(v2.capacity(), 4)  << "Move assignment should create a vector with capacity 4";
    EXPECT_EQ(v2.empty(), false) << "Move assignment should create a vector that is not empty";
    EXPECT_EQ(v2[0], 1)          << "Move assignment should create a vector with the correct elements";
    EXPECT_EQ(v2[1], 2)          << "Move assignment should create a vector with the correct elements";
    EXPECT_EQ(v2[2], 3)          << "Move assignment should create a vector with the correct elements";
}

TEST(SharedVectorTest, CustomCapacity)
{
    unstd::shared_vector<int> v;
    v.reserve(10);
    
    EXPECT_EQ(v.size(), 0)      << "Default size should be 0";
    EXPECT_EQ(v.capacity(), 10) << "Custom capacity should be 10";
}

TEST(SharedVectorTest, AutoCapacity)
{
    unstd::shared_vector<int> v;
    EXPECT_EQ(v.capacity(), 4) << "Default capacity should be 4";

    for (std::size_t i = 0; i < 4; ++i)
    {
        v.push_back(i + 1);
        EXPECT_EQ(v.capacity(), 4) << "Capacity should still be 4";
    }

    v.push_back(5);
    EXPECT_EQ(v.capacity(), 8) << "Capacity should have expanded to 8";
}

TEST(SharedVectorTest, MakeSharedVector)
{
    unstd::shared_vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    unstd::shared_vector<int> v2 = unstd::make_shared_vector(v1, v1.begin() + 1, v1.begin() + 4);

    EXPECT_EQ(v2.size(), 3)      << "Make shared vector should create a vector with size 3";
    EXPECT_EQ(v2.capacity(), 3)  << "Make shared vector should create a vector with capacity 3";
    EXPECT_EQ(v2.empty(), false) << "Make shared vector should create a vector that is not empty";
    EXPECT_EQ(v2[0], 2)          << "Make shared vector should create a vector with the correct elements";
    EXPECT_EQ(v2[1], 3)          << "Make shared vector should create a vector with the correct elements";
    EXPECT_EQ(v2[2], 4)          << "Make shared vector should create a vector with the correct elements";
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}