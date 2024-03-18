#include "../containers.h"
#include "gtest/gtest.h"

using namespace containers;

struct list_test : testing::Test {
  list<int>* m;
  list<int>* m2;
  list<int>* m3;
  void SetUp() {
    m = new list<int>{2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1};
    m2 = new list<int>{2, 5, 4, 6, 6, 5, 4, 4, 8, 8, 8, 8, 9, 9, 9};
    m3 = new list<int>{7, 7, 7, 7, 7, 7, 7, 7, 7};
  }
  void TearDown() {
    delete m;
    delete m2;
    delete m3;
  }

  template <size_t N>
  void CheckEQ(int (&ms)[N], list<int>* ml) {
    list<int>::iterator itr = ml->begin();
    size_t cnt = ml->size();
    for (size_t i = 0; i < cnt; i++, itr++) {
      EXPECT_EQ(ms[i], *itr);
    }
  }
};

TEST_F(list_test, constructors) {
  list<int> m1(5);
  int ma1[] = {0, 0, 0, 0, 0};

  list<int> m2(*m);
  int ma2[] = {2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1};
  list<int> m3(std::move(*m));
  size_t cnt = m1.size();
  for (size_t i = 0; i < cnt; i++) {
    EXPECT_EQ(ma1[i], m1.front());
    m1.pop_front();
  }
  EXPECT_TRUE(m1.empty());
  cnt = m2.size();
  for (size_t i = 0; i < cnt; i++) {
    EXPECT_EQ(ma2[i], m2.front());
    m2.pop_front();
  }
  EXPECT_TRUE(m2.empty());
  cnt = m3.size();
  for (size_t i = 0; i < cnt; i++) {
    EXPECT_EQ(ma2[i], m3.front());
    m3.pop_front();
  }

  EXPECT_TRUE(m3.empty());

  EXPECT_TRUE(m->empty());
};

TEST_F(list_test, insert) {
  m->insert(m->begin(), 4);
  m->insert(m->begin(), 8);
  m->insert(m->end(), 10);
  int mar[] = {8, 4, 2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 10, 1};
  CheckEQ<14>(mar, m);
};

TEST_F(list_test, insert_many) {
  m->insert_many(++(m->cbegin()), 3, 9, 8);
  int mar[] = {2, 3, 9, 8, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1};
  CheckEQ<sizeof(mar) / sizeof(mar[0])>(mar, m);
};

TEST_F(list_test, insert_front) {
  m->insert_many_front(3, 9, 8);
  int mar[] = {3, 9, 8, 2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1};
  CheckEQ<sizeof(mar) / sizeof(mar[0])>(mar, m);
};

TEST_F(list_test, insert_back) {
  m->insert_many_back(3, 9, 8);
  int mar[] = {2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1, 3, 9, 8};
  CheckEQ<sizeof(mar) / sizeof(mar[0])>(mar, m);
};

TEST_F(list_test, clear) {
  m->clear();
  EXPECT_TRUE(m->empty());
}

TEST_F(list_test, reverse) {
  int ar[] = {1, 8, 7, 4, 5, 3, 2, 1, 4, 5, 2};
  m->reverse();
  CheckEQ<11>(ar, m);
}

TEST_F(list_test, sort) {
  int ar[] = {1, 1, 2, 2, 3, 4, 4, 5, 5, 7, 8};
  m->sort();
  CheckEQ<11>(ar, m);
}

TEST_F(list_test, uniq) {
  int ar[] = {2, 5, 4, 1, 3, 7, 8};
  int ar2[] = {2, 5, 4, 6, 8, 9};
  int ar3[] = {7};
  m->unique();
  m2->unique();
  m3->unique();
  CheckEQ<sizeof(ar) / sizeof(ar[0])>(ar, m);
  CheckEQ<sizeof(ar2) / sizeof(ar2[0])>(ar2, m2);
  CheckEQ<sizeof(ar3) / sizeof(ar3[0])>(ar3, m3);
}

TEST_F(list_test, merge) {
  int ar[] = {2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1, 2, 5,
              4, 6, 6, 5, 4, 4, 8, 8, 8, 8, 9, 9, 9};
  m->merge(*m2);
  EXPECT_TRUE(m2->empty());
  CheckEQ<sizeof(ar) / sizeof(ar[0])>(ar, m);
}

TEST_F(list_test, splice) {
  int ar[] = {2, 5, 4, 6, 6, 5, 4, 4, 8, 8, 8, 8, 9,
              9, 9, 2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1};
  m->splice(m->cbegin(), *m2);
  EXPECT_TRUE(m2->empty());
  CheckEQ<sizeof(ar) / sizeof(ar[0])>(ar, m);
}

TEST_F(list_test, push_pop) {
  int ar[] = {11, 2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1, 22};
  int ar2[] = {5, 4, 6, 6, 5, 4, 4, 8, 8, 8, 8, 9, 9};
  m->push_back(22);
  m->push_front(11);
  m2->pop_back();
  m2->pop_front();

  CheckEQ<sizeof(ar) / sizeof(ar[0])>(ar, m);
  CheckEQ<sizeof(ar2) / sizeof(ar2[0])>(ar2, m2);
}

TEST_F(list_test, swap) {
  int ar[] = {2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1};
  int ar2[] = {2, 5, 4, 6, 6, 5, 4, 4, 8, 8, 8, 8, 9, 9, 9};
  m->swap(*m2);
  CheckEQ<sizeof(ar2) / sizeof(ar2[0])>(ar2, m);
  CheckEQ<sizeof(ar) / sizeof(ar[0])>(ar, m2);
}

TEST_F(list_test, front_back) {
  EXPECT_EQ(m->front(), 2);
  EXPECT_EQ(m->back(), 1);
  m->clear();
  EXPECT_EQ(m->front(), 0);
  EXPECT_EQ(m->back(), 0);
}

TEST_F(list_test, move_operator) {
  int ar[] = {2, 5, 4, 1, 2, 3, 5, 4, 7, 8, 1};
  list<int> t;
  t = std::move(*m);
  CheckEQ<sizeof(ar) / sizeof(ar[0])>(ar, &t);
  EXPECT_TRUE(m->empty());
}