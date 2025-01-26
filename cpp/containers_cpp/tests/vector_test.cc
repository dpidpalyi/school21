
#include "gtest/gtest.h"
#include "s21_containers/s21_vector.h"

template class s21::vector<int>;

class VectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_empty_ = s21::vector<int>();
    vec_size_5_ = s21::vector<int>(5);
    vec_init_list_ = s21::vector<int>{1, 2, 3, 4, 5};
  }

  s21::vector<int> vec_empty_;
  s21::vector<int> vec_size_5_;
  s21::vector<int> vec_init_list_;
};

TEST_F(VectorTest, DefaultConstructor) {
  EXPECT_EQ(vec_empty_.size(), 0);
  EXPECT_EQ(vec_empty_.capacity(), 0);
  EXPECT_EQ(vec_empty_.empty(), true);
}

TEST_F(VectorTest, SizeConstructor) {
  EXPECT_EQ(vec_size_5_.size(), 5);
  EXPECT_EQ(vec_size_5_.capacity(), 5);
  EXPECT_EQ(vec_size_5_.empty(), false);
}

TEST_F(VectorTest, InitializerListConstructor) {
  EXPECT_EQ(vec_init_list_.size(), 5);
  EXPECT_EQ(vec_init_list_.capacity(), 5);
  EXPECT_EQ(vec_init_list_.empty(), false);
  EXPECT_EQ(vec_init_list_[2], 3);
  EXPECT_EQ(vec_init_list_.front(), 1);
  EXPECT_EQ(vec_init_list_.back(), 5);
}

TEST_F(VectorTest, CopyConstructor) {
  s21::vector<int> original{1, 2, 3, 4, 5};
  s21::vector<int> copy(original);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy[1], 2);
  EXPECT_EQ(copy[2], 3);
  EXPECT_EQ(copy[3], 4);
  EXPECT_EQ(copy[4], 5);

  original[0] = 10;
  EXPECT_EQ(copy[0], 1);
}

TEST_F(VectorTest, MoveConstructor) {
  s21::vector<int> original{1, 2, 3, 4, 5};
  s21::vector<int> moved(std::move(original));
  EXPECT_EQ(moved[0], 1);
  EXPECT_EQ(moved[1], 2);
  EXPECT_EQ(moved[2], 3);
  EXPECT_EQ(moved[3], 4);
  EXPECT_EQ(moved[4], 5);

  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(original.capacity(), 0);
  EXPECT_EQ(original.data(), nullptr);
}

TEST_F(VectorTest, AssignmentOperator) {
  s21::vector<int> vec1{1, 2, 3};
  s21::vector<int> vec2;
  vec2 = vec1;

  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2.capacity(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);

  vec1 = vec1;

  EXPECT_EQ(vec1.size(), 3);
  EXPECT_EQ(vec1.capacity(), 3);
  EXPECT_EQ(vec1[0], 1);
  EXPECT_EQ(vec1[1], 2);
  EXPECT_EQ(vec1[2], 3);

  s21::vector<int> vec3;
  vec2 = vec3;

  EXPECT_EQ(vec2.size(), 0);
  EXPECT_EQ(vec2.capacity(), 0);
  EXPECT_EQ(vec2.empty(), true);

  vec3 = vec1;

  EXPECT_EQ(vec3.size(), 3);
  EXPECT_EQ(vec3.capacity(), 3);
  EXPECT_EQ(vec3[0], 1);
  EXPECT_EQ(vec3[1], 2);
  EXPECT_EQ(vec3[2], 3);
}

TEST_F(VectorTest, ConstAccessMethods) {
  const s21::vector<int> constVec{1, 2, 3, 4, 5};
  EXPECT_EQ(constVec.at(2), 3);
  EXPECT_THROW(constVec.at(10), std::out_of_range);

  EXPECT_EQ(constVec[2], 3);
  EXPECT_THROW(constVec[10], std::out_of_range);

  EXPECT_EQ(constVec.front(), 1);

  EXPECT_EQ(constVec.back(), 5);

  const int* constData = constVec.data();
  EXPECT_EQ(constData[2], 3);
}

TEST_F(VectorTest, AtMethod) {
  EXPECT_EQ(vec_init_list_.at(2), 3);

  EXPECT_THROW(vec_empty_.at(0), std::out_of_range);
}

TEST_F(VectorTest, SquareBracketOperator) {
  vec_size_5_[2] = 3;
  EXPECT_EQ(vec_size_5_[2], 3);
}

TEST_F(VectorTest, FrontMethod) {
  EXPECT_EQ(vec_init_list_.front(), 1);

  EXPECT_THROW(vec_empty_.front(), std::out_of_range);
}

TEST_F(VectorTest, BackMethod) {
  vec_size_5_.push_back(7);
  EXPECT_EQ(vec_size_5_.back(), 7);

  EXPECT_THROW(vec_empty_.back(), std::out_of_range);
}

TEST_F(VectorTest, DataMethod) {
  EXPECT_EQ(vec_size_5_.data(), &vec_size_5_[0]);

  EXPECT_EQ(vec_empty_.data(), nullptr);
}

TEST_F(VectorTest, BeginEndMethods) {
  auto it_begin = vec_init_list_.begin();
  auto it_end = vec_init_list_.end();

  EXPECT_EQ(*it_begin, 1);
  EXPECT_EQ(*(it_end - 1), 5);

  const s21::vector<int>& const_vec = vec_init_list_;
  auto it_cbegin = const_vec.cbegin();
  auto it_cend = const_vec.cend();

  EXPECT_EQ(*it_cbegin, 1);
  EXPECT_EQ(*(it_cend - 1), 5);
}
TEST_F(VectorTest, EmptyMethod) {
  EXPECT_EQ(vec_init_list_.empty(), false);

  EXPECT_EQ(vec_empty_.empty(), true);
}

TEST_F(VectorTest, SizeMethod) {
  EXPECT_EQ(vec_size_5_.size(), 5);

  EXPECT_EQ(vec_empty_.size(), 0);
}

TEST_F(VectorTest, MaxSizeMethod) {
  EXPECT_EQ(vec_init_list_.max_size(),
            std::numeric_limits<typename s21::vector<int>::size_type>::max());
}

TEST_F(VectorTest, ReserveMethod) {
  vec_empty_.reserve(10);
  EXPECT_EQ(vec_empty_.capacity(), 10);
  EXPECT_EQ(vec_empty_.size(), 0);
}

TEST_F(VectorTest, CapacityMethod) { EXPECT_EQ(vec_size_5_.capacity(), 5); }

TEST_F(VectorTest, ShrinkToFitMethod) {
  vec_size_5_.reserve(10);
  vec_size_5_.shrink_to_fit();
  EXPECT_EQ(vec_size_5_.capacity(), vec_size_5_.size());

  vec_empty_.shrink_to_fit();
  EXPECT_EQ(vec_empty_.capacity(), 0);
}

TEST_F(VectorTest, ClearMethod) {
  vec_size_5_.clear();
  EXPECT_EQ(vec_size_5_.size(), 0);
  EXPECT_EQ(vec_size_5_.capacity(), 0);
  EXPECT_EQ(vec_size_5_.empty(), true);

  vec_empty_.clear();
  EXPECT_EQ(vec_empty_.size(), 0);
  EXPECT_EQ(vec_empty_.capacity(), 0);
  EXPECT_EQ(vec_empty_.empty(), true);
}

TEST_F(VectorTest, InsertIntoMiddle) {
  auto it_inserted = vec_init_list_.insert(vec_init_list_.begin() + 2, 10);
  EXPECT_EQ(*it_inserted, 10);
  EXPECT_EQ(vec_init_list_.size(), 6);

  EXPECT_EQ(vec_init_list_[0], 1);
  EXPECT_EQ(vec_init_list_[1], 2);
  EXPECT_EQ(vec_init_list_[2], 10);
  EXPECT_EQ(vec_init_list_[3], 3);
  EXPECT_EQ(vec_init_list_[4], 4);
  EXPECT_EQ(vec_init_list_[5], 5);
}

TEST_F(VectorTest, InsertIntoBeginning) {
  auto it_inserted = vec_init_list_.insert(vec_init_list_.begin(), 0);
  EXPECT_EQ(*it_inserted, 0);
  EXPECT_EQ(vec_init_list_.size(), 6);

  EXPECT_EQ(vec_init_list_[0], 0);
  EXPECT_EQ(vec_init_list_[1], 1);
  EXPECT_EQ(vec_init_list_[2], 2);
  EXPECT_EQ(vec_init_list_[3], 3);
  EXPECT_EQ(vec_init_list_[4], 4);
  EXPECT_EQ(vec_init_list_[5], 5);
}

TEST_F(VectorTest, InsertOutOfRange) {
  EXPECT_THROW(vec_init_list_.insert(vec_init_list_.begin() + 8, 42),
               std::out_of_range);
}

TEST_F(VectorTest, InsertIntoEmpty) {
  auto it_inserted = vec_empty_.insert(vec_empty_.begin(), 42);
  EXPECT_EQ(*it_inserted, 42);
  EXPECT_EQ(vec_empty_.size(), 1);

  EXPECT_EQ(vec_empty_[0], 42);
}

TEST_F(VectorTest, EraseMethod) {
  s21::vector<int> vec_values{1, 2, 3, 4, 5};

  vec_values.erase(vec_values.begin() + 2);
  EXPECT_EQ(vec_values[0], 1);
  EXPECT_EQ(vec_values[1], 2);
  EXPECT_EQ(vec_values[2], 4);
  EXPECT_EQ(vec_values[3], 5);

  EXPECT_THROW(vec_empty_.erase(vec_empty_.begin()), std::out_of_range);
}

TEST_F(VectorTest, PushBackMethods) {
  vec_empty_.push_back(7);
  EXPECT_EQ(vec_empty_.size(), 1);
  EXPECT_EQ(vec_empty_[0], 7);

  vec_empty_.push_back(std::move(8));
  EXPECT_EQ(vec_empty_.size(), 2);
  EXPECT_EQ(vec_empty_[1], 8);
}

TEST_F(VectorTest, ConstPushBack) {
  const int value = 42;

  const s21::vector<int> constVec{1, 2, 3, 4, 5};
  s21::vector<int> modifiedVec = constVec;
  modifiedVec.push_back(value);

  EXPECT_EQ(modifiedVec.size(), constVec.size() + 1);
  EXPECT_EQ(modifiedVec.back(), value);

  EXPECT_EQ(constVec.size(), 5);
  EXPECT_NE(constVec.back(), value);
}

TEST_F(VectorTest, PopBackMethod) {
  vec_init_list_.pop_back();
  EXPECT_EQ(vec_init_list_.size(), 4);
  vec_empty_.pop_back();
  EXPECT_EQ(vec_empty_.size(), 0);
}

TEST_F(VectorTest, SwapMethod) {
  s21::vector<int> vec_swap{9, 10, 11};
  vec_init_list_.swap(vec_swap);
  EXPECT_EQ(vec_init_list_.size(), 3);
  EXPECT_EQ(vec_swap.size(), 5);
  EXPECT_EQ(vec_init_list_[1], 10);
  EXPECT_EQ(vec_swap[2], 3);
}

TEST_F(VectorTest, InsertManyMethod) {
  s21::vector<int> vec_1{9, 10, 11};
  vec_1.insert_many(vec_1.begin(), 0, -1, -2);

  ASSERT_EQ(vec_1.size(), 6);

  int expected_values[] = {0, -1, -2, 9, 10, 11};
  int i = 0;
  for (auto iter = vec_1.begin(); iter != vec_1.end(); ++iter, ++i) {
    ASSERT_EQ(*iter, expected_values[i]);
  }
}

TEST_F(VectorTest, InsertManyBackMethod) {
  s21::vector<int> vec_1{9, 10, 11};
  vec_1.insert_many_back(12, 13, 14, 15);

  ASSERT_EQ(vec_1.size(), 7);

  int expected_values[] = {9, 10, 11, 12, 13, 14, 15};
  int i = 0;
  for (auto iter = vec_1.begin(); iter != vec_1.end(); ++iter, ++i) {
    ASSERT_EQ(*iter, expected_values[i]);
  }
}
