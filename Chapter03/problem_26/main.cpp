#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <array>
#include <list>
#include <assert.h>
/*
 指定した区切り文字で文字列を連結する
 一連の文字列と区切り文字を入力として、すべての入力文字列を区切り文字を介し
 て連結した新しい文字列を出力する関数を書きなさい。区切り文字は最後の文字列の
 あとには付きません。入力文字列がなければ、空文字列を返します。
 入力 { "this","is","an","example" }
 区切り文字 ' '（空白）
 出力 "this is an example"
 */
template <typename Iter>
std::string join_strings(Iter begin, Iter end, char const * const separator)
{
   std::ostringstream os;
   std::copy(begin, end-1, std::ostream_iterator<std::string>(os, separator));
   //a,b,c => a,sep,b,sep,c,sepってやってるイメージ
   os << *(end-1);
   return os.str();
}


template <typename C>
std::string join_strings(C const & c, char const * const separator)
{
   if (c.size() == 0) return std::string{};
   return join_strings(std::begin(c), std::end(c), separator);
}

int main()
{
   using namespace std::string_literals;

   std::vector<std::string> v1{ "this","is","an","example" };
   std::vector<std::string> v2{ "example" };
   std::vector<std::string> v3{ };
   
   assert(
      join_strings(v1, " ") == "this is an example"s);

   assert(
      join_strings(v2, " ") == "example"s);

   assert(
      join_strings(v3, " ") == ""s);

   std::array<std::string, 4> a1{ {"this","is","an","example"} };
      std::array<std::string, 1> a2{ {"example"} };
   std::array<std::string, 0> a3{};

   assert(
      join_strings(a1, " ") == "this is an example"s);

   assert(
      join_strings(a2, " ") == "example"s);

   assert(
      join_strings(a3, " ") == ""s);
}
