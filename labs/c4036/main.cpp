#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>

using namespace std;

struct Student {
    string name;
    int score;
};

int main() {
    int n;
    cin >> n;

    vector<Student> students(n);
    for (int i = 0; i < n; ++i) {
        cin >> students[i].name >> students[i].score;
    }

    vector<Student> qualified;
    int index = 0;

/*
    //------------------------(기존_방식)--------------------------------//
    vector<Student> vec;
    for (int i = 0; i < n; i++)
    {
        Student s;
        cin >> s.name >>s.score;
        vec.push_back(s);
    }

    auto compareStudents = [](const Student& lhs, const Student& rhs) { return lhs.score < rhs.score; };

    // //------------------------(효율적인_방식)--------------------------------//

    ranges::sort(vec, greater{}, &Student::score);
    auto result = vec 
                | views::filter([](auto s){return s.score>=90;}) 
                | views::take(3);*/

    // TODO: while 문으로 students를 검사하며 90점 이상인 학생만 qualified에 넣으세요.
    while (index < n)
    {    if (students[index].score >= 90)
        {
            qualified.push_back(students[index]);
        }
        index++;
    }
    // TODO: qualified를 점수 내림차순, 이름 오름차순으로 정렬하세요.
    ranges::sort(qualified, [](const Student& a, const Student& b) {
        if (a.score == b.score) {
            return a.name < b.name; // 점수가 같으면 이름 오름차순
        }
        return a.score > b.score; // 점수 내림차순
    });
    // TODO: qualified가 비어 있으면 None을 출력하고, 아니면 앞에서부터 최대 3명의 이름을 출력하세요.
    if (qualified.empty()) {
        cout << "None" << endl;
    } else {
        for (size_t i = 0; i < qualified.size() && i < 3; ++i) {
            cout << qualified[i].name << endl;
        }
    }
    // TODO: 필요하면 sort 또는 ranges::sort를 사용할 수 있습니다.

    return 0;
}
