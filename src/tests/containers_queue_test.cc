#include "../containers.h"
#include "gtest/gtest.h"

using namespace containers;

struct queue_test : testing::Test {
  queue<int>* m;
  void SetUp() { m = new queue<int>{1, 2, 7, 7, 8, 9}; }
  void TearDown() { delete m; }
};

TEST_F(queue_test, constructor) {
  queue<int> c1;
  queue<std::string> c2;
  queue<int> c3(*m);
  queue<int> c4(std::move(*m));
}

TEST_F(queue_test, insert_back) {
  m->insert_many_back(3, 9, 8);
  EXPECT_EQ(m->front(), 1);
  m->pop();
  EXPECT_EQ(m->front(), 2);
  m->pop();
  EXPECT_EQ(m->front(), 7);
  m->pop();
  EXPECT_EQ(m->front(), 7);
  m->pop();
  EXPECT_EQ(m->front(), 8);
  m->pop();
  EXPECT_EQ(m->front(), 9);
  m->pop();

  EXPECT_EQ(m->front(), 3);
  m->pop();
  EXPECT_EQ(m->front(), 9);
  m->pop();
  EXPECT_EQ(m->front(), 8);
  m->pop();
};

TEST_F(queue_test, data_access) {
  EXPECT_EQ(m->front(), 1);
  m->pop();
  EXPECT_EQ(m->front(), 2);
  m->pop();
  EXPECT_EQ(m->front(), 7);
  m->pop();
  EXPECT_EQ(m->front(), 7);
  m->pop();
  EXPECT_EQ(m->front(), 8);
  m->pop();
  EXPECT_EQ(m->front(), 9);
  m->pop();
  m->push(2);
  m->push(3);
  EXPECT_EQ(m->front(), 2);
  m->pop();
  EXPECT_EQ(m->front(), 3);
  m->pop();
  EXPECT_TRUE(m->empty());
}

TEST_F(queue_test, swap) {
  queue<int> s{3, 2, 1};
  m->swap(s);
  EXPECT_EQ(m->front(), 3);
  EXPECT_EQ(m->back(), 1);
  EXPECT_EQ(s.front(), 1);
  EXPECT_EQ(s.back(), 9);
}
