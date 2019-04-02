#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>
#include <string_view>

/*
 テキストヒストグラム
 与えられた英語のテキストで、各英字の出現割合を求めてヒストグラムを出力する
 プログラムを書きなさい。頻度は全英字数に対する各英字の出現回数の割合です。プ
 ログラムは、英字だけを計測して、数字、記号、その他の文字を無視します。頻度は、
 テキストサイズではなく全英字数に対する割合です。
 */
std::map<char, double> analyze_text(std::string_view text)
{
   std::map<char, double> frequencies;
   for (char ch = 'a'; ch <= 'z'; ch++)
      frequencies[ch] = 0;

   for (auto ch : text)
   {
      if (isalpha(ch))
         frequencies[tolower(ch)]++;
   }

   auto total = std::accumulate(
      std::cbegin(frequencies), std::cend(frequencies),
      0ull,
      [](auto const sum, auto const & kvp) {
      return sum + static_cast<unsigned long long>(kvp.second);
   });

   std::for_each(
      std::begin(frequencies), std::end(frequencies),
      [total](auto & kvp) {
      kvp.second = (100.0 * kvp.second) / total;
   });

   return frequencies;
}

int main()
{
   auto result = analyze_text(R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.)");

   for (auto const & kvp : result)
   {
      std::cout
         << kvp.first << " : "
         << std::fixed
         << std::setw(5) << std::setfill(' ')
         << std::setprecision(2) << kvp.second << std::endl;
   }
}
