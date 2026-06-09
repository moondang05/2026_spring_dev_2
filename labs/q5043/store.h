#pragma once
#include <string>

// store.cpp 에 구현하세요.
// 재고 목록은 store.cpp 내부의 static 변수로 관리됩니다.
bool has_item(const std::string& item);
void restock(const std::string& item, int qty);
bool sell(const std::string& item, int qty);
void set_stock(const std::string& item, int qty);
void remove_item(const std::string& item);
int stock_qty(const std::string& item);
void print_inventory();
