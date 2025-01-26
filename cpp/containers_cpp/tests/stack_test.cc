#include <stack>
#include <string>

#include "gtest/gtest.h"
#include "s21_containers/s21_stack.h"

// explicit template class instantiation for the needs of code coverage
template class s21::stack<int>;
template class s21::stack<std::string>;

TEST(StackCtor, Default) {
  const int sz = 0;
  s21::stack<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(StackCtor, InitializerStack1) {
  const int sz = 0;
  s21::stack<int> l{};
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(StackCtor, InitializerStack2) {
  const int sz = 1;
  const int f = 10;
  s21::stack<int> l{10};
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(l.top(), f);
}

TEST(StackCtor, InitializerStack3) {
  const int sz = 5;
  const int t = 5;
  s21::stack<int> l{1, 2, 3, 4, 5};
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(l.top(), t);
}

TEST(StackCtor, Copy1) {
  const int sz = 0;
  s21::stack<int> l1;
  s21::stack<int> l2(l1);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
}

TEST(StackCtor, Copy2) {
  const int sz = 1;
  const int f = 10;
  s21::stack<int> l1{f};
  s21::stack<int> l2(l1);
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.top(), f);
}

TEST(StackCtor, Copy3) {
  const int sz = 3;
  const int t = 3;
  s21::stack<int> l1{1, 2, 3};
  s21::stack<int> l2(l1);
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.top(), t);
}

TEST(StackCtor, Move1) {
  const int sz = 0;
  s21::stack<int> l1;
  s21::stack<int> l2(std::move(l1));
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
}

TEST(StackCtor, Move2) {
  const int sz = 1;
  const int f = 10;
  s21::stack<int> l1{f};
  s21::stack<int> l2(std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.top(), f);
}

TEST(StackCtor, Move3) {
  const int sz = 3;
  const int t = 3;
  s21::stack<int> l1{1, 2, 3};
  s21::stack<int> l2(std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(l2.top(), t);
}

TEST(StackAssignment, CopyAssign1) {
  const int sz = 0;
  s21::stack<int> l1;
  s21::stack<int> l2;
  l2 = l1;
  EXPECT_TRUE(l1.empty());
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
  EXPECT_EQ(sz, l2.size());
}

TEST(StackAssignment, CopyAssign2) {
  const int sz = 1;
  const int f = 10;
  s21::stack<int> l1{f};
  s21::stack<int> l2;
  l2 = l1;
  l1.push(100);
  EXPECT_EQ(2, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.top(), f);
}

TEST(StackAsssignment, CopyAssign3) {
  const int sz = 3;
  const int t = 3;
  s21::stack<int> l1{1, 2, 3};
  s21::stack<int> l2;
  l2 = l1;
  l1.pop();
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(2, l1.size());
  EXPECT_EQ(l2.top(), t);
}

TEST(StackAssignment, MoveAssign1) {
  const int sz = 0;
  s21::stack<int> l1;
  s21::stack<int> l2;
  l2 = std::move(l1);
  EXPECT_TRUE(l1.empty());
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
  EXPECT_EQ(sz, l2.size());
}

TEST(StackAssignment, MoveAssign2) {
  const int sz = 1;
  const int f = 10;
  s21::stack<int> l1{f};
  s21::stack<int> l2;
  l2 = (std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.top(), f);
}

TEST(StackAsssignment, MoveAssign3) {
  const int sz = 3;
  const int t = 3;
  s21::stack<int> l1{1, 2, 3};
  s21::stack<int> l2;
  l2 = (std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(l2.top(), t);
}

TEST(StackMembers, Top1) {
  std::string s = "Hello";
  s21::stack<std::string> l{s};
  EXPECT_EQ(l.top(), s);
}

TEST(StackMembers, Top2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::stack<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.top(), s3);
}

TEST(StackMembers, ConstTop1) {
  std::string s = "Hello";
  const s21::stack<std::string> l{s};
  EXPECT_EQ(l.top(), s);
}

TEST(StackMembers, ConstTop2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::stack<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.top(), s3);
}

TEST(StackMembers, Empty1) {
  s21::stack<std::string> l;
  EXPECT_TRUE(l.empty());
}

TEST(StackMembers, Empty2) {
  std::string s = "Hello";
  s21::stack<std::string> l{s};
  EXPECT_FALSE(l.empty());
}

TEST(StackMembers, Empty3) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::stack<std::string> l{s1, s2, s3};
  EXPECT_FALSE(l.empty());
}

TEST(StackMembers, Size1) {
  const int sz = 0;
  s21::stack<std::string> l;
  EXPECT_EQ(sz, l.size());
}

TEST(StackMembers, Size2) {
  const int sz = 1;
  std::string s = "Hello";
  s21::stack<std::string> l;
  l.push(s);
  EXPECT_EQ(sz, l.size());
}

TEST(StackMembers, Size3) {
  const int sz = 3;
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::stack<std::string> l{s1, s2};
  l.push(s3);
  EXPECT_EQ(sz, l.size());
}

TEST(StackMembers, Push1) {
  const int e = 10;
  s21::stack<int> l1;
  std::stack<int> l2;
  l1.push(e);
  l2.push(e);
  EXPECT_EQ(l1.top(), l2.top());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(StackMembers, Push2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::stack<int> l1{e1, e2};
  std::stack<int> l2;
  l2.push(e1);
  l2.push(e2);
  l1.push(e3);
  l2.push(e3);
  EXPECT_EQ(l1.top(), l2.top());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(StackMembers, Pop1) {
  const int e1 = 100;
  s21::stack<int> l1{e1};
  std::stack<int> l2;
  l2.push(e1);
  l1.pop();
  l2.pop();
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(StackMembers, Pop2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::stack<int> l1{e1, e2, e3};
  std::stack<int> l2;
  l2.push(e1);
  l2.push(e2);
  l2.push(e3);
  l1.pop();
  l2.pop();
  EXPECT_EQ(l1.top(), l2.top());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(StackMembers, Swap1) {
  const int sz1 = 1, sz2 = 3;
  s21::stack<int> l1{1};
  s21::stack<int> l2{2, 4, 6};
  l1.swap(l2);
  EXPECT_EQ(sz1, l2.size());
  EXPECT_EQ(sz2, l1.size());
  EXPECT_EQ(6, l1.top());
  EXPECT_EQ(1, l2.top());
}

TEST(StackMembers, Swap2) {
  const int sz1 = 1, sz2 = 3;
  s21::stack<int> l1{2, 4, 6};
  s21::stack<int> l2{1};
  l1.swap(l2);
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(sz2, l2.size());
  EXPECT_EQ(1, l1.top());
  EXPECT_EQ(6, l2.top());
}

TEST(StackMembers, InsertManyFront1) {
  const int sz = 5;
  s21::stack<int> l;
  l.insert_many_front(1, 2, 3, 4, 5);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.top());
}

TEST(StackMembers, InsertManyFront2) {
  const int sz = 1;
  s21::stack<int> l;
  l.insert_many_front(1);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, l.top());
}

TEST(StackMembers, InsertManyFront3) {
  const int sz = 8;
  s21::stack<int> l{1, 2, 3, 4, 5};
  l.insert_many_front(10, 20, 30);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.top());
}
