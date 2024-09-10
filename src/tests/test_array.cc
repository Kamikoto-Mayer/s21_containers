#include "tests.h"

TEST(arrayMemberFunctionsTests, defaultConstructor) {
  s21::array<int, 0> ar;
  std::array<int, 0> stdAr;
  EXPECT_EQ(ar.empty(), stdAr.empty());
  EXPECT_EQ(ar.size(), stdAr.size());
  EXPECT_EQ(ar.size(), size_t(0));
}

TEST(arrayMemberFunctionsTests, initListConstructor) {
  using size_type = s21::array<int, 4>::size_type;
  s21::array<int, 4> ar = {98, 464, 6, 76};
  std::array<int, 4> stdAr = {98, 464, 6, 76};
  EXPECT_EQ(ar.size(), stdAr.size());
  EXPECT_EQ(ar.size(), size_t(4));
  EXPECT_TRUE(ar[0] = 98);
  EXPECT_TRUE(ar[1] = 464);
  EXPECT_TRUE(ar[2] = 6);
  EXPECT_TRUE(ar[3] = 76);
  for (size_type i = 0; i < ar.size(); i++) {
    EXPECT_EQ(ar[i], stdAr[i]);
  }
}

TEST(arrayMemberFunctionsTests, initListConstructor0Elements) {
  s21::array<int, 0> ar;
  std::array<int, 0> stdAr;
  EXPECT_EQ(ar.empty(), stdAr.empty());
  EXPECT_EQ(ar.size(), stdAr.size());
  EXPECT_EQ(ar.size(), size_t(0));
}

TEST(arrayMemberFunctionsTests, copyConstructor0Elements) {
  s21::array<int, 0> old;
  s21::array<int, 0> ar(old);
  std::array<int, 0> std_old;
  std::array<int, 0> stdAr(std_old);
  EXPECT_EQ(ar.empty(), old.empty());
  EXPECT_EQ(stdAr.empty(), std_old.empty());
  EXPECT_EQ(old.size(), ar.size());
  EXPECT_EQ(std_old.size(), stdAr.size());
  EXPECT_EQ(ar.size(), size_t(0));
  EXPECT_EQ(stdAr.size(), size_t(0));
}

TEST(arrayMemberFunctionsTests, moveConstructor) {
  s21::array<int, 5> old = {4546, 616, 78, 12, 43};
  s21::array<int, 5> ar(std::move(old));
  std::array<int, 5> std_old = {4546, 616, 78, 12, 43};
  std::array<int, 5> stdAr(std::move(std_old));
  EXPECT_FALSE(ar.empty());
  EXPECT_FALSE(stdAr.empty());
  EXPECT_TRUE(ar.size() == 5);
  EXPECT_TRUE(stdAr.size() == 5);
  EXPECT_TRUE(ar[0] = 4546);
  EXPECT_TRUE(ar[1] = 616);
  EXPECT_TRUE(ar[2] = 78);
  EXPECT_TRUE(ar[3] = 12);
  EXPECT_TRUE(ar[4] = 43);
  EXPECT_TRUE(stdAr[0] = 4546);
  EXPECT_TRUE(stdAr[1] = 616);
  EXPECT_TRUE(stdAr[2] = 78);
  EXPECT_TRUE(stdAr[3] = 12);
  EXPECT_TRUE(stdAr[4] = 43);
}

TEST(arrayMemberFunctionsTests, moveConstructor0Elements) {
  s21::array<int, 0> old;
  s21::array<int, 0> ar(std::move(old));
  EXPECT_TRUE(ar.empty());
  EXPECT_EQ(ar.size(), size_t(0));
}

TEST(arrayMemberFunctionsTests, moveAssignOperator) {
  using size_type = s21::array<int, 6>::size_type;
  s21::array<int, 4> old = {97, 46, 4341, 74};
  s21::array<int, 4> ar = {8, 132, 24, 191};
  std::array<int, 4> std_old = {97, 46, 4341, 74};
  std::array<int, 4> stdAr = {8, 132, 24, 191};
  EXPECT_EQ(ar.size(), size_t(4));
  EXPECT_EQ(stdAr.size(), ar.size());
  for (size_type i = 0; i < ar.size(); i++) {
    EXPECT_EQ(ar[i], stdAr[i]);
  }
  ar = std::move(old);
  stdAr = std::move(std_old);
  EXPECT_EQ(ar.size(), size_t(4));
  EXPECT_EQ(stdAr.size(), ar.size());
  for (size_type i = 0; i < ar.size(); i++) {
    EXPECT_EQ(ar[i], stdAr[i]);
  }
}

TEST(arrayMemberFunctionsTests, moveAssignOperator0Elements) {
  s21::array<int, 0> old;
  s21::array<int, 0> ar;
  EXPECT_EQ(ar.size(), size_t(0));
  ar = std::move(old);
  EXPECT_EQ(ar.size(), size_t(0));
  EXPECT_TRUE(ar.empty());
}

TEST(arrayElementAccessTests, atOk) {
  s21::array<int, 6> ar = {4, 97, 13, 735, 651, 981};
  std::array<int, 6> stdAr = {4, 97, 13, 735, 651, 981};
  EXPECT_EQ(ar.at(4), 651);
  EXPECT_EQ(stdAr.at(4), ar.at(4));
}

TEST(arrayElementAccessTests, atError) {
  s21::array<int, 6> ar = {4, 97, 13, 735, 651, 981};
  EXPECT_THROW(ar.at(8), std::out_of_range);
}

TEST(arrayElementAccessTests, operatorSquareBrackets) {
  s21::array<int, 5> ar = {64, 96, 13, 75, 32};
  std::array<int, 5> stdAr = {64, 96, 13, 75, 32};
  EXPECT_EQ(ar[2], 13);
  EXPECT_EQ(stdAr[2], ar[2]);
}

TEST(arrayElementAccessTests, front) {
  s21::array<int, 4> ar = {4, 46, 34, 981};
  std::array<int, 4> stdAr = {4, 46, 34, 981};
  EXPECT_EQ(ar.front(), 4);
  EXPECT_EQ(ar.front(), stdAr.front());
}

TEST(arrayElementAccessTests, frontEmpty) {
  s21::array<int, 0> ar;
  EXPECT_THROW(ar.front(), std::out_of_range);
}

TEST(arrayElementAccessTests, back) {
  s21::array<int, 4> ar = {4, 46, 34, 981};
  std::array<int, 4> stdAr = {4, 46, 34, 981};
  EXPECT_EQ(ar.back(), 981);
  EXPECT_EQ(ar.back(), stdAr.back());
}

TEST(arrayElementAccessTests, back1Element) {
  s21::array<int, 1> ar = {99};
  std::array<int, 1> stdAr = {99};
  EXPECT_EQ(ar.back(), 99);
  EXPECT_EQ(ar.back(), stdAr.back());
}

TEST(arrayElementAccessTests, backEmpty) {
  s21::array<int, 0> ar;
  EXPECT_THROW(ar.back(), std::out_of_range);
}

TEST(arrayElementAccessTests, data) {
  using iterator = s21::array<int, 7>::iterator;
  s21::array<int, 7> ar = {818, 461, 73, 614, 2554, 98, 71};
  std::array<int, 7> stdAr = {818, 461, 73, 614, 2554, 98, 71};
  iterator it = ar.data();
  auto std_it = stdAr.data();
  EXPECT_EQ(ar[0], *it);
  EXPECT_EQ(*std_it, *it);
}

TEST(arrayIteratorsTests, begin) {
  using iterator = s21::array<int, 7>::iterator;
  s21::array<int, 7> ar = {78, 45, 21, 671, 947, 3164, 7456};
  std::array<int, 7> stdAr = {78, 45, 21, 671, 947, 3164, 7456};
  iterator it = ar.begin();
  auto std_it = stdAr.begin();
  EXPECT_EQ(*std_it, *it);
  EXPECT_EQ(ar[0], *it);
  EXPECT_EQ(stdAr[0], *std_it);
}

TEST(arrayIteratorsTests, end) {
  using iterator = s21::array<int, 3>::iterator;
  s21::array<int, 3> ar = {678, 9554, 12};
  iterator it = ar.end();
  EXPECT_EQ(ar[ar.size()], *it);
}

TEST(arrayCapacityTests, empty) {
  s21::array<int, 0> ar;
  std::array<int, 0> stdAr;
  EXPECT_TRUE(ar.empty());
  EXPECT_TRUE(stdAr.empty());
}

TEST(arrayCapacityTests, notEmpty) {
  s21::array<int, 4> ar = {64, 2424, 68, 319};
  std::array<int, 4> stdAr = {64, 2424, 68, 319};
  EXPECT_FALSE(ar.empty());
  EXPECT_FALSE(stdAr.empty());
}

TEST(arrayCapacityTests, size) {
  s21::array<int, 10> ar = {47, 316, 454, 1322, 42, 913, 461, 342, 734, 642};
  std::array<int, 10> stdAr = {47, 316, 454, 1322, 42, 913, 461, 342, 734, 642};
  EXPECT_EQ(ar.size(), stdAr.size());
}

TEST(arrayCapacityTests, sizeEmpty) {
  s21::array<int, 0> ar;
  std::array<int, 0> stdAr;
  EXPECT_EQ(ar.size(), stdAr.size());
  EXPECT_EQ(ar.size(), size_t(0));
}

TEST(arrayCapacityTests, maxSize) {
  s21::array<int, 5> ar = {987, 342, 15, 97, 64};
  std::array<int, 5> stdAr = {987, 342, 15, 97, 64};
  EXPECT_EQ(ar.max_size(), size_t(5));
  EXPECT_EQ(stdAr.max_size(), size_t(5));
}

TEST(arrayCapacityTests, max_size_empty) {
  s21::array<int, 0> ar;
  std::array<int, 0> stdAr;
  EXPECT_EQ(ar.max_size(), size_t(0));
  EXPECT_EQ(stdAr.max_size(), size_t(0));
}

TEST(arrayModifiersTests, swap) {
  s21::array<int, 4> ar1 = {45, 65, 94, 121};
  s21::array<int, 4> ar2 = {69, 34, 91, 65};
  std::array<int, 4> stdAr1 = {45, 65, 94, 121};
  std::array<int, 4> stdAr2 = {69, 34, 91, 65};
  EXPECT_EQ(ar1.size(), stdAr1.size());
  EXPECT_EQ(ar1.size(), size_t(4));
  EXPECT_EQ(ar2.size(), stdAr2.size());
  EXPECT_EQ(ar2.size(), size_t(4));
  EXPECT_EQ(ar1.front(), 45);
  EXPECT_EQ(ar2.front(), 69);
  EXPECT_EQ(stdAr1.front(), 45);
  EXPECT_EQ(stdAr2.front(), 69);
  ar1.swap(ar2);
  stdAr1.swap(stdAr2);
  EXPECT_EQ(ar1.size(), stdAr1.size());
  EXPECT_EQ(ar1.size(), size_t(4));
  EXPECT_EQ(ar2.size(), stdAr2.size());
  EXPECT_EQ(ar2.size(), size_t(4));
  EXPECT_EQ(ar1.front(), 69);
  EXPECT_EQ(ar2.front(), 45);
  EXPECT_EQ(stdAr1.front(), 69);
  EXPECT_EQ(stdAr2.front(), 45);
}

TEST(arrayModifiersTests, fill) {
  using size_type = s21::array<int, 4>::size_type;
  s21::array<int, 3> ar = {65, 43, 32};
  std::array<int, 3> stdAr = {65, 43, 32};
  ar.fill(666);
  stdAr.fill(666);
  for (size_type i = 0; i < ar.size(); i++) {
    EXPECT_EQ(ar[i], 666);
    EXPECT_EQ(stdAr[i], 666);
  }
}

TEST(arrayModifiersTests, fillEmpty) {
  s21::array<int, 0> ar;
  std::array<int, 0> stdAr;
  ar.fill(333);
  stdAr.fill(333);

  EXPECT_TRUE(ar.empty());
  EXPECT_TRUE(stdAr.empty());
}