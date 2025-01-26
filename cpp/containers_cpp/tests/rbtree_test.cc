#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "gtest/gtest.h"
#include "s21_containers/detail/s21_rbtree.h"

// explicit template class instantiation for correct code coverage analysis
template class s21::search_tree<int>;
template class s21::search_tree<int, std::string>;
using itree = s21::search_tree<int>;

// NOLINTBEGIN
class SearchTreeTest : public testing::Test {
 protected:
  void SetUp() override {
    auto il_ = {4, 7, 12, 15, 3, 5, 14, 18, 16, 17, -1};
    iv_ = il_;
    sort(iv_.begin(), iv_.end());
    it_ = il_;
  }

  int i_ = 0;
  std::vector<int> iv_;
  s21::search_tree<int> it_;
  s21::search_tree<int, std::string> ist_ = {
      {1, "one"}, {2, "two"}, {3, "four"}};
};
// NOLINTEND

TEST_F(SearchTreeTest, InitializerListConstructor) {
  const s21::search_tree<int> it = {1, 2, 3};
  EXPECT_EQ(it.size(), 3);
  const s21::search_tree<int, std::string> ist = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(ist.size(), 3);
}

TEST_F(SearchTreeTest, EquivalenceOperators) {  // NOLINT
  const s21::search_tree<int> it1 = {1, 3, 4};
  const s21::search_tree<int> it2 = {1, 3, 4};
  ASSERT_TRUE(it1 == it1);
  ASSERT_TRUE(it1 == it2);
  const s21::search_tree<int> it3 = {1, 3, 3};
  ASSERT_TRUE(it1 != it3);
  const s21::search_tree<int> it4 = {1, 3};
  ASSERT_TRUE(it1 != it4);

  const s21::search_tree<int, std::string> ist1 = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  const s21::search_tree<int, std::string> ist2 = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  ASSERT_TRUE(ist1 == ist1);
  ASSERT_TRUE(ist1 == ist2);
  const s21::search_tree<int, std::string> ist3 = {
      {1, "one"}, {2, "two"}, {3, "four"}};
  ASSERT_TRUE(ist1 != ist3);
  const s21::search_tree<int, std::string> ist4 = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
  ASSERT_TRUE(ist1 != ist4);
}

TEST_F(SearchTreeTest, CopyConstructor) {
  const s21::search_tree<int> it(it_);
  ASSERT_EQ(it, it_);

  const s21::search_tree<int, std::string> ist(ist_);
  ASSERT_EQ(ist, ist_);
}

TEST_F(SearchTreeTest, MoveConstructor) {
  const s21::search_tree<int> ref(it_);
  const s21::search_tree<int> it(std::move(it_));
  ASSERT_EQ(it, ref);
  ASSERT_TRUE(it_.empty());

  const s21::search_tree<int, std::string> ref2(ist_);
  const s21::search_tree<int, std::string> ist(std::move(ist_));
  ASSERT_EQ(ist, ref2);
  ASSERT_TRUE(ist_.empty());
}

TEST_F(SearchTreeTest, CopyAssignment) {
  s21::search_tree<int> it;
  it = it_;
  ASSERT_EQ(it, it_);

  s21::search_tree<int, std::string> ist;
  ist = ist_;
  ASSERT_EQ(ist, ist_);
}

TEST_F(SearchTreeTest, MoveAssignment) {
  const s21::search_tree<int> ref(it_);
  s21::search_tree<int> it;
  it = std::move(it_);
  ASSERT_EQ(it, ref);
  ASSERT_TRUE(it_.empty());

  const s21::search_tree<int, std::string> ref2(ist_);
  s21::search_tree<int, std::string> ist;
  ist = std::move(ist_);
  ASSERT_EQ(ist, ref2);
  ASSERT_TRUE(ist_.empty());
}

TEST_F(SearchTreeTest, ClearMethod) {
  EXPECT_FALSE(it_.empty());
  it_.clear();
  EXPECT_TRUE(it_.empty());

  EXPECT_FALSE(ist_.empty());
  ist_.clear();
  EXPECT_TRUE(ist_.empty());
}

TEST_F(SearchTreeTest, EmptyMethod) {
  EXPECT_FALSE(it_.empty());
  it_.clear();
  EXPECT_TRUE(it_.empty());
  EXPECT_EQ(it_.size(), 0);

  EXPECT_FALSE(ist_.empty());
  ist_.clear();
  EXPECT_TRUE(ist_.empty());
  EXPECT_EQ(ist_.size(), 0);
}

TEST_F(SearchTreeTest, IsEmptyInitially) {
  const s21::search_tree<int> it;
  EXPECT_EQ(it.size(), 0);
  EXPECT_TRUE(it.empty());

  const s21::search_tree<int, std::string> ist;
  EXPECT_EQ(ist.size(), 0);
  EXPECT_TRUE(ist.empty());
}

TEST_F(SearchTreeTest, ProperOrderDemonstration) {
  auto il = {4, 7, 12, 15, 3, 5, 14, 18, 16, 17};  // NOLINT
  std::vector<int> vec = il;
  sort(vec.begin(), vec.end());

  s21::search_tree<int> tree = il;
  ASSERT_EQ(tree.size(), vec.size());

  int i = 0;
  for (auto iter = tree.begin(); iter != tree.end(); ++iter, ++i) {
    ASSERT_EQ(*iter, vec[i]);
  }

  // NOLINTBEGIN
  tree.erase(3);
  tree.erase(12);
  tree.erase(12);
  tree.erase(17);
  tree.erase(18);
  tree.erase(15);
  tree.erase(16);
  // NOLINTEND

  tree.clear();
  EXPECT_EQ(tree.size(), 0);
  EXPECT_EQ(tree.empty(), true);
}

TEST_F(SearchTreeTest, EraseAllMethod) {
  itree t = {1, 1, 1, 4, 4, 3};
  EXPECT_EQ(t.count(1), 3);
  t.erase_all(1);
  EXPECT_EQ(t.count(1), 0);
}

TEST_F(SearchTreeTest, InsertIfNeMethod) {
  itree t = {1, 1, 1, 4, 4, 3};
  EXPECT_EQ(t.count(1), 3);
  t.insert_if_ne(1);
  EXPECT_EQ(t.count(1), 3);
  t.insert_if_ne(2);
  EXPECT_EQ(t.count(2), 1);
}

TEST_F(SearchTreeTest, MergeIfNeMethod) {
  itree t1 = {1, 1, 1, 4, 4, 3};
  itree t2 = {1, 1, 1, 2, 0, 3};
  t1.merge_if_ne(t2);
  EXPECT_EQ(t1.size(), 8);
  EXPECT_EQ(t2.size(), 4);
}

TEST_F(SearchTreeTest, AtMethod) {  // NOLINT
  s21::search_tree<int, std::string> t = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(t.at(1), "one");
  t.at(1) = "not one";
  EXPECT_EQ(t.at(1), "not one");
  EXPECT_EQ(t.at(2), "two");
  EXPECT_EQ(t.at(3), "three");
  ASSERT_THROW(t.at(4), std::out_of_range);  // NOLINT
}

TEST_F(SearchTreeTest, SubscriptOperator) {
  s21::search_tree<int, std::string> t = {{1, "one"}, {2, "two"}, {3, "three"}};
  // NOLINTBEGIN
  EXPECT_EQ(t[1], "one");
  EXPECT_EQ(t[2], "two");
  EXPECT_EQ(t[3], "three");
  EXPECT_EQ(t[4], "");
  EXPECT_EQ(t[5], "");
  t[5] = "five";
  EXPECT_EQ(t[5], "five");
  // NOLINTEND
}

TEST_F(SearchTreeTest, InsertManyMethod) {
  itree it = {1, 2, 4};
  EXPECT_EQ(it.size(), 3);
  it.insert_many(1, 2, 4, 0, -1);
  EXPECT_EQ(it.size(), 8);
}

TEST_F(SearchTreeTest, InsertIfNeManyMethod) {
  itree it = {1, 2, 4};
  EXPECT_EQ(it.size(), 3);
  it.insert_if_ne_many(1, 2, 4, 0, -1);
  EXPECT_EQ(it.size(), 5);
}

TEST_F(SearchTreeTest, InsertOrAssignMethod) {
  s21::search_tree<int, std::string> t = {{1, "one"}, {2, "two"}, {3, "three"}};

  auto [pos, res] = t.insert_or_assign(4, std::string("four"));
  EXPECT_EQ(res, true);
  EXPECT_EQ((*pos).second, "four");

  std::tie(pos, res) = t.insert_or_assign(4, std::string("five"));
  EXPECT_EQ(res, false);
  EXPECT_EQ(t[4], "five");
}

TEST_F(SearchTreeTest, InsertIfNe2params) {
  s21::search_tree<int, std::string> t = {{1, "one"}, {2, "two"}, {3, "three"}};

  auto [pos, res] = t.insert_if_ne(4, std::string("four"));
  EXPECT_EQ(res, true);
  EXPECT_EQ((*pos).second, "four");

  std::tie(pos, res) = t.insert_if_ne(4, std::string("five"));
  EXPECT_EQ(res, false);
  EXPECT_EQ(t[4], "four");
}

TEST_F(SearchTreeTest, BoundMethods) {  // NOLINT
  s21::search_tree<int, std::string> t = {
      {1, "one"}, {2, "two"}, {2, "two"}, {2, "two"}, {3, "three"}};

  ASSERT_EQ(t.count(2), 3);

  auto posl = t.lower_bound(2);
  using value_type = s21::search_tree<int, std::string>::value_type;
  ASSERT_EQ(*posl, value_type(2, "two"));
  ASSERT_EQ((*posl).first, 2);
  ASSERT_EQ((*posl).second, "two");

  auto posu = t.upper_bound(2);
  ASSERT_EQ(*posu, value_type(3, "three"));

  auto [eql, equ] = t.equal_range(2);
  EXPECT_EQ(posl, eql);
  EXPECT_EQ(posu, equ);

  posu--;
  ASSERT_EQ(*posu, value_type(2, "two"));
}

TEST_F(SearchTreeTest, PrintMethod) {
  const s21::search_tree<int, std::string> t = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  std::clog << t;
  std::clog << t.max_size() << '\n';
  s21::search_tree<int> t2 = {5, 1, 6, 1234, 65, 1, 54, 0};  // NOLINT
  std::clog << t2;
  std::clog << t2.max_size() << '\n';
}

TEST_F(SearchTreeTest, MergeMethod) {
  s21::search_tree<int> t = {1, 2, 3};   // NOLINT
  s21::search_tree<int> t2 = {3, 4, 5};  // NOLINT
  t.merge(t2);
  t.merge(t2);
  EXPECT_EQ(t.size(), 6);
  EXPECT_EQ(t2.size(), 0);
  s21::search_tree<int> t3;
  t.merge(t3);
  EXPECT_EQ(t.size(), 6);
  EXPECT_EQ(t3.size(), 0);
}

int rand_i(unsigned i) {
  // NOLINTBEGIN
  i = (i << 13) ^ i;
  return ((i * (i * i * 15731 + 789221) + 1376312589) & 0x7fffffff);
  // NOLINTEND
}
TEST_F(SearchTreeTest, LargeOrderingTest) {
  std::vector<int> v;
  s21::search_tree<int> s;
  const int n = 1000;
  for (int i = 0; i < n; i++) {  // NOLINT
    const int rand = rand_i(i);
    v.push_back(rand);
    s.insert(rand);
  }

  // proper order after insertion
  sort(v.begin(), v.end());
  int i = 0;
  for (const auto& elem : s) {
    ASSERT_EQ(elem, v[i]);
    ++i;
  }

  // shuffle vector to remove elements in a random order
  auto rd = std::random_device{};
  auto rng = std::default_random_engine{rd()};
  std::shuffle(std::begin(v), std::end(v), rng);

  for (int i = 0; i < n * 0.7; i++) {  // NOLINT
    const int rem = v.back();
    v.pop_back();
    s.erase(rem);
  }

  // proper order after removing
  sort(v.begin(), v.end());
  i = 0;
  for (const auto& elem : s) {
    ASSERT_EQ(elem, v[i]);
    ++i;
  }
}

/* iterators */

TEST_F(SearchTreeTest, IteratorComparisonsWithDifferentConstness) {
  s21::search_tree<int> t = {1, 2, 3};  // NOLINT
  EXPECT_TRUE(t.begin() == t.cbegin());
  EXPECT_TRUE(t.begin() != t.cend());
}

TEST_F(SearchTreeTest, MutableIteration) {
  for (auto iter = it_.begin(); iter != it_.end(); ++iter, ++i_) {
    ASSERT_EQ(*iter, iv_[i_]);
  }
  auto iter = it_.begin();  // NOLINT
  EXPECT_FALSE(std::is_const_v<std::remove_reference_t<decltype(*iter)>>);
}
TEST_F(SearchTreeTest, ReverseMutableIteration) {
  std::reverse(iv_.begin(), iv_.end());
  for (auto iter = it_.rbegin(); iter != it_.rend(); ++iter, ++i_) {
    ASSERT_EQ(*iter, iv_[i_]);
  }
  auto iter = it_.rbegin();  // NOLINT
  EXPECT_FALSE(std::is_const_v<std::remove_reference_t<decltype(*iter)>>);
}

TEST_F(SearchTreeTest, NonMutableIteration) {
  for (auto iter = it_.cbegin(); iter != it_.cend(); ++iter, ++i_) {
    ASSERT_EQ(*iter, iv_[i_]);
  }
  auto iter = it_.cbegin();  // NOLINT
  EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(*iter)>>);
}
TEST_F(SearchTreeTest, ReverseNonMutableIteration) {
  std::reverse(iv_.begin(), iv_.end());
  for (auto iter = it_.crbegin(); iter != it_.crend(); ++iter, ++i_) {
    ASSERT_EQ(*iter, iv_[i_]);
  }
  auto iter = it_.crbegin();  // NOLINT
  EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(*iter)>>);
}

TEST_F(SearchTreeTest, NonMutableIterationConst) {
  const s21::search_tree<int> cit = it_;
  for (auto iter = cit.begin(); iter != cit.end(); ++iter, ++i_) {
    ASSERT_EQ(*iter, iv_[i_]);
  }
  auto iter = cit.begin();  // NOLINT
  EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(*iter)>>);
}
TEST_F(SearchTreeTest, ReverseNonMutableIterationConst) {
  std::reverse(iv_.begin(), iv_.end());
  const s21::search_tree<int> cit = it_;
  for (auto iter = cit.rbegin(); iter != cit.rend(); ++iter, ++i_) {
    ASSERT_EQ(*iter, iv_[i_]);
  }
  auto iter = cit.rbegin();  // NOLINT
  EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(*iter)>>);
}

TEST_F(SearchTreeTest, IteratorDemonstration) {  // NOLINT
  s21::search_tree<int> t = {1, 2, 3};

  auto iter = t.begin();
  ASSERT_EQ(*iter, 1);
  iter++;
  ASSERT_EQ(*iter, 2);
  iter--;
  ASSERT_EQ(*iter, 1);
  ++iter;
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(iter, t.end());

  auto riter = t.rbegin();
  ASSERT_EQ(*riter, 3);
  riter++;
  ASSERT_EQ(*riter, 2);
  --riter;
  ++riter;
  ASSERT_EQ(*riter, 2);
  ++riter;
  ASSERT_EQ(*riter, 1);
  ++riter;
  ASSERT_EQ(riter, t.rend());
}

/* special cases */

TEST_F(SearchTreeTest, BeginOnEmptyTree) {
  itree t;  // NOLINT
  EXPECT_EQ(t.begin(), t.end());
  const itree ct;
  EXPECT_EQ(ct.begin(), ct.end());
}

TEST_F(SearchTreeTest, FindOnEmptyTree) {
  const itree t;
  EXPECT_EQ(t.find(1), t.end());
}

TEST_F(SearchTreeTest, PrintOnEmptyTree) {
  const itree t;
  std::clog << t << '\n';
  EXPECT_TRUE(t.empty());
}

TEST_F(SearchTreeTest, BoundsOnEmptyTree) {
  itree t;
  auto lb = t.lower_bound(1);
  auto ub = t.upper_bound(1);
  auto er = t.equal_range(1);
  ASSERT_EQ(lb, t.end());
  ASSERT_EQ(ub, t.end());
  ASSERT_EQ(er.first, t.end());
  ASSERT_EQ(er.second, t.end());
}

TEST_F(SearchTreeTest, BoundsOnSingleEntry) {
  itree t = {1};
  auto lb = t.lower_bound(1);
  auto ub = t.upper_bound(1);
  auto er = t.equal_range(1);
  ASSERT_EQ(lb, er.first);
  ASSERT_EQ(lb, t.begin());
  ASSERT_EQ(ub, er.second);
  ASSERT_EQ(ub, t.end());
  ASSERT_EQ(*lb, 1);
}

TEST_F(SearchTreeTest, CountOnEmptyTree) {
  const itree t;
  EXPECT_EQ(t.count(1), 0);
}

TEST_F(SearchTreeTest, ContainsOnEmptyTree) {
  const itree t;
  EXPECT_EQ(t.contains(1), false);
}
