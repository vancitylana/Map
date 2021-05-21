#include <gtest.h>
#include "TMap.h"
#include "TSortMap.h"
using namespace std;

TEST(TMap, can_create_map)
{
  TMap<string, int> a;
  EXPECT_EQ(0, a.GetCount());
}


TEST(TMap, can_add_item)
{
  TMap<string, int> a;
  a.Add("hello", 444);
  EXPECT_EQ(444, a["hello"]);
}

TEST(TMap, can_find_item)
{
  TMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rain", 3);
  EXPECT_EQ(3, a.Find("rain"));
}

TEST(TMap, can_delete_item)
{
  TMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  a.Add("day", 77);
  a.Delete("world");
  ASSERT_ANY_THROW(a.Find("world"));
}

TEST(TMap, unexpected_indexation_wont_cause_error)
{
  TMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  ASSERT_NO_THROW(a["some key"]);
}

TEST(TMap, can_iterate_object)
{
  TMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  int sorted[3] = { 444, 555, 34 };
  int i = 0;
  TMap<string, int>::iterator it = a.Begin();
  while (it.CanGoNext()) {
    EXPECT_EQ(sorted[i], it.GetVal());
    it.GoNext();
    i++;
  }
}

TEST(TSorted, can_create_sorted_map) {
  TSortMap<string, int> a;
  EXPECT_EQ(0, a.GetCount());
}

TEST(TSorted, can_create_sorted_map_from_array) {
  int size = 4;
  auto* arr = new TNode<string, int>[size];
  // world rainy hello day - sorted
  string strs[4] = { "hello", "world", "rainy", "day" };
  string sorted[4] = { "world", "rainy", "hello", "day" };
  for (int i = 0; i < size; ++i) {
    arr[i] = TNode<string, int>(strs[i], i);
  }
  TSortMap<string, int> a(size, arr);
  TNode<string, int>* mas = a.GetMas();
  for (int j = 0; j < size; ++j) {
    EXPECT_EQ(sorted[j], mas[j].GetKey());
  }
}

TEST(TSorted, can_create_sorted_map_adding) {
  int size = 4;
  TSortMap<string, int> a;
  // world rainy hello day - sorted
  string strs[4] = { "hello", "world", "rainy", "day" };
  string sorted[4] = { "world", "rainy", "hello", "day" };
  for (int i = 0; i < size; ++i) {
    a.Add(strs[i], i);
  }
  TNode<string, int>* mas = a.GetMas();
  for (int j = 0; j < size; ++j) {
    EXPECT_EQ(sorted[j], mas[j].GetKey());
  }
}

TEST(TSorted, can_find_item) {
  TSortMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rain", 3);
  EXPECT_EQ(3, a.Find("rain"));
}

TEST(TSorted, can_delete_item) {
  TSortMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rain", 3);
  a.Delete("world");
  ASSERT_ANY_THROW(a.Find("world"));
}

TEST(TSorted, can_iterate_object)
{
  TSortMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  a.Add("day", 71);
  int sorted[4] = { 555, 34, 444, 71 };
  int i = 0;
  TMap<string, int>::iterator it = a.Begin();
  while (it.CanGoNext()) {
    EXPECT_EQ(sorted[i], it.GetVal());
    it.GoNext();
    i++;
  }
}

TEST(TSorted, can_save_and_load_map)
{
  TSortMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  a.Add("day", 71);
  a.save("test.txt");
  TMap<string, int> b = TMap<string, int>::load("test.txt");
  TSortMap<string, int>::iterator it = a.Begin();
  TSortMap<string, int>::iterator it2 = b.Begin();
  while (it.CanGoNext()) {
    EXPECT_EQ(it.GetVal(), it2.GetVal());
    EXPECT_EQ(it2.GetKey(), it2.GetKey());
    it.GoNext();
    it2.GoNext();
  }
}