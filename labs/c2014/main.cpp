#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const int baseGold = 1000;
    const int itemCost = 4000;
    int minionGold = 0;

    cout << "Enter gold collected from minions: ";
    cin >> minionGold;

    int totalGold = baseGold + minionGold;
    float averageGold = static_cast<float>(totalGold) / 2.0f;

    cout << "Total Gold: " << totalGold << endl;
    cout << fixed << setprecision(2);
    cout << "Average Gold: " << averageGold << endl;
    if (totalGold >= itemCost)
    {
        cout << "Item Purchase Available" << endl;
    }
    else
    {
        cout << "More Gold Needed" << endl;
    }
    return 0;
}