#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

/*
 優先度付きキュー
 優先度付きキューを表すデータ構造を書きなさい。優先度が最大の要素の取得が定
 数時間に、要素の追加削除が対数時間計算量になるようにしなさい。キューは新たな
 要素を末尾に挿入し、先頭から要素を削除します。デフォルトでは、キューは要素を比
 較するためにoperator<を用いますが、第1引数が第2引数より小さいとtrueを返す比
 較関数オブジェクトをユーザが与えることができるようにしなさい。実装では、少なく
 とも次の操作ができなければなりません。
 ● push()：新たな要素の追加
 ● pop()：先頭要素の削除
 ● top()：先頭要素へのアクセス
 ● size()：キューにある要素の個数
 ● empty()：キューが空かどうか

 heap使うってよ
 */

template <class T,
   class Compare = std::less<typename std::vector<T>::value_type>>
   class priority_queue
{
   typedef typename std::vector<T>::value_type      value_type;
   typedef typename std::vector<T>::size_type       size_type;
   typedef typename std::vector<T>::reference       reference;
   typedef typename std::vector<T>::const_reference const_reference;
public:
   bool empty() const noexcept { return data.empty(); }
   size_type size() const noexcept { return data.size(); }

   void push(value_type const & value)
   {
      data.push_back(value);
      std::push_heap(std::begin(data), std::end(data), comparer);
   }

   void pop()
   {
      std::pop_heap(std::begin(data), std::end(data), comparer);
      data.pop_back();
   }

   const_reference top() const { return data.front(); }

   void swap(priority_queue& other) noexcept
   {
      swap(data, other.data);
      swap(comparer, other.comparer);
   }

private:
   std::vector<T> data;
   Compare comparer;
};

template< class T, class Compare>
void swap(
   priority_queue<T, Compare>& lhs,
   priority_queue<T, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
   lhs.swap(rhs);
}

int main()
{
   priority_queue<int> q;
   for (int i : {1, 5, 3, 1, 13, 21, 8})
   {
      q.push(i);
   }

   assert(!q.empty());
   assert(q.size() == 7);

   while (!q.empty())
   {
      std::cout << q.top() << ' ';
      q.pop();
   }
}
