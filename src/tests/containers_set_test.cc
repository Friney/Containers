#include "../containers.h"
#include "gtest/gtest.h"

using namespace containers;

struct set_test : testing::Test {
  set<int>* m;
  void SetUp() { m = new set<int>{1, 2, 3, 4, 8, 7, 6, 5, 10}; }
  void TearDown() { delete m; }
};

TEST_F(set_test, find) {
  set<int>::iterator itr = m->find(4);
  EXPECT_EQ(itr.value(), 4);
  itr = m->find(10);
  EXPECT_EQ(itr.value(), 10);
}

TEST_F(set_test, contains) {
  EXPECT_TRUE(m->contains(4));
  EXPECT_FALSE(m->contains(20));
}

TEST_F(set_test, insert) {
  vector<std::pair<set<int>::iterator, bool>> res = m->insert_many(11, 12, 13);
  EXPECT_TRUE(res[0].second);
  EXPECT_EQ(*(res[0].first), 11);
  EXPECT_TRUE(res[1].second);
  EXPECT_EQ(*(res[1].first), 12);
  EXPECT_TRUE(res[2].second);
  EXPECT_EQ(*(res[2].first), 13);

  EXPECT_TRUE(m->contains(11));
  EXPECT_TRUE(m->contains(12));
  EXPECT_TRUE(m->contains(13));
}
