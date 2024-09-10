#include <set>

#include "tests.h"

TEST(multiset, ConstructorDefaultmultiset) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
}

TEST(multiset, ConstructorInitializermultiset) {
  s21::multiset<char> my_multiset = {'x', 'b', 'z', 'y'};
  std::multiset<char> orig_multiset = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(multiset, ConstructorInitializer2multiset) {
  s21::multiset<char> my_multiset = {};
  std::multiset<char> orig_multiset = {};
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(multiset, ConstructorCopymultiset) {
  s21::multiset<int> my_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> orig_multiset = {1, 2, 3, 4, 5};
  s21::multiset<int> my_multiset_copy = my_multiset;
  std::multiset<int> orig_multiset_copy = orig_multiset;
  EXPECT_EQ(my_multiset_copy.size(), orig_multiset_copy.size());
  auto my_it = my_multiset_copy.begin();
  auto orig_it = orig_multiset_copy.begin();
  for (; my_it != my_multiset_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(multiset, Capacitymultiset) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.insert('b');
  orig_empty_multiset.insert('c');
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
}

TEST(multiset, Clearmultiset) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  my_empty_multiset.clear();
  orig_empty_multiset.clear();
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.insert('a');
  orig_empty_multiset.insert('b');
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.clear();
  orig_empty_multiset.clear();
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
}

TEST(multiset, Swapmultiset) {
  s21::multiset<int> my_multiset = {1};
  s21::multiset<int> my_swap_multiset = {3, 4, 5};

  my_multiset.swap(my_swap_multiset);
  EXPECT_EQ(my_multiset.size(), 3);
  EXPECT_EQ(my_swap_multiset.size(), 1);
  EXPECT_EQ(*my_multiset.begin(), 3);
  EXPECT_EQ(*my_swap_multiset.begin(), 1);
}

TEST(multiset, Findmultiset) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_multiset.find(2.4);
  auto orig_it = orig_multiset.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(multiset, Containsmultiset) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_multiset.contains(2), orig_multiset.contains(2));
  EXPECT_EQ(my_multiset.contains(2.1), orig_multiset.contains(2.1));
}

TEST(multiset, Erasemultiset) {
  s21::multiset<int> my_multiset = {5, 4, 3, 2, 7, 8, 9};
  std::multiset<int> orig_multiset = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_multiset.size();
  auto new_size = my_multiset.size();
  EXPECT_EQ(size, new_size);
  my_multiset.erase(my_multiset.begin());
  orig_multiset.erase(orig_multiset.begin());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(multiset, ConstructorMovemultiset) {
  s21::multiset<int> my_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> orig_multiset = {1, 2, 3, 4, 5};
  s21::multiset<int> my_multiset_copy = std::move(my_multiset);
  std::multiset<int> orig_multiset_copy = std::move(orig_multiset);
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  EXPECT_EQ(my_multiset_copy.size(), orig_multiset_copy.size());
  auto my_it = my_multiset_copy.begin();
  auto orig_it = orig_multiset_copy.begin();
  for (; my_it != my_multiset_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_multiset.max_size(), my_multiset.max_size());
}

TEST(multiset, multisetIteratorsmultiset) {
  s21::multiset<std::string> my_multiset = {"This", "is", "my", "multiset"};
  std::multiset<std::string> orig_multiset = {"This", "is", "my", "multiset"};
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_multiset.begin();
  orig_it = orig_multiset.end();
  --my_it;
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(multiset, Mergemultiset) {
  s21::multiset<int> my_multiset = {1};
  s21::multiset<int> my_merge_multiset = {3, 4, 5};
  my_multiset.merge(my_merge_multiset);
  std::multiset<int> orig_multiset = {1};
  std::multiset<int> orig_merge_multiset = {3, 4, 5};
  orig_multiset.merge(orig_merge_multiset);
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_multiset.size(), my_multiset.size());

  EXPECT_EQ(my_merge_multiset.size(), orig_merge_multiset.size());
}

TEST(multiset, Multisetttt) {
  s21::multiset<int> my_merge_multiset = {3, 4, 5, 2, 4, 8, 10, 2};
  EXPECT_EQ(my_merge_multiset.count(2), 2);
  EXPECT_EQ(*(my_merge_multiset.equal_range(3).first), 3);
  EXPECT_EQ(*(my_merge_multiset.upper_bound(5)), 8);
  EXPECT_EQ(*(my_merge_multiset.lower_bound(4)), 4);
  my_merge_multiset.insert_many(1);
  EXPECT_EQ(*(my_merge_multiset.begin()), 1);
}