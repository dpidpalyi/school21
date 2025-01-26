#include <queue>
#include <string>

#include "gtest/gtest.h"
#include "s21_containers/s21_queue.h"

// explicit template class instantiation for the needs of code coverage
template class s21::queue<int>;
template class s21::queue<std::string>;

TEST(QueueCtor, Default) {
  const int sz = 0;
  s21::queue<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(QueueCtor, InitializerQueue1) {
  const int sz = 0;
  s21::queue<int> l{};
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(QueueCtor, InitializerQueue2) {
  const int sz = 1;
  const int f = 10;
  s21::queue<int> l{10};
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(l.front(), f);
}

TEST(QueueCtor, InitializerQueue3) {
  const int sz = 5;
  const int f = 1, b = 5;
  s21::queue<int> l{1, 2, 3, 4, 5};
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(l.front(), f);
  EXPECT_EQ(l.back(), b);
}

TEST(QueueCtor, Copy1) {
  const int sz = 0;
  s21::queue<int> l1;
  s21::queue<int> l2(l1);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
}

TEST(QueueCtor, Copy2) {
  const int sz = 1;
  const int f = 10;
  s21::queue<int> l1{f};
  s21::queue<int> l2(l1);
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(QueueCtor, Copy3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::queue<int> l1{1, 2, 3};
  s21::queue<int> l2(l1);
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}

TEST(QueueCtor, Move1) {
  const int sz = 0;
  s21::queue<int> l1;
  s21::queue<int> l2(std::move(l1));
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
}

TEST(QueueCtor, Move2) {
  const int sz = 1;
  const int f = 10;
  s21::queue<int> l1{f};
  s21::queue<int> l2(std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(QueueCtor, Move3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::queue<int> l1{1, 2, 3};
  s21::queue<int> l2(std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}

TEST(QueueAssignment, CopyAssign1) {
  const int sz = 0;
  s21::queue<int> l1;
  s21::queue<int> l2;
  l2 = l1;
  EXPECT_TRUE(l1.empty());
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
  EXPECT_EQ(sz, l2.size());
}

TEST(QueueAssignment, CopyAssign2) {
  const int sz = 1;
  const int f = 10;
  s21::queue<int> l1{f};
  s21::queue<int> l2;
  l2 = l1;
  l1.push(100);
  EXPECT_EQ(2, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(QueueAsssignment, CopyAssign3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::queue<int> l1{1, 2, 3};
  s21::queue<int> l2;
  l2 = l1;
  l1.pop();
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(2, l1.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}
TEST(QueueAssignment, MoveAssign1) {
  const int sz = 0;
  s21::queue<int> l1;
  s21::queue<int> l2;
  l2 = std::move(l1);
  EXPECT_TRUE(l1.empty());
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
  EXPECT_EQ(sz, l2.size());
}

TEST(QueueAssignment, MoveAssign2) {
  const int sz = 1;
  const int f = 10;
  s21::queue<int> l1{f};
  s21::queue<int> l2;
  l2 = (std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(QueueAsssignment, MoveAssign3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::queue<int> l1{1, 2, 3};
  s21::queue<int> l2;
  l2 = (std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}

TEST(QueueMembers, Front1) {
  std::string s = "Hello";
  s21::queue<std::string> l{s};
  EXPECT_EQ(l.front(), s);
}

TEST(QueueMembers, Front2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::queue<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.front(), s1);
}

TEST(QueueMembers, ConstFront1) {
  std::string s = "Hello";
  const s21::queue<std::string> l{s};
  EXPECT_EQ(l.front(), s);
}

TEST(QueueMembers, ConstFront2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::queue<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.front(), s1);
}

TEST(QueueMembers, Back1) {
  std::string s = "Hello";
  s21::queue<std::string> l{s};
  EXPECT_EQ(l.back(), s);
}

TEST(QueueMembers, Back2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::queue<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.back(), s3);
}

TEST(QueueMembers, ConstBack1) {
  std::string s = "Hello";
  const s21::queue<std::string> l{s};
  EXPECT_EQ(l.back(), s);
}

TEST(QueueMembers, ConstBack2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::queue<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.back(), s3);
}

TEST(QueueMembers, Empty1) {
  s21::queue<std::string> l;
  EXPECT_TRUE(l.empty());
}

TEST(QueueMembers, Empty2) {
  std::string s = "Hello";
  s21::queue<std::string> l{s};
  EXPECT_FALSE(l.empty());
}

TEST(QueueMembers, Empty3) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::queue<std::string> l{s1, s2, s3};
  EXPECT_FALSE(l.empty());
}

TEST(QueueMembers, Size1) {
  const int sz = 0;
  s21::queue<std::string> l;
  EXPECT_EQ(sz, l.size());
}

TEST(QueueMembers, Size2) {
  const int sz = 1;
  std::string s = "Hello";
  s21::queue<std::string> l;
  l.push(s);
  EXPECT_EQ(sz, l.size());
}

TEST(QueueMembers, Size3) {
  const int sz = 3;
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::queue<std::string> l{s1, s2};
  l.push(s3);
  EXPECT_EQ(sz, l.size());
}

TEST(QueueMembers, Push1) {
  const int e = 10;
  s21::queue<int> l1;
  std::queue<int> l2;
  l1.push(e);
  l2.push(e);
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(QueueMembers, Push2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::queue<int> l1{e1, e2};
  std::queue<int> l2;
  l2.push(e1);
  l2.push(e2);
  l1.push(e3);
  l2.push(e3);
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(QueueMembers, Pop1) {
  const int e1 = 100;
  s21::queue<int> l1{e1};
  std::queue<int> l2;
  l2.push(e1);
  l1.pop();
  l2.pop();
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(QueueMembers, Pop2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::queue<int> l1{e1, e2, e3};
  std::queue<int> l2;
  l2.push(e1);
  l2.push(e2);
  l2.push(e3);
  l1.pop();
  l2.pop();
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(QueueMembers, Swap1) {
  const int sz1 = 1, sz2 = 3;
  s21::queue<int> l1{1};
  s21::queue<int> l2{2, 4, 6};
  l1.swap(l2);
  EXPECT_EQ(sz1, l2.size());
  EXPECT_EQ(sz2, l1.size());
  EXPECT_EQ(6, l1.back());
  EXPECT_EQ(1, l2.back());
  EXPECT_EQ(2, l1.front());
  EXPECT_EQ(1, l2.front());
}

TEST(QueueMembers, Swap2) {
  const int sz1 = 1, sz2 = 3;
  s21::queue<int> l1{2, 4, 6};
  s21::queue<int> l2{1};
  l1.swap(l2);
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(sz2, l2.size());
  EXPECT_EQ(1, l1.back());
  EXPECT_EQ(6, l2.back());
  EXPECT_EQ(1, l1.front());
  EXPECT_EQ(2, l2.front());
}

TEST(QueueMembers, InsertManyBack1) {
  const int sz = 5;
  s21::queue<int> l;
  l.insert_many_back(1, 2, 3, 4, 5);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(QueueMembers, InsertManyBack2) {
  const int sz = 1;
  s21::queue<int> l;
  l.insert_many_back(1);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(QueueMembers, InsertManyBack3) {
  const int sz = 8;
  s21::queue<int> l{1, 2, 3, 4, 5};
  l.insert_many_back(10, 20, 30);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(30, l.back());
  EXPECT_EQ(1, l.front());
}
