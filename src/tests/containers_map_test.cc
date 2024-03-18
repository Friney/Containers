#include "../containers.h"
#include "gtest/gtest.h"

using namespace containers;

struct map_test : testing::Test {
  map<int, std::string>* m;
  void SetUp() {
    m = new map<int, std::string>{map<int, std::string>::value_type(1, "1"),
                                  map<int, std::string>::value_type(2, "2"),
                                  map<int, std::string>::value_type(3, "3"),
                                  map<int, std::string>::value_type(9, "9"),
                                  map<int, std::string>::value_type(8, "8"),
                                  map<int, std::string>::value_type(7, "7"),
                                  map<int, std::string>::value_type(6, "6"),
                                  map<int, std::string>::value_type(5, "5"),
                                  map<int, std::string>::value_type(4, "4"),
                                  map<int, std::string>::value_type(11, "11"),
                                  map<int, std::string>::value_type(10, "10")};
  }
  void TearDown() { delete m; }
};

TEST_F(map_test, constructor_list) {
  int i[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  std::string s[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
  int itr = 0;
  for (auto start{m->begin()}; start != m->end(); start++) {
    EXPECT_EQ(i[itr], start->first);
    EXPECT_EQ(s[itr], start->second);
    itr++;
  }
};

TEST_F(map_test, rev_iterator) {
  int i[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  std::string s[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
  int itr = 10;
  for (auto start{--(m->end())}; start != m->end(); start--) {
    EXPECT_EQ(i[itr], start->first);
    EXPECT_EQ(s[itr], start->second);
    itr--;
  }
};

TEST_F(map_test, getsize) { EXPECT_EQ(m->size(), 11); };

TEST_F(map_test, remove) {
  m->erase(++(m->begin()));
  m->erase(--(m->end()));

  int i[] = {1, 3, 4, 5, 6, 7, 8, 9, 10};
  std::string s[] = {"1", "3", "4", "5", "6", "7", "8", "9", "10"};
  int itr = 0;
  for (auto start{m->begin()}; start != m->end(); start++) {
    EXPECT_EQ(i[itr], start->first);
    EXPECT_EQ(s[itr], start->second);
    itr++;
  }
};

TEST_F(map_test, constructor) {
  map<int, std::string> m2(*m);
  EXPECT_EQ(m2.size(), m->size());
};

TEST_F(map_test, constructor2) {
  map<int, std::string> m2(std::move(*m));
  EXPECT_EQ(m2.size(), 11);
};

TEST_F(map_test, operator) {
  map<int, std::string> m2;
  m2 = *m;
  EXPECT_EQ(m2.size(), m->size());
};

TEST(map_test1, eq_empty) {
  map<int, std::string> m;
  EXPECT_EQ(m.begin(), m.end());
  EXPECT_TRUE(m.empty());
};

TEST(map_test1, access) {
  map<int, std::string> m;
  m[10] = "10";
  EXPECT_EQ(m.at(10), "10");
  m[5] = "5";
  EXPECT_EQ(m.at(5), "5");
  m[-2] = "-2";
  EXPECT_EQ(m.at(-2), "-2");
  m[5] = "6";
  EXPECT_EQ(m.at(5), "6");
  EXPECT_ANY_THROW(m.at(20));
  EXPECT_NO_THROW(m.at(10));
  EXPECT_TRUE(m.contains(10));
  EXPECT_FALSE(m.contains(40));
  EXPECT_NO_THROW(m.max_size());
};

TEST(map_test1, insert) {
  map<int, std::string> m;
  std::pair<map<int, std::string>::iterator, bool> res = m.insert(10, "10");
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->second, "10");
  res = m.insert(10, "20");
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->second, "10");
  res = m.insert_or_assign(10, "20");
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->second, "20");
  vector<std::pair<map<int, std::string>::iterator, bool>> res2 =
      m.insert_many(map<int, std::string>::value_type{30, "30"},
                    map<int, std::string>::value_type{40, "40"},
                    map<int, std::string>::value_type{30, "50"});
  EXPECT_TRUE(res2[0].second);
  EXPECT_EQ(res2[0].first->second, "30");
  EXPECT_TRUE(res2[1].second);
  EXPECT_EQ(res2[1].first->second, "40");
  EXPECT_FALSE(res2[2].second);
  EXPECT_EQ(res2[2].first->second, "30");
  res = m.insert_or_assign(100, "100");
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->second, "100");
};

TEST_F(map_test, swap) {
  int i[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  std::string s[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
  int i2[] = {-9, -1, 200, 300, 800};
  std::string s2[] = {"-9", "-1", "200", "300", "800"};
  map<int, std::string> m2{map<int, std::string>::value_type(-1, "-1"),
                           map<int, std::string>::value_type(200, "200"),
                           map<int, std::string>::value_type(300, "300"),
                           map<int, std::string>::value_type(-9, "-9"),
                           map<int, std::string>::value_type(800, "800")};
  m->swap(m2);
  int itr = 0;

  for (auto start{m2.begin()}; start != m2.end(); start++) {
    EXPECT_EQ(i[itr], start->first);
    EXPECT_EQ(s[itr], start->second);
    itr++;
  }
  itr = 0;
  for (auto start{m->begin()}; start != m->end(); start++) {
    EXPECT_EQ(i2[itr], start->first);
    EXPECT_EQ(s2[itr], start->second);
    itr++;
  }
};

TEST_F(map_test, merge) {
  int i[] = {-9, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 200, 300, 800};
  std::string s[] = {"-9", "-1", "1", "2", "3", "4", "5", "6",
                     "7", "8", "9", "10", "11", "200", "300", "800"};
  map<int, std::string> m2{map<int, std::string>::value_type(-1, "-1"),
                           map<int, std::string>::value_type(200, "200"),
                           map<int, std::string>::value_type(300, "300"),
                           map<int, std::string>::value_type(-9, "-9"),
                           map<int, std::string>::value_type(800, "800")};
  int itr = 0;

  m->merge(m2);
  for (auto start{m->begin()}; start != m->end(); start++) {
    EXPECT_EQ(i[itr], start->first);
    EXPECT_EQ(s[itr], start->second);
    itr++;
  }
};
