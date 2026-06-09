#include <iostream>
#include <string>
#include <limits>
using namespace std;
int main()
{
    int studentCount = 0;
    int highest_score = -1;
    string highest_name;
    cin >> studentCount;

    if (studentCount <= 0)
        return -1;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //buffer에 남아있는 Enter키(='\n')를 제거하여 getline() 함수에 남아있던 buffer값 물리는걸 방지
    
    int sum = 0;

    for (int i = 0; i < studentCount; i++)
    {
        string name;
        int score;

        cin >> name >> score;

        sum += score;

        if (highest_score < score)
        {
            highest_score = score;
            highest_name = name;
        }
    }

    cout << "Average: " << (double)sum / studentCount << '\n';
    cout << "Highest: " << highest_name << " " << highest_score << '\n';
    // TODO: read each student's name and score, then print the average and top student.
    return 0;
}