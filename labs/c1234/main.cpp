#include <iostream>
#include <iomanip>
#include <cmath> // round 함수 사용을 위해 추가
using namespace std;

int main() {
    // 가격을 float 대신 센트(int) 단위로 관리하여 부동소수점 오차를 방지합니다.
    const int BANANA_PRICE_CENTS = 530; // $5.30
    const int APPLE_PRICE_CENTS = 320;  // $3.20
    const int ORANGE_PRICE_CENTS = 240; // $2.40

    int banana_quantity = 0;
    int apple_quantity = 0;
    int orange_quantity = 0;

    int total_price_cents = 0;
    float received_money = 0;
    int received_money_cents = 0;
    int change_cents = 0;

    cout << "Enter the quantity of each fruit(banana, apple, orange)"<< endl;
    cin >> banana_quantity >> apple_quantity >> orange_quantity;

    total_price_cents = BANANA_PRICE_CENTS * banana_quantity + APPLE_PRICE_CENTS * apple_quantity + ORANGE_PRICE_CENTS * orange_quantity;
    
    // 사용자에게는 달러 단위로 보여줍니다.
    cout << fixed << setprecision(2);
    cout << "Total price: $" << total_price_cents / 100.0 << endl;

    cout << "Pay your charge."<<endl;
    cin >> received_money;

    // 받은 돈도 센트로 변환합니다. round를 사용하여 반올림 오차를 최소화합니다.
    received_money_cents = round(received_money * 100);

    // 지불한 금액이 부족할 경우, 충분한 금액을 받을 때까지 추가 결제를 요청합니다.
    while (received_money_cents < total_price_cents) {
        double needed_amount = (total_price_cents - received_money_cents) / 100.0;
        cout << "Not enough money. You need to pay $" << needed_amount << " more." << endl;
        cout << "Pay your extra charge." << endl;
        
        float extra_charge = 0;
        cin >> extra_charge;
        received_money_cents += round(extra_charge * 100);
    }

    change_cents = received_money_cents - total_price_cents;

    cout << "Thank you for your payment. ";

    if (change_cents == 0) {
        cout << "No change." << endl;
    } else {
        cout << "Here's your change: ";
        int change_dollar = change_cents / 100;
        int remaining_cents = change_cents % 100;
        int change_quarter = remaining_cents / 25;
        int change_cent = remaining_cents % 25;

        bool needs_separator = false;

        if (change_dollar > 0) {
            cout << "$" << change_dollar;
            needs_separator = true;
        }
        if (change_quarter > 0) {
            if (needs_separator) cout << " and ";
            cout << change_quarter << (change_quarter > 1 ? " quarters" : " quarter");
            needs_separator = true;
        }
        if (change_cent > 0) {
            if (needs_separator) cout << " and ";
            cout << change_cent << (change_cent > 1 ? " cents" : " cent");
        }
        cout << "." << endl;
    }

    return 0;
}