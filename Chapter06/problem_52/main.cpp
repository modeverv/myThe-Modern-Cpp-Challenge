#include <iostream>
#include <string>
#include <algorithm>

/*
 文字列の文字の順列を生成
 与えられた文字列を文字に分解して並び替え、すべての順列をコンソールに出力す
 る関数を書きなさい。この関数では、再帰を使ったものと使わないものの2つのバー
 ジョンを作りなさい。
 */
void print_permutations(std::string str)
{
   std::sort(std::begin(str), std::end(str));

   do
   {
      std::cout << str << std::endl;
   } while (std::next_permutation(std::begin(str), std::end(str)));
}

void next_permutation(std::string str, std::string perm)
{
   if (str.empty()) std::cout << perm << std::endl;
   else
   {
      for (size_t i = 0; i < str.size(); ++i)
      {
         next_permutation(str.substr(1), perm + str[0]);

         std::rotate(std::begin(str), std::begin(str) + 1, std::end(str));
      }
   }
}

void print_permutations_recursive(std::string str)
{
   next_permutation(str, "");
}

int main()
{
   std::cout << "non-recursive version" << std::endl;
   print_permutations("main");

   std::cout << "recursive version" << std::endl;
   print_permutations_recursive("main");
}
