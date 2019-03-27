#include <string>
#include <sstream>
#include <cctype>
#include <assert.h>
/*
 英文タイトルのキャピタライズ
 入力テキストをキャピタライズして、各単語が大文字で始まり残りは小文字になるよ
 うに変換する関数を書きなさい。例えば、テキスト"the c++ challenger"を"The C++
 Challenger"に変換します。
 */
template <class Elem>
//https://cpprefjp.github.io/reference/string/basic_string.html
//日本語扱うときはstd::wstringっぽい
//https://qiita.com/javacommons/items/9ea0c8fd43b61b01a8da
//UTF-8文字列リテラル
//https://cpprefjp.github.io/lang/cpp11/utf8_string_literals.html
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
tstring<Elem> capitalize(tstring<Elem> const & text)
{
   tstringstream<Elem> result;

   bool newWord = true;
   for (auto const ch : text)
   {
      newWord = newWord || std::ispunct(ch) || std::isspace(ch);
      if (std::isalpha(ch))
      {
         if (newWord)
         {
            result << static_cast<Elem>(std::toupper(ch));
            newWord = false;
         }
         else
            result << static_cast<Elem>(std::tolower(ch));
      }
      else result << ch;
   }

   return result.str();
}

int main()
{
   using namespace std::string_literals;

   std::string text = "THIS IS an ExamplE, should wORk!";
   std::string expected = "This Is An Example, Should Work!";
   assert(expected == capitalize(text));

   //https://cpprefjp.github.io/reference/cassert/assert.html
   //sってなに
   // https://cpprefjp.github.io/reference/string/basic_string/op_s.html
   // std::stringのリテラル
   assert(
          L"The C++ Challenger"s ==
          capitalize(L"the c++ challenger"s));
   
   assert(
      L"This Is An Example, Should Work!"s == 
      capitalize(L"THIS IS an ExamplE, should wORk!"s));
}
