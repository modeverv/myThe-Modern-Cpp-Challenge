#include <iostream>

/*
 問 題 1
 3または5で割り切れる正の整数の総和
 与えられた上限までの3または5で割り切れる正の整数の総和を計算して出力するプ
 ログラムを書きなさい。
 */
int main()
{
  unsigned int limit = 10;
  unsigned long long sum = 0;
  for (unsigned int i=1; i < limit; i++){
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }
  std::cout << "sum=" << sum << std::endl;
/*
      unsigned int limit = 0;
   std::cout << "Upper limit:";
   std::cin >> limit;

   unsigned long long sum = 0;
   for (unsigned int i = 3; i < limit; ++i)
   {
      if (i % 3 == 0 || i % 5 == 0)
         sum += i;
   }

   std::cout << "sum=" << sum << std::endl;
*/
}
