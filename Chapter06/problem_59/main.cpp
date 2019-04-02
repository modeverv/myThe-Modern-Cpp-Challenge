#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <random>
#include <algorithm>
#include <array>
#include <iomanip>
/*
 イタチプログラム
 Richard Dawkinsのイタチコンピュータシミュレーションを実装したプログラム（イ
 タチプログラム、https://en.wikipedia.org/wiki/Weasel_program参照）を書きなさい。
 ドーキンス自身の言葉では次のように説明されています（『盲目の時計職人』第3章 小さ
 な変化を累積する、訳文は中嶋他訳、早川書房からの引用）。
 プログラムに決定的な変更を施した上で、もう一度あのコンピュータのサルを用
 いて、ちょうど前と同じ28文字からなるでたらめな配列を選んでやってみよう。
 84 ■ 6 章 アルゴリズムとデータ構造
 （中略）この句は繰り返し複製を作るものの、その複写過程においてある確率で
 ランダム・エラーすなわち「突然変異」を起こす。コンピュータは、その突然変
 異を起こした意味のない句、つまりその元の句の「子（孫）」を検討し、たとえわ
 ずかであっても、あの目標の句、METHINKS IT IS LIKE A WEASEL（おれに
 はイタチのようにも見えるがな＊1
 ）に最もよく似ている句を選ぶ。
 *?
class weasel
{
   std::string target;
   std::uniform_int_distribution<> chardist;
   std::uniform_real_distribution<> ratedist;
   std::mt19937 mt;
   std::string const allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

public:
   weasel(std::string_view t) :
      target(t), 
      chardist(0, 26),
      ratedist(0, 100)
   {
      std::random_device rd;
      auto seed_data = std::array<int, std::mt19937::state_size> {};
      std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
      std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
      mt.seed(seq);
   }

   void run(int const copies)
   {
      auto parent = make_random();
      int step = 1;
      std::cout << std::left << std::setw(5) << std::setfill(' ') << step << parent << std::endl;

      do
      {
         std::vector<std::string> children;
         std::generate_n(
            std::back_inserter(children), 
            copies, 
            [parent, this]() {return mutate(parent, 5); });

         parent = *std::max_element(
            std::begin(children), std::end(children),
            [this](std::string_view c1, std::string_view c2) {return fitness(c1) < fitness(c2); });

         std::cout << std::setw(5) << std::setfill(' ') << step << parent << std::endl;
         step++;

      } while (parent != target);
   }

private:
   weasel() = delete;

   double fitness(std::string_view candidate)
   {
      int score = 0;
      for (size_t i = 0; i < candidate.size(); ++i)
      {
         if (candidate[i] == target[i])
            score++;
      }

      return score;
   }

   std::string mutate(std::string_view parent, double const rate)
   {
      std::stringstream sstr;
      for (auto const c : parent)
      {
         auto nc = ratedist(mt) > rate ? c : allowed_chars[chardist(mt)];
         sstr << nc;
      }

      return sstr.str();
   }

   std::string make_random()
   {
      std::stringstream sstr;
      for (size_t i = 0; i < target.size(); ++i)
      {
         sstr << allowed_chars[chardist(mt)];
      }
      return sstr.str();
   }
};

int main()
{
   weasel w("METHINKS IT IS LIKE A WEASEL");
   w.run(100);
}
