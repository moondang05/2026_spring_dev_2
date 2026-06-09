#ifndef MOVIE_H
#define MOVIE_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

enum class Genre {
    Action,
    Drama,
    SciFi,
};

std::string genreToString(Genre genre);
Genre stringToGenre(std::string_view text);
int starsToInt(std::string_view stars);

class MovieDatabase {
public:
    void addRating(const std::string& title, std::string_view genre_text, std::string_view stars);
    void printSummary() const;

private:
    std::map<std::string, Genre> genres_;
    std::map<std::string, std::vector<int>> ratings_;
};

#endif
