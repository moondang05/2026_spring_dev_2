#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <string_view>

std::string normalize_newlines(std::string_view text);
std::string visualize_invisible(std::string_view text);

#endif
