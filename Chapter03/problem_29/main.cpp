#include <string>
#include <string_view>
#include <regex>
#include <assert.h>
/*
 ナンバープレートの検証
 LLL-LL DDDまたはLLL-LL DDDDというフォーマット（LはAからZの大文字、Dは数字）
 のナンバープレートを考えます。次の関数を書きなさい。
 ● ナンバープレートが正しいフォーマットか検証する関数
 ● 入力テキストから、ナンバープレートに相当する部分文字列すべてを取り出して
 返す関数
 */
bool validate_license_plate_format(std::string_view str)
{
   std::regex rx(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
   return std::regex_match(str.data(), rx);
}

std::vector<std::string> extract_license_plate_numbers(std::string const & str)
{
   std::regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})*)");
   std::smatch match;
   std::vector<std::string> results;

   for(auto i = std::sregex_iterator(std::cbegin(str), std::cend(str), rx); 
       i != std::sregex_iterator(); ++i) 
   {
      if((*i)[1].matched)
         results.push_back(i->str());
   }

   return results;
}

int main()
{
   assert(validate_license_plate_format("ABC-DE 123"));
   assert(validate_license_plate_format("ABC-DE 1234"));
   assert(!validate_license_plate_format("ABC-DE 12345"));
   assert(!validate_license_plate_format("abc-de 1234"));

   std::vector<std::string> expected{"AAA-AA 123", "ABC-DE 1234", "XYZ-WW 0001"};
   std::string text("AAA-AA 123qwe-ty 1234  ABC-DE 123456..XYZ-WW 0001");
   assert(expected == extract_license_plate_numbers(text));
}
