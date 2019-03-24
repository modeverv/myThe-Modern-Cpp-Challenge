#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>

/*
 素因数分解
 与えられた正の整数の素因数分解を出力するプログラムを書きなさい。
 */
// ref long long https://cpprefjp.github.io/lang/cpp11/long_long_type.html

std::vector<unsigned long long> prime_factors(unsigned long long n)
{
   std::vector<unsigned long long> factors;
   // print the number of 2s that divide n
   while (n % 2 == 0)
   {
      factors.push_back(2);
      n = n / 2;
   }

   for (unsigned long long i = 3; i <= std::sqrt(n); i += 2)
   {
      // while i divides n, print i and divide n
      while (n%i == 0)
      {
         factors.push_back(i);
         n = n / i;
      }
   }

   // n is a prime number greater than 2
   if (n > 2)
      factors.push_back(n);

   return factors;
}

int main()
{
   unsigned long long number = 0;
   std::cout << "number:";
   std::cin >> number;

   auto factors = prime_factors(number);

   std::copy(
      std::begin(factors), std::end(factors),
      std::ostream_iterator<unsigned long long>(std::cout, " "));
   //https://cpprefjp.github.io/reference/iterator/ostream_iterator.html
}
