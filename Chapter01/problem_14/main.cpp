#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <assert.h>

/*
 ISBNの検証
 文字列として与えられた10桁の値が、10桁のISBN-10番号として正しいかどうか検
 証するプログラムを書きなさい。
 */
bool validate_isbn_10(std::string_view isbn)
{
   auto valid = false;
   // https://cpprefjp.github.io/reference/algorithm/count_if.html
   if (isbn.size() == 10 &&
       std::count_if(std::begin(isbn), std::end(isbn), isdigit) == 10)
   {
      auto w = 10;
      auto sum = std::accumulate(
         std::begin(isbn), std::end(isbn), 0,
         [&w](int const total, char const c) {
            return total + w-- * (c - '0'); });

      valid = !(sum % 11);
   }

   return valid;
}

int main()
{
   assert(validate_isbn_10("0306406152"));
   assert(!validate_isbn_10("0306406151"));

   std::string isbn;
   std::cout << "isbn:";
   std::cin >> isbn;

   std::cout << "valid: " << validate_isbn_10(isbn) << std::endl;
   
}
