#include <fstream>
#include <string>
#include <iostream>

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
 テキストファイルから空行を取り除く
 テキストファイルへのパスが与えられると、そのファイルから空行をすべて取り除く
 関数を書きなさい。空白のみの行は空行とみなします。
 */

void remove_empty_lines(fs::path filepath)
{
   std::ifstream filein(filepath.native(), std::ios::in);
   if (!filein.is_open())
      throw std::runtime_error("cannot open input file");

  //https://cpprefjp.github.io/reference/filesystem/temp_directory_path.html
   //https://cpprefjp.github.io/reference/filesystem/path.html
   //https://cpprefjp.github.io/reference/filesystem/path/op_append.html
   auto temppath = fs::temp_directory_path() / "temp.txt";
  std::cout << temppath << std::endl;
   std::ofstream fileout(temppath.native(), std::ios::out | std::ios::trunc);
   if (!fileout.is_open())
      throw std::runtime_error("cannot create temporary file");

   std::string line;
   while (std::getline(filein, line))
   {
      if (line.length() > 0 &&
         line.find_first_not_of(' ') != line.npos)
      {
         fileout << line << '\n';
         std::cout << line << std::endl;
      }
   }

   filein.close();
   fileout.close();

   fs::remove(filepath);
   fs::rename(temppath, filepath);
}

int main()
{
   remove_empty_lines("/Users/seijiro/Downloads/sample34.txt");
}
