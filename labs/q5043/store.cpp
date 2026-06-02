#include "store.h"
#include <map>
#include <iostream>

// TODO: 아래 일곱 함수를 구현하세요.
// 재고 목록은 아래 static 변수로 관리합니다. 함수 파라미터로 전달하지 않습니다.
static std::map<std::string, int> inv;

bool has_item(const std::string& item) {
    // item 이 재고 목록에 있으면 true 를 반환합니다.
    // 힌트: inv.count(item) 을 사용하세요.
    // 다른 함수에서 이 함수를 호출하면 중복 코드를 줄일 수 있습니다.
    return inv.count(item) > 0;
}

void restock(const std::string& item, int qty) {
    // 기존 재고에 qty 만큼 추가합니다. 새 상품이면 qty 로 등록합니다.
    // 힌트: inv[item] 은 처음 접근 시 0 으로 초기화됩니다.
    inv[item] += qty;
}

bool sell(const std::string& item, int qty) {
    // 재고가 qty 이상이면 qty 만큼 차감하고 true 를 반환합니다.
    // 상품이 없거나 재고가 부족하면 아무 것도 하지 않고 false 를 반환합니다.
    if (has_item(item) && inv[item] >= qty) {
    inv[item] -= qty;
    return true;
    }
    return false;
}

void set_stock(const std::string& item, int qty) {
    // 재고 조사 후 수량을 qty 로 정정합니다 (덮어쓰기).
    inv[item] = qty;
}

void remove_item(const std::string& item) {
    // 상품을 단종 처리합니다 (목록에서 완전히 삭제).
    inv.erase(item);
}

int stock_qty(const std::string& item) {
    // item 의 재고 수량을 반환합니다. 없으면 -1 을 반환합니다.
    // 주의: inv[item] 을 직접 쓰면 없는 항목이 0 으로 생성됩니다.
    return inv.count(item) > 0 ? inv[item] : -1;
}

void print_inventory() {
    // 재고 목록을 이름 오름차순으로 "이름 수량" 형식으로 한 줄씩 출력합니다.
    for (const auto& [name, qty] : inv) {
        std::cout << name << " " << qty << '\n';
    }
}
