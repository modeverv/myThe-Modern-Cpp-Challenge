#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

/*
 選択アルゴリズム
 要素列と射影関数が与えられたときに、各要素を新たな値に変換して、変換された
 値を要素とする列を返す関数を書きなさい。例えば、id, title, authorを持つbookとい
 う型があり、bookの列を与えたなら、各bookのtitleを要素とする列を返せるようにし
 ます。次に関数の使用例を示します。
 struct book
 {
 int id;
 std::string title;
 std::string author;
 };
 std::vector<book> books {
 {101, "The C++ Programming Language", "Bjarne Stroustrup"},
 {203, "Effective Modern C++", "Scott Meyers"},
 {404, "The Modern C++ Programming Cookbook", "Marius Bancila"}};
 auto titles = select(books, [](book const & b) {return b.title; });
 */
template <
   typename T, typename A, typename F,
   typename R = typename std::decay<typename std::result_of<typename std::decay<F>::type&(typename std::vector<T, A>::const_reference)>::type>::type>
   std::vector<R> select(std::vector<T, A> const & c, F&& f)
{
   std::vector<R> v;
   std::transform(
      std::cbegin(c), std::cend(c),
      std::back_inserter(v),
      std::forward<F>(f));

   return v;
}

struct book
{
   int id;
   std::string title;
   std::string author;
};

int main()
{
   std::vector<book> books{
      {101, "The C++ Programming Language", "Bjarne Stroustrup"},
      {203, "Effective Modern C++", "Scott Meyers"},
      {404, "The Modern C++ Programming Cookbook", "Marius Bancila"}};

   auto titles = select(books, [](book const & b) {return b.title; });

   for (auto const & title : titles)
   {
      std::cout << title << std::endl;
   }
}
