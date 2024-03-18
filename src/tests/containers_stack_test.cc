#include "../containers.h"
#include "gtest/gtest.h"

using namespace containers;


struct stack_test : testing::Test {
  stack<int>* m;
  void SetUp() { m = new stack<int>{1, 2, 7, 7, 8, 9}; }
  void TearDown() { delete m; }
};

TEST_F(stack_test, constructor) {
  stack<int> c1;
  stack<std::string> c2;
  stack<int> c3(*m);
  stack<int> c4(std::move(*m));
}

TEST_F(stack_test, insert_back) {
  m->insert_many_front(3, 5, 6);

  EXPECT_EQ(m->top(), 6);
  m->pop();
  EXPECT_EQ(m->top(), 5);
  m->pop();
  EXPECT_EQ(m->top(), 3);
  m->pop();

  EXPECT_EQ(m->top(), 9);
  m->pop();
  EXPECT_EQ(m->top(), 8);
}

TEST_F(stack_test, data_access) {
  EXPECT_EQ(m->top(), 9);
  m->pop();
  EXPECT_EQ(m->top(), 8);
  m->pop();
  EXPECT_EQ(m->top(), 7);
  m->pop();
  EXPECT_EQ(m->top(), 7);
  m->pop();
  EXPECT_EQ(m->top(), 2);
  m->pop();
  EXPECT_EQ(m->top(), 1);
  m->pop();
  m->push(2);
  m->push(3);
  EXPECT_EQ(m->top(), 3);
  m->pop();
  EXPECT_EQ(m->top(), 2);
  m->pop();
  EXPECT_TRUE(m->empty());
}

TEST_F(stack_test, swap) {
  stack<int> s{3, 2, 1};
  m->swap(s);
  EXPECT_EQ(m->top(), 1);
  EXPECT_EQ(s.top(), 9);
}
