#include <vector>

#include "../containers.h"
#include "gtest/gtest.h"
using namespace containers;

TEST(containesrs_vector, construct_default) {
  vector<int> v;
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.size(), 0);
}

TEST(containesrs_vector, construct_initializer_list) {
  vector<int> v = {1, 2, 3};
  std::vector std_v = {1, 2, 3};
  EXPECT_EQ(v.capacity(), std_v.capacity());
  EXPECT_EQ(v.size(), std_v.size());
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

TEST(containesrs_vector, copy) {
  vector<int> v = {1, 2, 3};
  vector<int> v2(v);
  vector<int> v3 = v;
  EXPECT_EQ(v2.capacity(), v3.capacity());
  EXPECT_EQ(v2.size(), v3.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v2[i], v3[i]);
  }
  EXPECT_TRUE(v.begin() != v3.begin());
}

TEST(containesrs_vector, move) {
  vector<int> v = {1, 2, 3};
  vector<int> v2(v);
  vector<int> v3(std::move(v));
  EXPECT_EQ(v2.capacity(), v3.capacity());
  EXPECT_EQ(v2.size(), v3.size());
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], v3[i]);
  }
  EXPECT_TRUE(v2.begin() != v3.begin());
  auto it = v3.begin();
  v = std::move(v3);
  EXPECT_TRUE(it == v.begin());
}

TEST(containesrs_vector, pop_back) {
  vector<int> v;
  v.pop_back();
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.size(), 0);
}

TEST(containesrs_vector, clean) {
  vector<int> v;
  EXPECT_TRUE(v.empty());
  v.push_back(1);
  EXPECT_FALSE(v.empty());
  v.clear();
  EXPECT_TRUE(v.empty());
}

TEST(containesrs_vector, capacity) {
  vector<int> v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  EXPECT_EQ(v.capacity(), std_v.capacity());
  v.push_back(1);
  std_v.push_back(1);
  EXPECT_EQ(v.capacity(), std_v.capacity());
  v.pop_back();
  std_v.pop_back();
  EXPECT_EQ(v.capacity(), std_v.capacity());
}

TEST(containesrs_vector, max_size) {
  vector<int> v;
  std::vector<int> std_v;
  EXPECT_EQ(v.max_size(), std_v.max_size());
}

TEST(containesrs_vector, insert) {
  vector<int> v = {1, 2, 3, 5};
  std::vector<int> std_v = {1, 2, 3, 5};
  v.insert(v.begin() + 2, 4);
  std_v.insert(std_v.begin() + 2, 4);
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
  v.insert(v.end(), 6);
  std_v.insert(std_v.end(), 6);
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
  v.pop_back();
  std_v.pop_back();
  v.insert(v.begin() + 2, 4);
  std_v.insert(std_v.begin() + 2, 4);
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

TEST(containesrs_vector, reserve) {
  vector<int> v = {1, 2, 3, 5};
  std::vector<int> std_v = {1, 2, 3, 5};
  v.reserve(1);
  std_v.reserve(1);
  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  v.reserve(99);
  std_v.reserve(99);
  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  EXPECT_ANY_THROW(v.reserve(size_t(-1)));
  EXPECT_ANY_THROW(std_v.reserve(size_t(-1)));
}

TEST(containesrs_vector, shrink_to_fit) {
  vector<int> v = {1, 2, 3};
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
  v.push_back(1);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 4);
}

TEST(containesrs_vector, swap) {
  vector<int> v = {1, 2, 3, 5};
  std::vector<int> std_v = {1, 2, 3, 5};
  vector<int> v2 = {1, 2, 3};
  std::vector<int> std_v2 = {1, 2, 3};
  v.swap(v2);
  std_v.swap(std_v2);
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
  for (size_t i = 0; i < std_v2.size(); ++i) {
    EXPECT_EQ(v2[i], std_v2[i]);
  }
}

TEST(containesrs_vector, data) {
  vector<int> v = {1, 2, 3, 5};
  std::vector<int> std_v = {1, 2, 3, 5};
  int* arr_v = v.data();
  int* arr_std_v = std_v.data();
  arr_std_v[0] = 6;
  arr_v[0] = 6;
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

TEST(containesrs_vector, front_back) {
  vector<int> v = {1, 2, 3, 5};
  std::vector<int> std_v = {1, 2, 3, 5};
  EXPECT_EQ(v.back(), std_v.back());
  EXPECT_EQ(v.front(), std_v.front());
}

TEST(containesrs_vector, erase) {
  vector<int> v = {1, 2, 3, 5};
  std::vector<int> std_v = {1, 2, 3, 5};
  v.erase(v.begin() + 2);
  std_v.erase(std_v.begin() + 2);
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
  v.erase(v.end() - 1);
  std_v.erase(std_v.end() - 1);
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

TEST(containesrs_vector, at) {
  vector<int> v = {1, 2, 3, 5};
  EXPECT_EQ(v[3], v.at(3));
  EXPECT_ANY_THROW(v.at(60));
}

TEST(containesrs_vector, insert_many) {
  vector<int> v = {1, 2, 3, 5};
  v.insert_many(v.begin(), 7, 8, 9);

  std::vector<int> std_v{7, 8, 9, 1, 2, 3, 5};
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

TEST(containesrs_vector, insert_many_back) {
  vector<int> v = {1, 2, 3, 5};
  v.insert_many_back(7, 8, 9);

  std::vector<int> std_v{1, 2, 3, 5, 7, 8, 9};
  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}
