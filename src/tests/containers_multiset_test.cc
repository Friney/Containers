#include "../containers.h"
#include "gtest/gtest.h"

using namespace containers;

struct multiset_test : testing::Test {
  multiset<int>* m;
  void SetUp() {
    m = new multiset<int>{1, 2, 3, 3, 3, 4, 4, 4, 4, 5, 6, 7, 7, 8, 9};
  }
  void TearDown() { delete m; }
};

TEST_F(multiset_test, constructor) {
  int itr = 0;
  int i[] = {1, 2, 3, 3, 3, 4, 4, 4, 4, 5, 6, 7, 7, 8, 9};
  for (auto start{m->begin()}; start != m->end(); start++) {
    EXPECT_EQ(i[itr], start.value());
    itr++;
  }
}

TEST_F(multiset_test, insert) {
  m->insert(30);
  EXPECT_TRUE(m->contains(30));
  m->insert(40);
  EXPECT_TRUE(m->contains(40));
  m->insert(40);
  EXPECT_EQ(m->count(40), 2);
};

TEST_F(multiset_test, many_insert) {
  vector<std::pair<multiset<int>::iterator, bool>> res =
      m->insert_many(1, 2, 3);
  EXPECT_TRUE(res[0].second);
  EXPECT_EQ(*(res[0].first), 1);
  EXPECT_TRUE(res[1].second);
  EXPECT_EQ(*(res[1].first), 2);
  EXPECT_TRUE(res[2].second);
  EXPECT_EQ(*(res[2].first), 3);
  EXPECT_EQ(m->count(1), 2);
  EXPECT_EQ(m->count(2), 2);
  EXPECT_EQ(m->count(3), 4);
}
TEST_F(multiset_test, count) {
  EXPECT_EQ(m->count(3), 3);
  EXPECT_EQ(m->count(4), 4);
  EXPECT_EQ(m->count(7), 2);
};

TEST_F(multiset_test, find) {
  multiset<int>::iterator itr = m->find(4);
  EXPECT_EQ(itr.value(), 4);
  itr = m->find(6);
  EXPECT_EQ(itr.value(), 6);
};

TEST_F(multiset_test, contains) {
  EXPECT_TRUE(m->contains(5));
  EXPECT_TRUE(m->contains(9));
  EXPECT_FALSE(m->contains(30));
};

TEST_F(multiset_test, range) {
  std::pair<multiset<int>::iterator, multiset<int>::iterator> rres =
      m->equal_range(4);
  int rr[] = {4, 4, 4, 4};
  int itr = 0;
  for (auto start{rres.first}; start != rres.second; start++) {
    EXPECT_EQ(rr[itr], start.value());  //?
    itr++;
  }
  itr = 0;
  rres = m->equal_range(3);
  int rr1[] = {3, 3, 3};
  itr = 0;
  for (auto start{rres.first}; start != rres.second; start++) {
    EXPECT_EQ(rr1[itr], start.value());  //?
    itr++;
  }
  itr = 0;
  rres = m->equal_range(7);
  int rr2[] = {7, 7};
  itr = 0;
  for (auto start{rres.first}; start != rres.second; start++) {
    EXPECT_EQ(rr2[itr], start.value());  //?
    itr++;
  }
}