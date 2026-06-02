#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <ranges>

using namespace std;
int main() {
    int n;
    cin >> n;

    istream_iterator<int> is(cin);
    vector<int> vec;
    copy_n(is, n, back_insert_iterator(vec));

    sort(begin(vec), end(vec));

    ostream_iterator<int> os(cout, "\n");
    copy(vec.begin(), vec.end(), os);

    //------------------------(기존_방식)--------------------------------//

    // auto res = views::istream<int>(cin) 
    //          | views::take(n) 
    //          | ranges::to<vector<int>>();

    // ranges::sort(res);
    // ranges::copy(res, os);


    // vec.reserve(n);

    // TODO: copy_n 과 istream_iterator<int> 로 n개의 정수를 읽으세요.
    // TODO: 정렬한 뒤 copy 와 ostream_iterator<int> 로 한 줄에 하나씩 출력하세요.

    return 0;
}
