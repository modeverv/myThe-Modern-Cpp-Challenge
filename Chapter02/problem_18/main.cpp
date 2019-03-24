#include <iostream>
#include <functional>

/*
 任意個数の引数を取る最小値関数
 任意個数の引数を取ることができて、その最小値を返す関数テンプレートを、比較
 にoperator<演算子を使って書きなさい。operator<の代わりに、引数として与えられ
 た2項比較関数を使う、この関数テンプレートの修正版も書きなさい。
 */
template <typename T>
T minimum(T const a, T const b) { return a < b ? a : b; }

template <typename T1, typename... T>
T1 minimum(T1 a, T... args)
{
   return minimum(a, minimum(args...));
}

template <class Compare, typename T>
T minimumc(Compare comp, T const a, T const b) { return comp(a, b) ? a : b; }

template <class Compare, typename T1, typename... T>
T1 minimumc(Compare comp, T1 a, T... args)
{
   return minimumc(comp, a, minimumc(comp, args...));
}

int main()
{
   auto x = minimum(5, 4, 2, 3);
   std::cout << x << std::endl;
   
   auto y = minimumc(std::less<>(), 3, 2, 1, 0);
   std::cout << y << std::endl;
}
