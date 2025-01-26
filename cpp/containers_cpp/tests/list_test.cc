#include <list>
#include <string>

#include "gtest/gtest.h"
#include "s21_containers/s21_list.h"

// explicit template class instantiation for the needs of code coverage
template class s21::list<int>;
template class s21::list<std::string>;

TEST(ListCtor, Default) {
  const int sz = 0;
  s21::list<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(ListCtor, Count1) {
  const int sz = 0;
  s21::list<std::string> l(sz);
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(ListCtor, Count2) {
  const int sz = 1;
  s21::list<std::string> l(sz);
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(ListCtor, Count3) {
  const int sz = 10;
  s21::list<std::string> l(sz);
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(ListCtor, InitializerList1) {
  const int sz = 0;
  s21::list<int> l{};
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(sz, l.size());
}

TEST(ListCtor, InitializerList2) {
  const int sz = 1;
  const int f = 10;
  s21::list<int> l{10};
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(l.front(), f);
}

TEST(ListCtor, InitializerList3) {
  const int sz = 5;
  const int f = 1, b = 5;
  s21::list<int> l{1, 2, 3, 4, 5};
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(l.front(), f);
  EXPECT_EQ(l.back(), b);
}

TEST(ListCtor, Copy1) {
  const int sz = 0;
  s21::list<int> l1;
  s21::list<int> l2(l1);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
}

TEST(ListCtor, Copy2) {
  const int sz = 1;
  const int f = 10;
  s21::list<int> l1{f};
  s21::list<int> l2(l1);
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(ListCtor, Copy3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::list<int> l1{1, 2, 3};
  s21::list<int> l2(l1);
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}

TEST(ListCtor, Move1) {
  const int sz = 0;
  s21::list<int> l1;
  s21::list<int> l2(std::move(l1));
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
}

TEST(ListCtor, Move2) {
  const int sz = 1;
  const int f = 10;
  s21::list<int> l1{f};
  s21::list<int> l2(std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(ListCtor, Move3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::list<int> l1{1, 2, 3};
  s21::list<int> l2(std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}

TEST(ListAssignment, CopyAssign1) {
  const int sz = 0;
  s21::list<int> l1;
  s21::list<int> l2;
  l2 = l1;
  EXPECT_TRUE(l1.empty());
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
  EXPECT_EQ(sz, l2.size());
}

TEST(ListAssignment, CopyAssign2) {
  const int sz = 1;
  const int f = 10;
  s21::list<int> l1{f};
  s21::list<int> l2;
  l2 = l1;
  l1.push_back(100);
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(2, l1.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(ListAsssignment, CopyAssign3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::list<int> l1{1, 2, 3};
  s21::list<int> l2;
  l2 = l1;
  l1.erase(l1.begin());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(2, l1.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}

TEST(ListAssignment, MoveAssign1) {
  const int sz = 0;
  s21::list<int> l1;
  s21::list<int> l2;
  l2 = std::move(l1);
  EXPECT_TRUE(l1.empty());
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz, l1.size());
  EXPECT_EQ(sz, l2.size());
}

TEST(ListAssignment, MoveAssign2) {
  const int sz = 1;
  const int f = 10;
  s21::list<int> l1{f};
  s21::list<int> l2;
  l2 = (std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(l2.front(), f);
}

TEST(ListAsssignment, MoveAssign3) {
  const int sz = 3;
  const int f = 1, b = 3;
  s21::list<int> l1{1, 2, 3};
  s21::list<int> l2;
  l2 = (std::move(l1));
  EXPECT_TRUE(l1.empty());
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(sz, l2.size());
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(l2.front(), f);
  EXPECT_EQ(l2.back(), b);
}

TEST(ListMembers, Front1) {
  std::string s = "Hello";
  s21::list<std::string> l{s};
  EXPECT_EQ(l.front(), s);
}

TEST(ListMembers, Front2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.front(), s1);
}

TEST(ListMembers, ConstFront1) {
  std::string s = "Hello";
  const s21::list<std::string> l{s};
  EXPECT_EQ(l.front(), s);
}

TEST(ListMembers, ConstFront2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.front(), s1);
}

TEST(ListMembers, Back1) {
  std::string s = "Hello";
  s21::list<std::string> l{s};
  EXPECT_EQ(l.back(), s);
}

TEST(ListMembers, Back2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.back(), s3);
}

TEST(ListMembers, ConstBack1) {
  std::string s = "Hello";
  const s21::list<std::string> l{s};
  EXPECT_EQ(l.back(), s);
}

TEST(ListMembers, ConstBack2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(l.back(), s3);
}

TEST(ListMembers, Begin1) {
  std::string s = "Hello";
  s21::list<std::string> l;
  auto it = l.begin();
  l.push_back(s);
  EXPECT_EQ(*--it, s);
}

TEST(ListMembers, Begin2) {
  std::string s = "Hello";
  s21::list<std::string> l{s};
  EXPECT_EQ(*l.begin(), s);
}

TEST(ListMembers, Begin3) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::list<std::string> l{s1, s2, s3};
  auto it = l.cbegin();
  EXPECT_EQ(*it++, s1);
  EXPECT_EQ(*it, s2);
  EXPECT_EQ(it->size(), s2.size());
}

TEST(ListMembers, ConstBegin1) {
  std::string s = "Hello";
  const s21::list<std::string> l{s};
  EXPECT_EQ(*l.begin(), s);
}

TEST(ListMembers, ConstBegin2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(*l.begin(), s1);
  EXPECT_EQ(*++l.begin(), s2);
}

TEST(ListMembers, End1) {
  std::string s = "Hello";
  s21::list<std::string> l;
  auto it = l.end();
  l.push_back(s);
  EXPECT_EQ(*--it, s);
}

TEST(ListMembers, End2) {
  std::string s = "Hello";
  s21::list<std::string> l{s};
  EXPECT_EQ(*--l.end(), s);
}

TEST(ListMembers, End3) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(*--l.end(), s3);
  EXPECT_EQ(*++l.end(), s1);
}

TEST(ListMembers, ConstEnd1) {
  std::string s = "Hello";
  const s21::list<std::string> l{s};
  EXPECT_EQ(*--l.end(), s);
}

TEST(ListMembers, ConstEnd2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(*--l.end(), s3);
  EXPECT_EQ(*++l.end(), s1);
}

TEST(ListMembers, Cend1) {
  std::string s = "Hello";
  s21::list<std::string> l;
  auto it = l.cend();
  l.push_back(s);
  it--;
  EXPECT_EQ(*it, s);
}

TEST(ListMembers, Cend2) {
  std::string s = "Hello";
  s21::list<std::string> l{s};
  EXPECT_EQ(*--l.cend(), s);
}

TEST(ListMembers, Cend3) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(*--l.cend(), s3);
  EXPECT_EQ(*++l.cend(), s1);
}

TEST(ListMembers, ConstCend1) {
  std::string s = "Hello";
  const s21::list<std::string> l{s};
  EXPECT_EQ(*--l.cend(), s);
}

TEST(ListMembers, ConstCend2) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  const s21::list<std::string> l{s1, s2, s3};
  EXPECT_EQ(*--l.cend(), s3);
  EXPECT_EQ(*++l.cend(), s1);
}

TEST(ListMembers, Empty1) {
  s21::list<std::string> l;
  EXPECT_TRUE(l.empty());
}

TEST(ListMembers, Empty2) {
  std::string s = "Hello";
  s21::list<std::string> l{s};
  EXPECT_FALSE(l.empty());
}

TEST(ListMembers, Empty3) {
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::list<std::string> l{s1, s2, s3};
  EXPECT_FALSE(l.empty());
}

TEST(ListMembers, Size1) {
  const int sz = 0;
  s21::list<std::string> l;
  EXPECT_EQ(sz, l.size());
}

TEST(ListMembers, Size2) {
  const int sz = 1;
  std::string s = "Hello";
  s21::list<std::string> l;
  l.push_back(s);
  EXPECT_EQ(sz, l.size());
}

TEST(ListMembers, Size3) {
  const int sz = 3;
  std::string s1 = "Hi";
  std::string s2 = ", ";
  std::string s3 = "World!";
  s21::list<std::string> l{s1, s2};
  l.push_back(s3);
  EXPECT_EQ(sz, l.size());
}

TEST(ListMembers, MaxSize) {
  s21::list<std::string> l1;
  std::list<std::string> l2;
  EXPECT_EQ(l1.max_size(), l2.max_size());
}

TEST(ListMembers, Insert1) {
  const int e = 10;
  s21::list<int> l1;
  std::list<int> l2;
  auto it1 = l1.insert(l1.begin(), e);
  auto it2 = l2.insert(l2.begin(), e);
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(ListMembers, Insert2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::list<int> l1{e1, e2};
  std::list<int> l2{e1, e2};
  auto it1 = l1.insert(l1.end(), e3);
  auto it2 = l2.insert(l2.end(), e3);
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(ListMembers, Erase1) {
  const int e1 = 100;
  s21::list<int> l1{e1};
  std::list<int> l2{e1};
  auto it1 = l1.erase(l1.begin());
  auto it2 = l2.erase(l2.begin());
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(ListMembers, Erase2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::list<int> l1{e1, e2, e3};
  std::list<int> l2{e1, e2, e3};
  auto it1 = l1.erase(l1.begin());
  auto it2 = l2.erase(l2.begin());
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(ListMembers, PushBack1) {
  const int e = 10;
  s21::list<int> l1;
  std::list<int> l2;
  l1.push_back(e);
  l2.push_back(e);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(*--l1.end(), *--l2.end());
}

TEST(ListMembers, PushBack2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::list<int> l1{e1, e2};
  std::list<int> l2{e1, e2};
  l1.push_back(e3);
  l2.push_back(e3);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(*--l1.end(), *--l2.end());
}

TEST(ListMembers, PopBack1) {
  const int e1 = 100;
  s21::list<int> l1{e1};
  std::list<int> l2{e1};
  l1.pop_back();
  l2.pop_back();
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(ListMembers, PopBack2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::list<int> l1{e1, e2, e3};
  std::list<int> l2{e1, e2, e3};
  l1.pop_back();
  l2.pop_back();
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(*--l1.end(), *--l2.end());
}

TEST(ListMembers, PushFront1) {
  const int e = 10;
  s21::list<int> l1;
  std::list<int> l2;
  l1.push_front(e);
  l2.push_front(e);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(*l1.begin(), *l2.begin());
}

TEST(ListMembers, PushFront2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::list<int> l1{e1, e2};
  std::list<int> l2{e1, e2};
  l1.push_front(e3);
  l2.push_front(e3);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(*l1.begin(), *l2.begin());
}

TEST(ListMembers, PopFront1) {
  const int e1 = 100;
  s21::list<int> l1{e1};
  std::list<int> l2{e1};
  l1.pop_front();
  l2.pop_front();
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(ListMembers, PopFront2) {
  const int e1 = 10, e2 = 20, e3 = 30;
  s21::list<int> l1{e1, e2, e3};
  std::list<int> l2{e1, e2, e3};
  l1.pop_front();
  l2.pop_front();
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(*l1.begin(), *l2.begin());
}

TEST(ListMembers, Swap1) {
  const int sz1 = 1, sz2 = 3;
  s21::list<int> l1{1};
  s21::list<int> l2{2, 4, 6};
  l1.swap(l2);
  EXPECT_EQ(sz1, l2.size());
  EXPECT_EQ(sz2, l1.size());
  EXPECT_EQ(2, *l1.begin());
  EXPECT_EQ(1, *l2.begin());
}

TEST(ListMembers, Swap2) {
  const int sz1 = 1, sz2 = 3;
  s21::list<int> l1{2, 4, 6};
  s21::list<int> l2{1};
  l1.swap(l2);
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(sz2, l2.size());
  EXPECT_EQ(2, *l2.begin());
  EXPECT_EQ(1, *l1.begin());
}

TEST(ListMembers, Merge1) {
  const int sz1 = 3;
  s21::list<int> l1;
  s21::list<int> l2{1, 2, 4};
  auto it = l2.begin();
  l1.merge(l2);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(*l1.begin(), 1);
  EXPECT_EQ(*it, 1);
}

TEST(ListMembers, Merge2) {
  const int sz1 = 3;
  s21::list<int> l1{1, 2, 4};
  s21::list<int> l2;
  auto it = --l1.end();
  l1.merge(l2);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(*l1.begin(), 1);
  EXPECT_EQ(*it, 4);
}

TEST(ListMembers, Merge3) {
  const int sz1 = 5;
  s21::list<int> l1{1};
  s21::list<int> l2{2, 3, 4, 5};
  auto it = l2.begin();
  l1.merge(l2);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(*--l1.end(), 5);
  EXPECT_EQ(*it, 2);
}

TEST(ListMembers, Merge4) {
  const int sz1 = 5;
  s21::list<int> l1{6};
  s21::list<int> l2{2, 3, 4, 5};
  auto it = l2.begin();
  l1.merge(l2);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(*--l1.end(), 6);
  EXPECT_EQ(*it, 2);
}

TEST(ListMembers, Merge5) {
  const int sz1 = 3;
  s21::list<int> l{1, 2, 3};
  auto it = l.begin();
  l.merge(l);
  EXPECT_EQ(sz1, l.size());
  EXPECT_EQ(*it, 1);
}

TEST(ListMembers, Splice1) {
  const int sz1 = 5;
  s21::list<int> l1{6};
  s21::list<int> l2{2, 3, 4, 5};
  auto it = l1.begin();
  l1.splice(l1.begin(), l2);
  EXPECT_TRUE(l2.empty());
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(*l1.begin(), 2);
  EXPECT_EQ(*it, 6);
}

TEST(ListMembers, Splice2) {
  const int sz1 = 4;
  s21::list<int> l1{2, 3, 4, 5};
  s21::list<int> l2;
  l1.splice(l1.begin(), l2);
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(*l1.begin(), 2);
}

TEST(ListMembers, Splice3) {
  const int sz1 = 4;
  s21::list<int> l1;
  s21::list<int> l2{2, 3, 4, 5};
  auto it = l2.begin();
  l1.splice(l1.begin(), l2);
  EXPECT_EQ(sz1, l1.size());
  EXPECT_EQ(*l1.begin(), 2);
  EXPECT_EQ(*it, 2);
}

TEST(ListMembers, Reverse1) {
  const int sz = 0;
  s21::list<int> l;
  l.reverse();
  EXPECT_EQ(sz, l.size());
}

TEST(ListMembers, Reverse2) {
  const int sz = 1;
  s21::list<int> l{1};
  l.reverse();
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, *l.begin());
}

TEST(ListMembers, Reverse3) {
  const int sz = 3, e1 = 2, e2 = 6, e3 = 4;
  s21::list<int> l{e1, e2, e3};
  l.reverse();
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(e3, *l.begin());
  EXPECT_EQ(e2, *++l.begin());
  EXPECT_EQ(e1, *--l.end());
}

TEST(ListMembers, Unique1) {
  const int sz = 0;
  s21::list<int> l;
  l.unique();
  EXPECT_EQ(sz, l.size());
}

TEST(ListMembers, Unique2) {
  const int sz = 1;
  s21::list<int> l{1};
  l.unique();
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, *l.begin());
}

TEST(ListMembers, Unique3) {
  const int sz = 1;
  s21::list<int> l{1, 1, 1, 1, 1};
  l.unique();
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, *l.begin());
}

TEST(ListMembers, Unique4) {
  const int sz = 5;
  s21::list<int> l{1, 2, 3, 4, 5};
  l.unique();
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, *--l.end());
}

TEST(ListMembers, Unique5) {
  const int sz = 3;
  s21::list<int> l{1, 2, 2, 2, 5};
  l.unique();
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, *--l.end());
}

TEST(ListMembers, Sort1) {
  const int sz = 0;
  s21::list<int> l;
  l.sort();
  EXPECT_EQ(sz, l.size());
}

TEST(ListMembers, Sort2) {
  s21::list<int> l{10};
  l.sort();
  EXPECT_EQ(10, *l.begin());
}

TEST(ListMembers, Sort3) {
  s21::list<int> l1{5, 4, 3, 2, 1};
  std::list<int> l2{5, 4, 3, 2, 1};
  l1.sort();
  l2.sort();
  auto it1 = l1.begin();
  for (auto it2 = l2.begin(); it2 != l2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(ListMembers, Sort4) {
  s21::list<int> l1{5, 4, 3, 2, 10};
  std::list<int> l2{5, 4, 3, 2, 10};
  l1.sort();
  l2.sort();
  auto it1 = l1.begin();
  for (auto it2 = l2.begin(); it2 != l2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(ListMembers, Sort5) {
  s21::list<std::string> l1{"Hello", ", ", "World", "!"};
  std::list<std::string> l2{"Hello", ", ", "World", "!"};
  auto itb1 = l1.begin(), ite1 = --l1.end();
  auto itb2 = l2.begin(), ite2 = --l2.end();
  l1.sort();
  l2.sort();
  auto it1 = l1.begin();
  for (auto it2 = l2.begin(); it2 != l2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(*itb1, *itb2);
  EXPECT_EQ(*ite1, *ite2);
  EXPECT_EQ(ite1->size(), ite2->size());
}

TEST(ListMembers, InsertMany1) {
  const int sz = 5;
  s21::list<int> l;
  auto it = l.insert_many(l.begin(), 1, 2, 3, 4, 5);
  EXPECT_EQ(5, *it);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(ListMembers, InsertMany2) {
  const int sz = 1;
  s21::list<int> l;
  auto it = l.insert_many(l.begin(), 1);
  EXPECT_EQ(1, *it);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(ListMembers, InsertMany3) {
  const int sz = 8;
  s21::list<int> l{1, 2, 3, 4, 5};
  auto it = l.insert_many(l.begin(), 10, 20, 30);
  EXPECT_EQ(30, *it);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.back());
  EXPECT_EQ(10, l.front());
}

TEST(ListMembers, InsertManyBack1) {
  const int sz = 5;
  s21::list<int> l;
  l.insert_many_back(1, 2, 3, 4, 5);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(ListMembers, InsertManyBack2) {
  const int sz = 1;
  s21::list<int> l;
  l.insert_many_back(1);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(ListMembers, InsertManyBack3) {
  const int sz = 8;
  s21::list<int> l{1, 2, 3, 4, 5};
  l.insert_many_back(10, 20, 30);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(30, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(ListMembers, InsertManyFront1) {
  const int sz = 5;
  s21::list<int> l;
  l.insert_many_front(1, 2, 3, 4, 5);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(ListMembers, InsertManyFront2) {
  const int sz = 1;
  s21::list<int> l;
  l.insert_many_front(1);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(1, l.back());
  EXPECT_EQ(1, l.front());
}

TEST(ListMembers, InsertManyFront3) {
  const int sz = 8;
  s21::list<int> l{1, 2, 3, 4, 5};
  l.insert_many_front(10, 20, 30);
  EXPECT_EQ(sz, l.size());
  EXPECT_EQ(5, l.back());
  EXPECT_EQ(10, l.front());
}
