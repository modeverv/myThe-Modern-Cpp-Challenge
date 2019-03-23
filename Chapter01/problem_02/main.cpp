#include <iostream>

/*

 最大公約数
 与えられた2個の正の整数の最大公約数を計算して出力するプログラムを書きなさ
 い。
 */

unsigned int gcd(unsigned int a,unsigned int b)
{
  if(b == 0){
    return a;
  }
  return gcd(b, a % b);
}
int main()
{
  std::cout << gcd(100,34) << std::endl;
}
/*
unsigned int gcd(unsigned int const a, unsigned int const b)
{
   return b == 0 ? a : gcd(b, a % b);
}

unsigned int gcd2(unsigned int a, unsigned int b)
{
   while (b != 0)
   {
      unsigned int r = a % b;
      a = b;
      b = r;
   }

   return a;
}

unsigned int mygcd(unsigned int a, unsigned int b)
{
	if (b == 0) {
		return a;
	}
	else {
		return mygcd(b, a % b);
	}
}


int main()
{
	unsigned int a = 10, b = 5;
    unsigned int x = mygcd(a, b);
	std::cout << x << std::endl;


	/*
   std::cout << "Input numbers:";

   unsigned int a, b;
   std::cin >> a >> b;

   std::cout
      << "rec gcd(" << a << ", " << b << ")="
      << gcd(a, b) << std::endl;

   std::cout
      << "    gcd(" << a << ", " << b << ")="
      << gcd2(a, b) << std::endl;
	  */
}
*/
