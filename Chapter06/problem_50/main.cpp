#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <algorithm>

/*
 電話番号のリストをフィルタリング
 与えられた電話番号のリストから、指定された国の電話番号だけを返す関数を書き
 なさい。国は、国際電話の国番号で（例えば英国の場合は44）示します。電話番号は、
 国番号、+国番号、あるいは国番号なしで始まる場合があります。国番号のない電話番
 号は無視します。
 */
bool starts_with(std::string_view str, std::string_view prefix)
{
   return str.find(prefix) == 0;
}

template <typename InputIt>
std::vector<std::string> filter_numbers(
   InputIt begin, InputIt end,
   std::string const & countryCode)
{
   std::vector<std::string> result;

   std::copy_if(
      begin, end,
      std::back_inserter(result),
      [countryCode](auto const & number) {
      return starts_with(number, countryCode) ||
             starts_with(number, "+" + countryCode);
   });

   return result;
}

std::vector<std::string> filter_numbers(
   std::vector<std::string> const & numbers,
   std::string const & countryCode)
{
  //https://cpprefjp.github.io/reference/iterator/cbegin.html
  /*
   範囲から先頭要素への読み取り専用イテレータを取得する。
   */
   return filter_numbers(
      std::cbegin(numbers), std::cend(numbers), 
      countryCode);
}


int main()
{
   std::vector<std::string> numbers{
      "+40744909080",
      "44 7520 112233",
      "+44 7555 123456",
      "40 7200 123456",
      "7555 123456"
   };

   auto result = filter_numbers(numbers, "44");

   for (auto const & number : result)
   {
      std::cout << number << std::endl;
   }
}
