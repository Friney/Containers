#include <array>

#include "../containers.h"
#include "gtest/gtest.h"

using namespace containers;

TEST(containesrs_array, construct_default) {
  array<int, 5> a;
  EXPECT_EQ(a.size(), 5);
}

TEST(containesrs_array, construct_initializer_list) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> std_a = {1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), std_a.size());
  for (int i = 0; i < (int)std_a.size(); ++i) {
    EXPECT_EQ(a[i], std_a[i]);
  }
}

TEST(containesrs_array, copy) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  array<int, 5> a2(a);
  array<int, 5> a3 = a;
  EXPECT_EQ(a2.size(), a3.size());
  for (int i = 0; i < (int)a.size(); ++i) {
    EXPECT_EQ(a2[i], a3[i]);
  }
  EXPECT_TRUE(a.begin() != a3.begin());
}

TEST(containesrs_array, move) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  array<int, 5> a2(a);
  array<int, 5> a3(std::move(a));
  EXPECT_EQ(a2.size(), a3.size());
  for (int i = 0; i < (int)a2.size(); ++i) {
    EXPECT_EQ(a2[i], a3[i]);
  }
  EXPECT_TRUE(a2.begin() != a3.begin());
}

TEST(containesrs_array, max_size) {
  array<int, 5> a;
  std::array<int, 5> std_a;
  EXPECT_EQ(a.max_size(), std_a.max_size());
}

TEST(containesrs_array, swap) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> std_a = {1, 2, 3, 4, 5};
  array<int, 5> a2 = {1, 2, 3, 4, 5};
  std::array<int, 5> std_v2 = {1, 2, 3, 4, 5};
  a.swap(a2);
  std_a.swap(std_v2);
  for (int i = 0; i < (int)std_a.size(); ++i) {
    EXPECT_EQ(a[i], std_a[i]);
  }
  for (int i = 0; i < (int)std_v2.size(); ++i) {
    EXPECT_EQ(a2[i], std_v2[i]);
  }
}

TEST(containesrs_array, data) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  EXPECT_EQ(a.data(), a.begin());
}

TEST(containesrs_array, front_back) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> std_a = {1, 2, 3, 4, 5};
  EXPECT_EQ(a.back(), std_a.back());
  EXPECT_EQ(a.front(), std_a.front());
}

TEST(containesrs_array, at) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  EXPECT_EQ(a[3], a.at(3));
  EXPECT_ANY_THROW(a.at(60));
}

TEST(containesrs_array, fill) {
  array<int, 5> a;
  std::array<int, 5> std_a;
  a.fill(1);
  std_a.fill(1);
  for (size_t i = 0; i < std_a.size(); ++i) {
    EXPECT_EQ(a[i], std_a[i]);
  }
}

TEST(containesrs_array, empty) {
  array<int, 5> a;
  std::array<int, 5> std_a;
  EXPECT_EQ(a.empty(), std_a.empty());
  array<int, 0> a2;
  std::array<int, 0> std_a2;
  EXPECT_EQ(a2.empty(), std_a2.empty());
}