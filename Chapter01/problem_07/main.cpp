#include <iostream>
#include <set>
#include <cmath>

/*
 友愛数
 1,000,000より小さいすべての友愛数のペアを出力するプログラムを書きなさい。
 */
int sum_proper_divisors(int const number)
{
   int result = 1;
   for (int i = 2; i <= std::sqrt(number); i++)
   {
      if (number%i == 0)
      {
         result += (i == (number / i)) ? i : (i + number / i);
      }
   }

   return result;
}

void print_amicables(int const limit)
{
   for (int number = 4; number < limit; ++number)
   {
/*
 auto i = 0;                         // i は int 型
 const auto l = 0L;                  // l は const long 型
 auto& r = i;                        // r は int& 型
 auto s = "";                        // s は const char* 型
 auto p = std::make_pair(1, 'c');    // p は std::pair<int, char> 型
 auto q = std::make_shared<int>(42); // q は std::shared_ptr<int> 型
 auto z = { 1.0, 2.0, 3.0, };        // z は std::initializer_list<double> 型
 auto f = []{};                      // f は 引数を取らずに値を返さない operator() を持つユニークなクロージャ型
 */
      auto sum1 = sum_proper_divisors(number);

      if (sum1 < limit)
      {
         auto sum2 = sum_proper_divisors(sum1);

         if (sum2 == number && number != sum1)
         {
            std::cout << number << "," << sum1 << std::endl;
         }
      }
   }
}

void print_amicables_once(int const limit)
{
   std::set<int> printed;
   for (int number = 4; number < limit; ++number)
   {
      if (printed.find(number) != printed.end()) continue;

      auto sum1 = sum_proper_divisors(number);

      if (sum1 < limit)
      {
         auto sum2 = sum_proper_divisors(sum1);

         if (sum2 == number && number != sum1)
         {
            printed.insert(number);
            printed.insert(sum1);

            std::cout << number << "," << sum1 << std::endl;
         }
      }
   }
}

int main()
{
   print_amicables(1000000);
   print_amicables_once(1000000);
}
