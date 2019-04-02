#include <iostream>
#include <numeric>
#include <string>

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
 ディレクトリのサイズを計算する
 ディレクトリのサイズを再帰的に計算してバイト単位で返す関数を書きなさい。シン
 ボリックリンクはたどるかどうか指定できるようにしなさい。
 */
std::uintmax_t get_directory_size(
   fs::path const & dir,
   bool const follow_symlinks = false)
{
#ifdef USE_BOOST_FILESYSTEM
   auto iterator = fs::recursive_directory_iterator(
      dir,
      follow_symlinks ? fs::symlink_option::recurse : fs::symlink_option::none);
#else
   auto iterator = fs::recursive_directory_iterator(
      dir,
      follow_symlinks ? fs::directory_options::follow_directory_symlink : fs::directory_options::none);
#endif
//0ull ull unsigned long long
  //https://cpprefjp.github.io/lang/cpp11/long_long_type.html

   return std::accumulate(
      fs::begin(iterator), fs::end(iterator),
      0ull,
      [](std::uintmax_t const total,
         fs::directory_entry const & entry) {
      return total + (fs::is_regular_file(entry) ?
         fs::file_size(entry.path()) : 0);
   });
}

int main()
{
   std::string path;
   std::cout << "Path: ";
   std::cin >> path;
   std::cout << "Size: " << get_directory_size(path) << std::endl;
}
