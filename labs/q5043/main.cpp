#include "store.h"
#include <iostream>
#include <string>

// main 함수는 미리 작성되어 있습니다. 수정하지 마세요.
// store.cpp 에 일곱 함수를 구현하세요.
//
// 입력 형식:
//   q                    → 명령 수
//   RESTOCK <item> <qty> → 기존 수량에 qty 추가 (없으면 새로 등록)
//   SELL    <item> <qty> → qty 만큼 판매 (성공 시 OK, 실패 시 FAIL)
//   SET     <item> <qty> → 재고 조사 후 수량을 qty 로 정정
//   REMOVE  <item>       → 상품 단종 (목록에서 완전 삭제)
//   HAS     <item>       → 재고 목록에 있으면 YES, 없으면 NO 출력
//   STOCK   <item>       → 재고 수량 출력 (없으면 -1)
// 모든 명령 처리 후 재고 목록을 이름 오름차순으로 한 줄씩 출력합니다.

int main() {
    int q;
    std::cin >> q;
    while (q--) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "RESTOCK") {
            std::string item; int qty;
            std::cin >> item >> qty;
            restock(item, qty);
        } else if (cmd == "SELL") {
            std::string item; int qty;
            std::cin >> item >> qty;
            std::cout << (sell(item, qty) ? "OK" : "FAIL") << '\n';
        } else if (cmd == "SET") {
            std::string item; int qty;
            std::cin >> item >> qty;
            set_stock(item, qty);
        } else if (cmd == "REMOVE") {
            std::string item;
            std::cin >> item;
            remove_item(item);
        } else if (cmd == "HAS") {
            std::string item;
            std::cin >> item;
            std::cout << (has_item(item) ? "YES" : "NO") << '\n';
        } else {  // STOCK
            std::string item;
            std::cin >> item;
            std::cout << stock_qty(item) << '\n';
        }
    }
    print_inventory();
    return 0;
}
