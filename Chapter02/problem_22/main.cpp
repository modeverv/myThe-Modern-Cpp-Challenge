#include <cmath>
#include <assert.h>

/*
 さまざまな温度単位のリテラル
 温度をよく使われる3つの単位、摂氏、華氏、ケルビンで表示できて、相互に単位変
 換ができる小さなライブラリを書きなさい。このライブラリでは、温度リテラルを摂氏
 は36.5_deg、華氏は97.7_f、ケルビンは309.65_Kと書き、これらの値で演算が行えて、
 相互に変換できるようにしなさい。
 */
// Traits
// https://qiita.com/rita0222/items/09e49723e3339ba5de24
// https://cpprefjp.github.io/reference/type_traits.html
/*

 */
bool are_equal(double const d1, double const d2, double const epsilon = 0.001)
{
   return std::fabs(d1 - d2) < epsilon;
}

namespace temperature
{
   enum class scale
   {
      celsius,
      fahrenheit,
      kelvin
   };

   template <scale S>
   class quantity
   {
      const double amount;
   public:
      constexpr explicit quantity(double const a) : amount(a) {}

      explicit operator double() const { return amount; }
   };

   template <scale S>
   inline bool operator==(quantity<S> const & lhs, quantity<S> const & rhs)
   {
      return are_equal(static_cast<double>(lhs), static_cast<double>(rhs));
   }

   template <scale S>
   inline bool operator!=(quantity<S> const & lhs, quantity<S> const & rhs)
   {
      return !(lhs == rhs);
   }

   template <scale S>
   inline bool operator< (quantity<S> const & lhs, quantity<S> const & rhs)
   {
      return static_cast<double>(lhs) < static_cast<double>(rhs);
   }

   template <scale S>
   inline bool operator> (quantity<S> const & lhs, quantity<S> const & rhs)
   {
      return rhs < lhs;
   }

   template <scale S>
   inline bool operator<=(quantity<S> const & lhs, quantity<S> const & rhs)
   {
      return !(lhs > rhs);
   }

   template <scale S>
   inline bool operator>=(quantity<S> const & lhs, quantity<S> const & rhs)
   {
      return !(lhs < rhs);
   }

   template <scale S>
   constexpr quantity<S> operator+(quantity<S> const &q1, quantity<S> const &q2)
   {
      return quantity<S>(static_cast<double>(q1) + static_cast<double>(q2));
   }

   template <scale S>
   constexpr quantity<S> operator-(quantity<S> const &q1, quantity<S> const &q2)
   {
      return quantity<S>(static_cast<double>(q1) - static_cast<double>(q2));
   }

   template <scale S, scale R>
   struct conversion_traits
   {
   //https://cpprefjp.github.io/lang/cpp11/defaulted_and_deleted_functions.html
   /*
    = deleteは、特殊関数の暗黙定義を明示的に禁止するための機能である。これは、コピーを禁止するクラスを定義するような場合に使用する：

    class X {
    public:
    // コピーは禁止するが、ムーブは許可する
    X(const X&) = delete;
    X& operator=(const X&) = delete;

    // 特殊メンバ関数を明示的に定義もしくはdeleteした場合、
    // それ以外の特殊メンバ関数は明示的に定義もしくはdefault宣言しなければ
    // 暗黙定義されない
    X(X&&) = default;
    X() = default;
    X& operator=(X&&) = default;
    };
    */
      static double convert(double const value) = delete;
   };

   template <>
   struct conversion_traits<scale::celsius, scale::kelvin>
   {
      static double convert(double const value)
      {
         return value + 273.15;
      }
   };

   template <>
   struct conversion_traits<scale::kelvin, scale::celsius>
   {
      static double convert(double const value)
      {
         return value - 273.15;
      }
   };

   template <>
   struct conversion_traits<scale::celsius, scale::fahrenheit>
   {
      static double convert(double const value)
      {
         return (value * 9) / 5 + 32;;
      }
   };

   template <>
   struct conversion_traits<scale::fahrenheit, scale::celsius>
   {
      static double convert(double const value)
      {
         return (value - 32) * 5 / 9;
      }
   };

   template <>
   struct conversion_traits<scale::fahrenheit, scale::kelvin>
   {
      static double convert(double const value)
      {
         return (value + 459.67) * 5 / 9;
      }
   };

   template <>
   struct conversion_traits<scale::kelvin, scale::fahrenheit>
   {
      static double convert(double const value)
      {
         return (value * 9) / 5 - 459.67;
      }
   };

   template <scale R, scale S>
   constexpr quantity<R> temperature_cast(quantity<S> const q)
   {
      return quantity<R>(conversion_traits<S, R>::convert(static_cast<double>(q)));
   }

   namespace temperature_scale_literals
   {
      constexpr quantity<scale::celsius> operator "" _deg(long double const amount)
      {
         return quantity<scale::celsius> {static_cast<double>(amount)};
      }

      constexpr quantity<scale::fahrenheit> operator "" _f(long double const amount)
      {
         return quantity<scale::fahrenheit> {static_cast<double>(amount)};
      }

      constexpr quantity<scale::kelvin> operator "" _k(long double const amount)
      {
         return quantity<scale::kelvin> {static_cast<double>(amount)};
      }
   }
}

int main()
{
   using namespace temperature;
   using namespace temperature_scale_literals;

   auto t1{ 36.5_deg };
   auto t2{ 79.0_f };
   auto t3{ 100.0_k };

   {
      auto tf = temperature_cast<scale::fahrenheit>(t1);
      auto tc = temperature_cast<scale::celsius>(tf);
      assert(t1 == tc);
   }

   {
      auto tk = temperature_cast<scale::kelvin>(t1);
      auto tc = temperature_cast<scale::celsius>(tk);
      assert(t1 == tc);
   }

   {
      auto tc = temperature_cast<scale::celsius>(t2);
      auto tf = temperature_cast<scale::fahrenheit>(tc);
      assert(t2 == tf);
   }

   {
      auto tk = temperature_cast<scale::kelvin>(t2);
      auto tf = temperature_cast<scale::fahrenheit>(tk);
      assert(t2 == tf);
   }

   {
      auto tc = temperature_cast<scale::celsius>(t3);
      auto tk = temperature_cast<scale::kelvin>(tc);
      assert(t3 == tk);
   }

   {
      auto tf = temperature_cast<scale::fahrenheit>(t3);
      auto tk = temperature_cast<scale::kelvin>(tf);
      assert(t3 == tk);
   }
}
