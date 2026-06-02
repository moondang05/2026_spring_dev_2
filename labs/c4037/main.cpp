#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
    int n;
    cin >> n;

    map<string  /*key_values*/, int /*values*/> counts;


    for (int i = 0; i < n; i++)
    {
        string name;
        cin >> name;
        //효율적 방법
        ++counts[name];

        //정석적인 방법
            // if(counts.find(name)!=counts.end()) {
            //     counts[name] += 1;
            // }
            // else {
            //     counts[name] = 1;
            // }
    }

    for (auto [k, v] : counts) 
    {
        cout << k << " " << v << "\n";
    }
    
    
    // TODO: 단어 n개를 입력받아 counts[word] 를 증가시키세요.
    // TODO: for 문으로 map 을 순회하며 "단어 개수" 형식으로 출력하세요.

    return 0;
}
