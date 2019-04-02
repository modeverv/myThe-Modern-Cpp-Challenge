#include <iostream>
#include <vector>

/*
 ペア作成アルゴリズム
 要素列が与えられたときに、入力列の要素を2つずつペアにした新たな列を返す汎用
 関数を書きなさい。入力列が奇数個の要素の場合は、末尾の要素を無視します。例え
 ば、入力列が{1, 1, 3, 5, 8, 13, 21}ならば、結果は{ {1, 1}, {3, 5}, {8, 13} }
 となります。
 */
template <typename Input, typename Output>
void pairwise(Input begin, Input end, Output result)
{
   auto it = begin;
   while (it != end)
   {
      auto v1 = *it++; if (it == end) break;
      auto v2 = *it++;
      result++ = std::make_pair(v1, v2);
   }
}

template <typename T>
std::vector<std::pair<T, T>> pairwise(std::vector<T> const & range)
{
   std::vector<std::pair<T, T>> result;
   pairwise(std::begin(range), std::end(range),
      std::back_inserter(result));

   return result;
}

int main()
{
   std::vector<int> v{ 1, 1, 3, 5, 8, 13, 21 };

   auto result = pairwise(v);

   for (auto const & p : result)
   {
      std::cout << '{' << p.first << ',' << p.second << '}' << std::endl;
   }
}
