#include <string>
#include <string_view>
#include <vector>
#include <assert.h>

/*
 最長回文部分文字列
 入力文字列に対して、最長の回文になっている部分文字列を返す関数を書きなさい。
 もし、そのような部分文字列が複数個あるなら、最初の部分文字列を返しなさい。
 */
std::string longest_palindrome(std::string_view str)
{
   size_t const len = str.size();
   size_t longestBegin = 0;
   size_t maxLen = 1;

   std::vector<bool> table(len * len, false);

   for (size_t i = 0; i < len; i++)
   {
      table[i*len + i] = true;
   }

   for (size_t i = 0; i < len - 1; i++)
   {
      if (str[i] == str[i + 1]) 
      {
         table[i*len + i + 1] = true;
         if (maxLen < 2)
         {
            longestBegin = i;
            maxLen = 2;
         }
      }
   }

   for (size_t k = 3; k <= len; k++)
   {
      for (size_t i = 0; i < len - k + 1; i++)
      {
         size_t j = i + k - 1;
         if (str[i] == str[j] && table[(i + 1)*len + j - 1])
         {
            table[i*len +j] = true;
            if (maxLen < k)
            {
               longestBegin = i;
               maxLen = k;
            }
         }
      }
   }

   return std::string(str.substr(longestBegin, maxLen));
}

int main()
{
   using namespace std::string_literals;

   assert(longest_palindrome("sahararahnide") == "hararah");
   assert(longest_palindrome("level") == "level");
   assert(longest_palindrome("s") == "s");
   assert(longest_palindrome("aabbcc") == "aa");
   assert(longest_palindrome("abab") == "aba");
}
