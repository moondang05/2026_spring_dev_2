#ifndef RANGE_HPP
#define RANGE_HPP

class Range {
private:
    long long start_;   // 시작 값 (포함)
    long long stop_;    // 종료 값 (미포함)
    long long step_;    // 증감 폭

public:
    // Python 의 range() 처럼 중첩 Iterator 클래스를 정의합니다.
    class Iterator {
    private:
        long long current_;
        long long step_;
        long long stop_;

    public:
        Iterator(long long current, long long step, long long stop);

        // TODO: 아래 5 개 연산자를 구현하세요 (Range.cpp).
        long long operator*() const;              // 현재 값 반환
        Iterator& operator++();                   // 전위 증가
        Iterator  operator++(int);                // 후위 증가
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
    };

    explicit Range(long long stop);                              // range(stop)
    Range(long long start, long long stop);                      // range(start, stop)
    Range(long long start, long long stop, long long step);      // range(start, stop, step)

    [[nodiscard]] Iterator begin() const;
    [[nodiscard]] Iterator end()   const;
};

#endif // RANGE_HPP
