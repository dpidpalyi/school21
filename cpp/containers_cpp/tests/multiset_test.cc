
#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>
#include <utility>
#include <vector>

#include "gtest/gtest.h"
#include "s21_containers/s21_multiset.h"

// explicit template class instantiation for correct code coverage analysis
template class s21::multiset<int>;

// NOLINTBEGIN
class MultisetTest : public testing::Test {
 protected:
  void SetUp() override {
    auto il_ = {4, 7, 12, 15, 3, 5, 14, 18, 16, 17, -1};  // NOLINT
    iv_ = il_;
    sort(iv_.begin(), iv_.end());
    ims_ = il_;
  }

  std::vector<int> iv_;
  s21::multiset<int> ims_;
  int i_ = 0;
};
// NOLINTEND

TEST_F(MultisetTest, EquivalenceOperators) {
  const s21::multiset<int> s = {1, 2, 3};
  ASSERT_TRUE(s == s);
  ASSERT_FALSE(s != s);
  const s21::multiset<int> s2 = {1, 2};
  ASSERT_TRUE(s != s2);
  ASSERT_FALSE(s == s2);
  const s21::multiset<int> s3 = {1, 2, 3, 3};
  ASSERT_TRUE(s != s3);
}

TEST_F(MultisetTest, CopyConstructor) {
  const s21::multiset<int> s(ims_);
  ASSERT_EQ(s, ims_);
}

TEST_F(MultisetTest, CopyAssignmentOperator) {
  s21::multiset<int> s;
  s = ims_;
  ASSERT_EQ(s, ims_);
}

TEST_F(MultisetTest, SelfCopyAssignmentOperator) {
  const s21::multiset<int> ref(ims_);
  s21::multiset<int> s(ims_);
  s = s;
  ASSERT_EQ(s, ref);
}

TEST_F(MultisetTest, MoveConstructor) {
  const s21::multiset<int> ref(ims_);
  const s21::multiset<int> s(std::move(ims_));
  ASSERT_EQ(s, ref);
}

TEST_F(MultisetTest, MoveAssignmentOperator) {
  const s21::multiset<int> ref(ims_);
  s21::multiset<int> s;
  s = std::move(ims_);
  ASSERT_EQ(s, ref);
}

TEST_F(MultisetTest, SelfMoveAssignmentOperator) {
  const s21::multiset<int> ref(ims_);
  s21::multiset<int> s(ims_);
  s21::multiset<int>* sp = &s;  // hide selfmove
  s = std::move(*sp);
  ASSERT_EQ(s, ref);
}

TEST_F(MultisetTest, FindMethod) {
  const s21::multiset<int> cims = {1, 2, 3};
  auto pos = cims.find(1);
  EXPECT_EQ(*pos, 1);
  pos = cims.find(0);
  EXPECT_EQ(pos, cims.end());
}

TEST_F(MultisetTest, InsertPolicy) {
  s21::multiset<int> ims = {1, 1, 2, 3, 4};
  ASSERT_EQ(ims.size(), 5);
  ims.insert(3);
  ASSERT_EQ(ims.size(), 6);
  ims.erase(1);
  ASSERT_EQ(ims.size(), 4);
  ims.insert_many(1, 1);
  auto pos = ims.find(1);
  ims.erase(pos);
  ASSERT_TRUE(ims.contains(1));
  ASSERT_EQ(ims.size(), 5);

  const s21::multiset<int> ims2 = {1, 1, 1};
  ASSERT_EQ(ims2.size(), 3);
}

TEST_F(MultisetTest, InsertMethod) {  // NOLINT
  auto pos = ims_.insert(4);
  EXPECT_EQ(*pos, 4);

  pos = ims_.insert(4);
  EXPECT_EQ(*pos, 4);
  EXPECT_EQ(*--pos, 4);

  const int imax = std::numeric_limits<int>::max();
  pos = ims_.insert(imax);
  EXPECT_EQ(*pos, imax);
}

TEST_F(MultisetTest, EraseMethod) {
  ims_.insert(4);
  auto bsz = ims_.size();
  auto count = ims_.count(4);
  ims_.erase(4);
  EXPECT_EQ(ims_.size(), bsz - count);
}

TEST_F(MultisetTest, InsertManyMethod) {
  s21::multiset<int> ims = {1, 2, 3};
  ims.insert_many(1, 2, 3, 4);
  EXPECT_EQ(ims.size(), 7);
}

TEST_F(MultisetTest, MergeMethod) {
  s21::multiset<int> s1 = {1, 3};
  s21::multiset<int> s2 = {-1, 3, 2, 5, 6};  // NOLINT

  s1.merge(s2);
  EXPECT_EQ(s1.size(), 7);
  EXPECT_EQ(s2.size(), 0);
}

TEST_F(MultisetTest, SwapMethod) {
  s21::multiset<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(ims_.empty());
  s.swap(ims_);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(ims_.empty());
}

TEST_F(MultisetTest, ClearMethod) {
  EXPECT_FALSE(ims_.empty());
  ims_.clear();
  EXPECT_TRUE(ims_.empty());
}

TEST_F(MultisetTest, MaxSizeMethod) { std::clog << ims_.max_size() << '\n'; }

TEST_F(MultisetTest, BoundMethods) {
  s21::multiset<int> ims = {1, 2, 3, 4, 0, 0, 0, -1};
  auto lb = ims.lower_bound(0);
  auto ub = ims.upper_bound(0);
  auto er = ims.equal_range(0);
  EXPECT_EQ(*lb, 0);
  EXPECT_EQ(*ub, 1);
  EXPECT_EQ(*--ub, 0);
  ++ub;
  EXPECT_EQ(er.first, lb);
  EXPECT_EQ(er.second, ub);
}

/* iterators */

TEST_F(MultisetTest, IteratorsInvocation) {  // NOLINT
  s21::multiset<int> s = {1, 2, 3};          // NOLINT
  EXPECT_EQ(*s.begin(), 1);
  EXPECT_EQ(*--s.end(), 3);
  EXPECT_EQ(*s.cbegin(), 1);
  EXPECT_EQ(*--s.cend(), 3);
  EXPECT_EQ(*s.rbegin(), 3);
  EXPECT_EQ(*--s.rend(), 1);
  EXPECT_EQ(*s.crbegin(), 3);
  EXPECT_EQ(*--s.crend(), 1);

  const s21::multiset<int> cs(s);
  EXPECT_EQ(*cs.begin(), 1);
  EXPECT_EQ(*--cs.end(), 3);
  EXPECT_EQ(*cs.rbegin(), 3);
  EXPECT_EQ(*--cs.rend(), 1);
}
