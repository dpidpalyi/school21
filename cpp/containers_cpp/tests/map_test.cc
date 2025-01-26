#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

#include "gtest/gtest.h"
#include "s21_containers/s21_map.h"

// explicit template class instantiation for correct code coverage analysis
template class s21::map<int, std::string>;
using pair = std::pair<int, std::string>;
using map = s21::map<int, std::string>;

// NOLINTBEGIN
class MapTest : public testing::Test {
 protected:
  int i_ = 0;
  s21::map<int, std::string> ism_ = {{1, "one"}, {2, "two"}, {3, "three"}};
};
// NOLINTEND

TEST_F(MapTest, CopyConstructor) {
  const s21::map<int, std::string> m(ism_);
  ASSERT_EQ(m, ism_);
}

TEST_F(MapTest, CopyAssignmentOperator) {
  s21::map<int, std::string> m;
  m = ism_;
  ASSERT_EQ(m, ism_);
}

TEST_F(MapTest, SelfCopyAssignmentOperator) {
  const s21::map<int, std::string> ref(ism_);
  s21::map<int, std::string> m(ism_);
  m = m;
  ASSERT_EQ(m, ref);
}

TEST_F(MapTest, MoveConstructor) {
  const s21::map<int, std::string> ref(ism_);
  const s21::map<int, std::string> m(std::move(ism_));
  ASSERT_EQ(m, ref);
}

TEST_F(MapTest, MoveAssignmentOperator) {
  const s21::map<int, std::string> ref(ism_);
  s21::map<int, std::string> m;
  m = std::move(ism_);
  ASSERT_EQ(m, ref);
}

TEST_F(MapTest, SelfMoveAssignmentOperator) {
  const s21::map<int, std::string> ref(ism_);
  s21::map<int, std::string> m(ism_);
  s21::map<int, std::string>* sp = &m;  // hide selfmove
  m = std::move(*sp);
  ASSERT_EQ(m, ref);
}

TEST_F(MapTest, FindMethod) {
  auto pos = ism_.find(1);
  EXPECT_EQ((*pos).second, "one");
  pos = ism_.find(0);
  EXPECT_EQ(pos, ism_.end());

  // const find
  const map ism = {{1, "one"}};
  auto cpos = ism.find(1);
  EXPECT_EQ((*cpos).second, "one");
}

TEST_F(MapTest, UniquenessProperty) {
  s21::map<int, std::string> ism = {{1, "one"}, {1, "two"}, {3, "three"}};
  ASSERT_EQ(ism.size(), 2);
  ism.insert(1, "four");
  ASSERT_EQ(ism.size(), 2);
  ism.erase(1);
  ASSERT_EQ(ism.size(), 1);
}

TEST_F(MapTest, InsertMethod) {  // NOLINT
  const bool is_exist = ism_.contains(4);

  auto [pos, res] = ism_.insert(4, "four");
  if (is_exist)
    EXPECT_EQ(res, false);
  else
    EXPECT_EQ(res, true);
  EXPECT_EQ((*pos).second, "four");

  std::tie(pos, res) = ism_.insert(1, "oneone");
  EXPECT_EQ(res, false);
  EXPECT_EQ((*pos).second, "one");

  std::tie(pos, res) = ism_.insert(0, "five");
  EXPECT_EQ(res, true);
  EXPECT_EQ((*pos).second, "five");
}

TEST_F(MapTest, EraseMethod) {
  ism_.insert(pair(4, "five"));
  const auto bsz = ism_.size();
  ism_.erase(4);
  EXPECT_EQ(ism_.size(), bsz - 1);

  ism_.insert(pair(4, "five"));
  EXPECT_EQ(ism_.size(), bsz);
  auto pos = ism_.find(4);
  ism_.erase(pos);
  EXPECT_EQ(ism_.size(), bsz - 1);
}

TEST_F(MapTest, InsertManyMethod) {
  map ism = {{1, "one"}, {2, "two"}, {3, "three"}};
  const pair a = {1, "two"}, b = {4, "four"}, c = {0, "five"};
  ism.insert_many(a, b, c);
  EXPECT_EQ(ism.size(), 5);
}

TEST_F(MapTest, InsertOrAssignMethod) {
  auto [pos, res] = ism_.insert_or_assign(4, "four");
  EXPECT_EQ(res, true);
  EXPECT_EQ((*pos).second, "four");

  std::tie(pos, res) = ism_.insert_or_assign(4, "five");
  EXPECT_EQ(res, false);
  EXPECT_EQ(ism_[4], "five");
}

TEST_F(MapTest, SubscriptOperator) {
  EXPECT_EQ(ism_[1], "one");
  EXPECT_EQ(ism_[2], "two");
  EXPECT_EQ(ism_[0], "");
  ism_[-1] = "mone";
  EXPECT_EQ(ism_[-1], "mone");
}

TEST_F(MapTest, AtMethod) {  // NOLINT
  EXPECT_EQ(ism_.at(1), "one");
  ism_.at(1) = "not one";
  EXPECT_EQ(ism_.at(1), "not one");
  EXPECT_EQ(ism_.at(2), "two");
  EXPECT_EQ(ism_.at(3), "three");
  ASSERT_THROW(ism_.at(4), std::out_of_range);  // NOLINT
  const auto ism(ism_);
  EXPECT_EQ(ism.at(1), "not one");
}

TEST_F(MapTest, MergeMethod) {
  s21::map<int, std::string> ism = {{1, "one"}, {0, "two"}, {-1, "three"}};
  ism_.merge(ism);
  EXPECT_EQ(ism_.size(), 5);
  EXPECT_EQ(ism.size(), 1);
  EXPECT_TRUE(ism.contains(1));
}

TEST_F(MapTest, SwapMethod) {
  s21::map<int, std::string> m;
  EXPECT_TRUE(m.empty());
  EXPECT_FALSE(ism_.empty());
  m.swap(ism_);
  EXPECT_FALSE(m.empty());
  EXPECT_TRUE(ism_.empty());
}

TEST_F(MapTest, ClearMethod) {
  EXPECT_FALSE(ism_.empty());
  ism_.clear();
  EXPECT_TRUE(ism_.empty());
}

TEST_F(MapTest, MaxSizeMethod) { std::clog << ism_.max_size() << '\n'; }

TEST_F(MapTest, EmptyInitializerListConstructor) {
  const s21::map<int, std::string> m({});
  EXPECT_TRUE(m.empty());
}

/* iterators */

TEST_F(MapTest, IteratorsInvocation) {  // NOLINT
  auto& m = ism_;                       // NOLINT
  EXPECT_EQ((*m.begin()).second, "one");
  EXPECT_EQ((*--m.end()).second, "three");
  EXPECT_EQ((*m.cbegin()).second, "one");
  EXPECT_EQ((*--m.cend()).second, "three");
  EXPECT_EQ((*m.rbegin()).second, "three");
  EXPECT_EQ((*--m.rend()).second, "one");
  EXPECT_EQ((*m.crbegin()).second, "three");
  EXPECT_EQ((*--m.crend()).second, "one");

  const s21::map<int, std::string> cs(m);
  EXPECT_EQ((*cs.begin()).second, "one");
  EXPECT_EQ((*--cs.end()).second, "three");
  EXPECT_EQ((*cs.rbegin()).second, "three");
  EXPECT_EQ((*--cs.rend()).second, "one");
}
