#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <list>

/*
 任意個数の要素をコンテナに追加
 push_back(T&& value)メソッドを備えたコンテナの末尾に任意個数の要素を追加で
 きる汎用の関数を書きなさい。
 */

template<typename C, typename... Args>
void push_back(C& c, Args&&... args)
{
   (c.push_back(args), ...);
}

int main()
{
   std::vector<int> v;
   push_back(v, 1, 2, 3, 4);
   std::copy(std::begin(v), std::end(v), 
             std::ostream_iterator<int>(std::cout, " "));

   std::list<int> l;
   push_back(l, 1, 2, 3, 4);   
   std::copy(std::begin(l), std::end(l), 
             std::ostream_iterator<int>(std::cout, " "));
}
