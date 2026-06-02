#pragma once

// =========================================================================
// [현재 방식 / C++17] my_accumulate
//
//   begin 부터 end 직전까지 반복자로 순회하면서, 각 원소를 init 에 더한
//   최종 누적값을 반환하는 함수 템플릿을 작성하세요.
//
//   - 함수 시그니처(템플릿 매개변수, 반환 타입, 인자 이름)는 그대로 유지합니다.
//   - 반복문은 반복자(it) 를 ++ 로 한 칸씩 옮기는 형태로 작성합니다.
//   - std::accumulate 같은 표준 알고리즘을 호출하지 않습니다.
// =========================================================================
template <typename Iterator, typename T>
T my_accumulate(Iterator begin, Iterator end, T init) {
    // TODO: begin 부터 end 직전까지 순회하며 init 에 값을 누적하고
    //       최종 누적값을 반환하세요.

    T result = init;

    for (Iterator it = begin; it != end; ++it) {
        result += *it;
    }
    
    return result;
}
