#include <iostream>
#include <random>
#include <algorithm>
#include <array>

/*
 πの計算
 π（円周率、PIと書く）の値を小数第2位までの精度で計算するプログラムを書きな
 さい。
 */
template <
   typename E = std::mt19937, 
   typename D = std::uniform_real_distribution<>>
double compute_pi(E& engine, D& dist,
   int const samples = 1000000)
{
   auto hit = 0;

   for (auto i = 0; i<samples; i++)
   {
      auto x = dist(engine);
      auto y = dist(engine);

      if (y <= std::sqrt(1 - std::pow(x, 2))) hit += 1;
   }

   return 4.0 * hit / samples;
}

int main()
{
   std::random_device rd;
   auto seed_data = std::array<int, std::mt19937::state_size> {};
   std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
   std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
   auto eng = std::mt19937{ seq };
   auto dist = std::uniform_real_distribution<>{ 0, 1 };
   // ref https://cpprefjp.github.io/reference/random/uniform_real_distribution.html

   for (auto j = 0; j < 10; j++)
   {
      std::cout << compute_pi(eng, dist,1000000) << std::endl;
   }
   /*
    3.14326
    3.14354
    3.1405
    3.14231
    3.13933
    3.14252
    3.14007
    3.13896
    3.14125
    3.14152
    */
}
