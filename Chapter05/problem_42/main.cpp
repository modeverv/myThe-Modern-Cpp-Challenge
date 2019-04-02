#include <iostream>
#include "date.h"
#include "iso_week.h"
/*
 年間の日と週
 与えられた日付が、1年の何日目か（1から365まで、うるう年は366まで）を返す関数
 と、同じ入力に対して1年の何週目かを返す関数を書きなさい。
 */
unsigned int calendar_week(int const y, unsigned int const m, unsigned int const d)
{
   using namespace date;
   
   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

   return (unsigned int)tiso.weeknum();
}

int day_of_year(int const y, unsigned int const m, unsigned int const d)
{
   using namespace date;
   
   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   return (sys_days{ year{ y } / month{ m } / day{ d } } -
      sys_days{ year{ y } / jan / 0 }).count();
}

int main()
{
   int y = 0;
   unsigned int m = 0, d = 0;
   std::cout << "Year:"; std::cin >> y;
   std::cout << "Month:"; std::cin >> m;
   std::cout << "Day:"; std::cin >> d;

   std::cout << "Calendar week:" << calendar_week(y, m, d) << std::endl;
   std::cout << "Day of year:" << day_of_year(y, m, d) << std::endl;
}
