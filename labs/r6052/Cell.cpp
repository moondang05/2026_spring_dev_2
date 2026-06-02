#include "Cell.h"
#include <iomanip>
#include <sstream>
#include <format>

Cell::Cell() : type_{CellType::STRING}, stringVal_{""}, intVal_{0}, doubleVal_{0.0} {}

// TODO: 아래 생성자와 멤버 함수를 구현하세요.

Cell::Cell(const std::string val) {
    // 문자열 값을 저장하는 생성자
    // type_ 을 STRING 으로 설정하세요.
    type_ = CellType::STRING;
    stringVal_ = val;
    intVal_ = 0;
    doubleVal_ = 0.0;
}

Cell::Cell(int val) {
    // 정수 값을 저장하는 생성자
    // type_ 을 INT 로 설정하세요.
    type_ = CellType::INT;
    intVal_ = val;
    stringVal_ = "";
    doubleVal_ = 0.0;
}

Cell::Cell(double val) {
    // 실수 값을 저장하는 생성자
    // type_ 을 DOUBLE 로 설정하세요.
    type_ = CellType::DOUBLE;
    doubleVal_ = val;
    stringVal_ = "";
    intVal_ = 0;
}

bool Cell::isNumeric() const {
    // INT 또는 DOUBLE 이면 true 를 반환합니다.
    return type_ == CellType::INT || type_==CellType::DOUBLE;
}

bool Cell::isString() const {
    // STRING 이면 true 를 반환합니다.
    return type_ == CellType::STRING; 
}

double Cell::getNumericValue() const {
    // INT 이면 intVal_ 을 double 로, DOUBLE 이면 doubleVal_ 을 반환합니다.
    // STRING 이면 0.0 을 반환합니다.
    return (type_==CellType::INT) ? static_cast<double>(intVal_)
          :(type_==CellType::STRING) ? 0.0
          :doubleVal_;
}

std::string Cell::toString() const {
    // STRING 이면 stringVal_ 을 그대로 반환합니다.
    // INT 이면 정수를 문자열로 변환합니다 (예: 87 → "87").
    // DOUBLE 이면 소수점 1자리로 변환합니다 (예: 75.7 → "75.7").
    // 힌트: std::ostringstream + std::fixed + std::setprecision(1)
    return (type_==CellType::STRING) ? stringVal_
          :(type_==CellType::INT) ? std::format("{}", intVal_)
          :std::format("{:.1f}", doubleVal_);
}
