#pragma once

#include <concepts>
#include <iterator>
#include <ranges>
#include <utility>

/**
 * =================================================================================
 * [학습 과제] C++20 / C++23 Concepts 및 Ranges를 활용한 Generic my_accumulate 구현
 * =================================================================================
 * 
 * 본 과제에서는 기존 C++98/11 스타일의 std::accumulate를 한 단계 더 발전시켜,
 * 최신 C++ 표준의 타입 제약 조건(Concepts)과 범위(Ranges) 아키텍처를 직접 설계해 봅니다.
 * 
 * [학습 목표]
 * 1. std::input_iterator와 std::sentinel_for의 관계 이해 및 제약 조건(Constraints) 적용
 * 2. std::ranges::input_range를 활용한 임의의 컨테이너(Range) 직접 바인딩
 * 3. 복사 비용을 극적으로 줄이는 이동 의미론(Move Semantics) 기반의 누적 연산 최적화
 * 4. constexpr 지시어를 통한 컴파일 타임 연산 수행 역량 확보
 * =================================================================================
 */

namespace modern {

/**
 * (1) 반복자(Iterator) + 센티넬(Sentinel) 기반 my_accumulate
 * 
 * [기능 정의]
 * - 시작 반복자 `begin`부터 끝을 가리키는 `end`까지 순회하며 `init` 값에 누적 연산을 수행합니다.
 * 
 * [제약 조건 (Concepts)]
 * - Iterator: 최소한 값을 읽을 수 있는 입력 반복자(`std::input_iterator`) 구조여야 합니다.
 * - Sentinel: Iterator와 동등성 비교가 가능한 종결자(`std::sentinel_for<Iterator>`)여야 합니다.
 *   (C++20부터는 물리적인 반복자 쌍뿐만 아니라, null-terminator처럼 반복자와 타입이 다른 센티넬도 지원합니다)
 * 
 * [최적화 힌트]
 * - 누적할 때 단순히 `init = init + *begin;`을 사용하면 무거운 타입(예: std::string, 빅인티저)의 경우
 *   매 루프마다 불필요한 임시 객체 복사가 일어납니다.
 * - 복사본을 최소화하고 메모리 자원을 재사용할 수 있도록 `std::move`를 활용해 보세요.
 * 
 * @param begin 입력 범위의 시작점 반복자
 * @param end   입력 범위의 종결점 센티넬
 * @param init  누적 연산의 초기값
 * @return      최종 누적 연산 완료 후의 결과값 (T 타입)
 */
template <std::input_iterator Iterator,
          std::sentinel_for<Iterator> Sentinel,
          typename T>
constexpr T my_accumulate(Iterator begin, Sentinel end, T init) {
    // ---------------------------------------------------------------------
    // TODO: 아래 주석의 가이드를 따라 알고리즘을 완성하세요.
    // ---------------------------------------------------------------------
    
    // 1. begin 반복자가 sentinel인 end에 도달할 때까지 루프를 수행합니다.
    // 2. 각 루프 단계에서:
    //    init = std::move(init) + *begin;  <-- 이동 의미론을 적용해 효율성을 높이세요.
    // 3. begin 반복자를 1 증가시킵니다 (++begin).
    // 4. 누적이 완료된 최종 결과인 init을 반환합니다.

    // (아래 줄을 지우고 여러분의 코드로 대체하세요.)
    for (; begin != end; ++begin) {
        init = std::move(init) + *begin;
    }

    
    return init;
}

/**
 * (2) Range(컨테이너) 기반 my_accumulate (얇은 래퍼 함수)
 * 
 * [기능 정의]
 * - `std::vector`나 `std::list`, 혹은 `std::views` 파이프라인 같은 Range 객체를 통째로 인자로 받아
 *   모든 원소의 합을 구합니다.
 * - 이 함수는 내부적으로 새롭게 알고리즘을 구현하지 않고, 위에서 작성한 
 *   (1)번 '반복자 + 센티넬' 버전의 `my_accumulate`를 호출하는 방식으로 작성해야 합니다.
 * 
 * [제약 조건 (Concepts)]
 * - Range: `std::ranges::input_range` 조건을 충족해야 합니다.
 * 
 * [구현 힌트]
 * - Range 객체 `r`로부터 반복자와 센티넬을 안전하게 획득하기 위해 C++20 ADL 지원 도구인
 *   `std::ranges::begin(r)`과 `std::ranges::end(r)`을 사용하세요.
 * - Range 객체가 우측값 참조(`Range&&`)로 넘어올 수 있으므로, 완벽한 전달(Perfect Forwarding) 개념을 고려하면 좋습니다.
 * 
 * @param r    합을 구할 대상 Range (컨테이너 혹은 뷰)
 * @param init 누적 연산의 초기값
 * @return     최종 누적 결과값
 */
template <std::ranges::input_range Range, typename T>
constexpr T my_accumulate(Range&& r, T init) {
    // ---------------------------------------------------------------------
    // TODO: 아래 주석의 가이드를 따라 (1)번 함수를 호출하도록 구현하세요.
    // ---------------------------------------------------------------------
    
    // 1. std::ranges::begin 및 std::ranges::end 함수를 사용해 r의 반복자와 센티넬을 얻습니다.
    // 2. 이미 정의된 modern::my_accumulate(begin, end, init)을 호출하고 그 결과를 즉시 리턴하세요.

    // (아래 줄을 지우고 여러분의 코드로 대체하세요.)
    return modern::my_accumulate(std::ranges::begin(r), std::ranges::end(r), std::move(init));
}

} // namespace modern