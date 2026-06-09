#include "tools.h"

std::string normalize_newlines(std::string_view text) {
    std::string result;

    // TODO: "\r\n" 은 "\n" 하나로 바꾸세요.
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\r') {
            if (i + 1 < text.size() && text[i + 1] == '\n') {
                result += '\n';
                ++i; // Skip the next character since it's part of the "\r\n" sequence
            } else {
                result += '\n'; 
                // TODO: 단독 '\r' 도 '\n' 으로 바꾸세요.
            }
        } else {
            result += text[i]; 
            // TODO: 그 외 문자는 그대로 유지하세요.
        }
    }

    return result;
}

std::string visualize_invisible(std::string_view text) {
    std::string result;

    // TODO: 공백은 [SP], 탭은 [TAB], 줄바꿈은 [LF], 캐리지리턴은 [CR] 로 바꾸세요.
    for (char ch : text) {
        switch (ch) {
            case ' ':
                result += "[SP]";
                break;
            case '\t':
                result += "[TAB]";
                break;
            case '\n':
                result += "[LF]";
                break;
            case '\r':
                result += "[CR]";
                break;
            default:
            // TODO: 그 외 문자는 그대로 result 에 추가하세요.
                result += ch;
                break;
        }
    }

    return result;
}
