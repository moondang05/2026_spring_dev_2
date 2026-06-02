#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// using std::ranges::transform;
// using std::ranges::count;


int countCharacter(const std::string& str, char ch) {
    // TODO: str에서 문자 ch가 몇 번 등장하는지 세어 반환하세요.
    int cnt = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if(str[i] == ch) {
            cnt++;
        }
    }
    
    return cnt;
    // return count(str, ch);
}

void toUpperCase(std::string& str) {
    // TODO: str의 모든 문자를 대문자로 바꾸세요.
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= 'a' && str[i] <='z') {
            str[i] -= 32;
        }
    }
    return;
}

bool startsWith(std::string_view str, std::string_view prefix) {
    // TODO: str이 prefix로 시작하면 true, 아니면 false를 반환하세요.
    int std = 0;
    for (int i = 0; i < prefix.length(); i++)
    {
        if (str[i] == prefix[i]) {
            std = 1;
        }
        else {
            std = 0;
            return false;
        }
    }
    if (std == 1) {
        return true;
    }

    // std::transform(str, begin(str), begin(str), [](auto& c){
    //     return std::toupper(c);
    // });
}

int main() {
    std::vector<std::string> words = {"hello", "world", "example"};

    char characterToCount = 'l';
    for (const auto& word : words) {
        std::cout << "Count of '" << characterToCount << "' in \"" << word << "\": "
                  << countCharacter(word, characterToCount) << '\n';
    }
    std::cout << '\n';

    for (auto& word : words) {
        toUpperCase(word);
        std::cout << "Modified string: " << word << '\n';
    }
    std::cout << '\n';

    std::string_view prefix = "EX";
    for (const auto& word : words) {
        std::cout << "Does \"" << word << "\" start with '" << prefix << "'? "
                  << (startsWith(word, prefix) ? "Yes" : "No") << '\n';
    }

    return 0;
}
