#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <string_view>
#include <functional>

#ifdef USE_BOOST_FILESYSTEM
#  include <boost/filesystem/path.hpp>
#  include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;
#else
#  include <filesystem>
#  ifdef FILESYSTEM_EXPERIMENTAL
namespace fs = std::experimental::filesystem;
#  else
namespace fs = std::filesystem;
#  endif
#endif

/*
 ディレクトリ内で正規表現にマッチするファイルを見つける
 ディレクトリへのパスと正規表現が与えられたときに、名前が正規表現にマッチする
 すべてのエントリのリストを返す関数を書きなさい。
 */

std::vector<fs::directory_entry> find_files(
   fs::path const & path,
   std::string_view regex)
{
   std::vector<fs::directory_entry> result;
   std::regex rx(regex.data());
//https://cpprefjp.github.io/reference/algorithm/copy_if.html
   std::copy_if(
      fs::recursive_directory_iterator(path),
//https://cpprefjp.github.io/reference/filesystem/recursive_directory_iterator.html
//https://ja.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
// 無指定なのでファイルシステムの最後の要素までのイテレーターになるのかな。
//
    fs::recursive_directory_iterator(),
                //https://cpprefjp.github.io/reference/iterator/back_inserter.html
      std::back_inserter(result),
      [&rx](fs::directory_entry const & entry) {
         return fs::is_regular_file(entry.path()) &&
                std::regex_match(entry.path().filename().string(), rx);
      });
/*
 あるあるの処理らしい
 挿入イテレータはアルゴリズム系のテンプレート関数との組み合わせでよく使われます。有名な活用例としては、copy関数を応用した コンテナ要素の追加処理 等が挙げられます。

 std::vector<int> v = {1, 2, 3};
 std::vector<int> w = {4, 5, 6};
 std::copy(w.begin(), w.end(), std::back_inserter(v));
 // v == {1, 2, 3, 4, 5, 6}
 https://marycore.jp/prog/cpp/insert-inserters/
 */
   return result;
}

int main()
{
   auto dir = fs::temp_directory_path();
   auto pattern = R"(wct[0-9a-zA-Z]{3}\.tmp)";
   auto result = find_files(dir, pattern);

   for (auto const & entry : result)
   {
      std::cout << entry.path().string() << std::endl;
   }
}
