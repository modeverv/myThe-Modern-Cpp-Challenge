#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <array>
#include <assert.h>

/*
 バイナリから文字列への変換
 与えられた範囲（range）の8ビット整数の配列またはベクトルを16進表記の文字列で
 返す関数を書きなさい。16進は大文字または小文字が使えるようにしなさい。次に入
 力と出力の例を示します。
 入力 { 0xBA, 0xAD, 0xF0, 0x0D } 出力 "BAADF00D"または"baadf00d"
 入力 { 1,2,3,4,5,6 } 出力 "010203040506"
 */
template <typename Iter>
std::string bytes_to_hexstr(Iter begin, Iter end, bool const uppercase = false)
{
   std::ostringstream oss;
   if(uppercase)
      oss.setf(std::ios_base::uppercase);
   for (; begin != end; ++begin)
      oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*begin);
   return oss.str();
}

template <typename C>
std::string bytes_to_hexstr(C const & c, bool const uppercase = false)
{
   return bytes_to_hexstr(std::cbegin(c), std::cend(c), uppercase);
}

int main()
{
   std::vector<unsigned char> v{ 0xBA, 0xAD, 0xF0, 0x0D };
   // https://cpprefjp.github.io/lang/cpp11/uniform_initialization.html
   // 一様初期化
   std::array<unsigned char, 6> a{{ 1,2,3,4,5,6 }};
   unsigned char buf[5] = {0x11, 0x22, 0x33, 0x44, 0x55};

   assert(bytes_to_hexstr(v, true) == "BAADF00D");
   assert(bytes_to_hexstr(a, true) == "010203040506");
   assert(bytes_to_hexstr(buf, true) == "1122334455");

   assert(bytes_to_hexstr(v) == "baadf00d");
   assert(bytes_to_hexstr(a) == "010203040506");
   assert(bytes_to_hexstr(buf) == "1122334455");
}
