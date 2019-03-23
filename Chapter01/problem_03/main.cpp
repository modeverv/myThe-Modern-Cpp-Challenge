#include <iostream>
#include <numeric>
#include <vector>

/*
 最小公倍数
 与えられた2個以上の正の整数について、その最小公倍数を計算して出力するプロ
 グラムを書きなさい。
 */
int mygcd(int a,int b)
{
  if(b == 0){
    return a;
  }
  return mygcd(b, a % b);
}
int mylcm(int a, int b)
{
  int gcd = mygcd(a,b);
  if(gcd == 0){
    return 0;
  }
  return a * b / gcd;
}
int main()
{
  std::cout << mylcm(20,10) << std::endl;
}

int gcd(int const a, int const b)
{
   return b == 0 ? a : gcd(b, a % b);
}

int lcm(int const a, int const b)
{
   int h = gcd(a, b);
   return h ? (a * (b / h)) : 0;
}

template<class InputIt>
int lcmr(InputIt first, InputIt last)
{
   return std::accumulate(first, last, 1, lcm);
}
/*
int main()
{
   int n = 0;
   std::cout << "Input count:";
   std::cin >> n;

   std::vector<int> numbers;
   for (int i = 0; i < n; ++i)
   {
      int v{ 0 };
      std::cin >> v;
      numbers.push_back(v);
   }

   std::cout
      << "lcm="
      << lcmr(std::begin(numbers), std::end(numbers))
      << std::endl;
}
*/
