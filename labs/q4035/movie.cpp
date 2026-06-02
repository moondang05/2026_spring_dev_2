#include "movie.h"
#include <string>
#include <iostream>

// TODO: genreToString을 구현하세요.
std::string genreToString(Genre genre) {    
    if (Genre::Action == genre)
    {
        return "Action";
    }
    else if (Genre::Drama == genre)
    {
        return "Drama";
    }
    else if (Genre::SciFi == genre)
    {
        return "SciFi";
    }
    return "Unknown";
}
// TODO: stringToGenre를 구현하세요.

// TODO: 별점 문자열에서 검은 별(★) 개수를 세어 정수로 반환하세요.

// TODO: addRating에서 제목별 장르와 평점을 저장하세요.

// TODO: printSummary에서 제목 알파벳 순으로
// "제목: N ratings, average rating M stars, genre: 장르"
// 형식의 요약을 출력하세요.