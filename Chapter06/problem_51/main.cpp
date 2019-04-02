#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
 電話番号のリストの変換
 与えられた電話番号のリストを、どれも+記号が前に付いた国番号から始まる形式に
 変換する関数を書きなさい。電話番号の間の空白は取り除きます。入力リストと出力の
 例を次に示します。
 07555 123456 => +447555123456
 07555123456 => +447555123456
 +44 7555 123456 => +447555123456
 44 7555 123456 => +447555123456
 7555 123456 => +447555123456
 */

bool starts_with(std::string_view str, std::string_view prefix)
{
   return str.find(prefix) == 0;
}

void normalize_phone_numbers(
   std::vector<std::string>& numbers,
   std::string const & countryCode)
{
   std::transform(
      std::cbegin(numbers), std::cend(numbers),
      std::begin(numbers),
      [countryCode](std::string const & number) {
      std::string result;
      if (number.size() > 0)
      {
         if (number[0] == '0')
            result = "+" + countryCode + number.substr(1);
         else if (starts_with(number, countryCode))
            result = "+" + number;
         else if (starts_with(number, "+" + countryCode))
            result = number;
         else
            result = "+" + countryCode + number;
      }

      result.erase(
         std::remove_if(
            std::begin(result), std::end(result),
            [](const char ch) {return isspace(ch); }),
         std::end(result));

      return result;
   });
}

int main()
{
   std::vector<std::string> numbers{
      "07555 123456",
      "07555123456",
      "+44 7555 123456",
      "44 7555 123456",
      "7555 123456"
   };

   normalize_phone_numbers(numbers, "44");

   for (auto const & number : numbers)
   {
      std::cout << number << std::endl;
   }
}
