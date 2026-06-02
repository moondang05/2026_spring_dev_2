#include "tools.h"
#include <iostream>
#include <string>
#include <string_view>

namespace {

std::string decode_escaped(std::string_view encoded) {
    std::string result;

    for (std::size_t index = 0; index < encoded.size(); ++index) {
        if (encoded[index] == '\\' && index + 1 < encoded.size()) {
            ++index;
            switch (encoded[index]) {
                case 'n':
                    result.push_back('\n');
                    break;
                case 'r':
                    result.push_back('\r');
                    break;
                case 't':
                    result.push_back('\t');
                    break;
                case '\\':
                    result.push_back('\\');
                    break;
                default:
                    result.push_back(encoded[index]);
                    break;
            }
        } else {
            result.push_back(encoded[index]);
        }
    }

    return result;
}

std::string escape_controls(std::string_view text) {
    std::string result;

    for (char ch : text) {
        switch (ch) {
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            case '\\':
                result += "\\\\";
                break;
            default:
                result.push_back(ch);
                break;
        }
    }

    return result;
}

} // namespace

int main() {
    std::string mode;
    std::string encoded;

    std::getline(std::cin, mode);
    std::getline(std::cin, encoded);

    const std::string text = decode_escaped(encoded);

    if (mode == "normalize") {
        std::cout << escape_controls(normalize_newlines(text)) << '\n';
    } else if (mode == "visualize") {
        std::cout << visualize_invisible(text) << '\n';
    } else {
        std::cout << "UNKNOWN MODE\n";
    }

    return 0;
}
