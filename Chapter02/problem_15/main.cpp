#include <iostream>
#include <array>
#include <sstream>
#include <assert.h>

/*
 IPv4データ型
 IPv4アドレスを表すクラスを書きなさい。IPv4アドレスをキーボードから入力
 し、ディスプレイに出力するのに必要な関数を書きなさい。ユーザは、127.0.0.1や
 168.192.0.100のようにドット形式で入力できなければなりません。これは、出力に使
 う形式でもあります。
 */

class ipv4
{
   // https://cpprefjp.github.io/reference/array/array.html
   std::array<unsigned char, 4> data;
public:
   //https://qiita.com/saltheads/items/dd65935878a0901fe9e7
   // constructor 1
   // https://cpprefjp.github.io/lang/cpp11/uniform_initialization.html
  // X x4 = {0};をやってる 0の部分が{0,2,2}
   constexpr ipv4() :data{ {0} } {}
   // constructor 2
   constexpr ipv4(unsigned char const a, unsigned char const b,
                  unsigned char const c, unsigned char const d):
   data{{a,b,c,d}} {}
   // longが渡された時のコンストラクタ
   // https://cpprefjp.github.io/lang/cpp11/explicit_conversion_operator.html
   explicit constexpr ipv4(unsigned long a) :
      data{ { static_cast<unsigned char>((a >> 24) & 0xFF), 
              static_cast<unsigned char>((a >> 16) & 0xFF),
              static_cast<unsigned char>((a >> 8) & 0xFF),
              static_cast<unsigned char>(a & 0xFF) } } {}



  ipv4(ipv4 const & other) noexcept : data(other.data) {}

  // 代入演算子のオーバーロード
  // なぜ必要なのか今の私にはわからない
  // https://qiita.com/rinse_/items/9d87d5cb0dc1e89d005e
  ipv4& operator=(ipv4 const & other) noexcept
   {
      data = other.data;
      return *this;
   }

   // to_string
   std::string to_string() const
   {
      // https://www.sejuku.net/blog/51234
      std::stringstream sstr;
      sstr << *this;
      return sstr.str();
   } 
   // https://cpprefjp.github.io/reference/bitset/bitset/to_ulong.html
   constexpr unsigned long to_ulong() const noexcept
   {
      return
         (static_cast<unsigned long>(data[0]) << 24) |
         (static_cast<unsigned long>(data[1]) << 16) |
         (static_cast<unsigned long>(data[2]) << 8) |
         static_cast<unsigned long>(data[3]);
   }

   // 出力をオーバーロードしてる
   friend std::ostream& operator<<(std::ostream& os, const ipv4& a)
   {
      os << static_cast<int>(a.data[0]) << '.' 
         << static_cast<int>(a.data[1]) << '.'
         << static_cast<int>(a.data[2]) << '.'
         << static_cast<int>(a.data[3]);
      return os;
   }

   // 入力をオーバーロードしている
   friend std::istream& operator>>(std::istream& is, ipv4& a)
   {
      char d1, d2, d3;
      int b1, b2, b3, b4;
      is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
      if (d1 == '.' && d2 == '.' && d3 == '.')
         a = ipv4(b1, b2, b3, b4);
      else
         is.setstate(std::ios_base::failbit);

      return is;
   }
};

int main()
{
  std::stringstream ss;

  std::string str = "samurai engineer programmer";

  std::string output;

  ss << str;

  ss >> output;

  std::cout << "元の文字列：" << str << "\n";
  std::cout << "抽出：" << output << "\n";



   ipv4 a(168, 192, 0, 1);
   std::cout << a << std::endl;
   std::cout << a.to_string() << std::endl;
/*
   ipv4 b = a;
   ipv4 c;
   c = b;

   ipv4 ip;
   std::cout << ip << std::endl;
   std::cin >> ip;
   if(!std::cin.fail())
      std::cout << ip << std::endl;
*/
}
