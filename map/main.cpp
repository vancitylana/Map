#include <iostream>
#include "TSortMap.h"
using namespace std;
int main()
{
  TSortMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  a.Add("day", 71);
  a.save("test.txt");
  TMap<string, int> b = TMap<string, int>::load("test.txt");
  std::cout << b << std::endl;
  return 0;
}