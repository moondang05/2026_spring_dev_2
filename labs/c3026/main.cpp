#include <algorithm>
#include <iostream>
#include <vector>

using std::ranges::sort;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> values(n);

    // TODO: n개의 정수를 입력받아 values에 저장하세요.
    for (int i = 0; i < n; i++)
    {
        std::cin>>values[i]; 
    }
    
    // TODO: std::sort를 사용해 values를 오름차순으로 정렬하세요.
    //sort(values); //like py...sorted(values);
    //1. 최신_마참내_드디어
    sort(values);
    //2. 옛날_방식
    std::sort(std::begin(values),std::end(values));
    //3. 이건_뭐더라
    std::ranges::sort(values);
    // TODO: 정렬된 결과를 공백으로 구분해 한 줄에 출력하세요.

    for (int v : values) {          //손에 좀 익혔음 좋겠다..
        std::cout << v<< " ";
    }
    return 0;
}
