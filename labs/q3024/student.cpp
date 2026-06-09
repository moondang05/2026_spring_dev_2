#include "student.h"
#include <vector>
std::array<Student, STUDENT_COUNT> init_students() {
    return {{
        {1, "Choi", 9.9},
        {2, "Park", 0.1},
        {3, "Kim", 5.0},
        {4, "Lee", 3.0},
        {5, "Moon", 9.5},
        {6, "Kang", 7.0},
        {7, "Jeon", 0.9}
    }};
}

const Student& get_last(const std::array<Student, STUDENT_COUNT>& students) {
    // TODO: 마지막 학생을 반환하세요.
    return students[STUDENT_COUNT - 1];
}

std::string compare_points(const Student& s1, const Student& s2) {
    // TODO: 점수를 비교해 의미 있는 문장을 반환하세요.
    if (s1.points > s2.points) {
        return s1.name + " has more points than " + s2.name + ".";
    } else if (s1.points < s2.points) {
        return s2.name + " has more points than " + s1.name + ".";
    }
    return s1.name + " and " + s2.name + " have the same points.";
}

const Student& get_lowest_points(const std::array<Student, STUDENT_COUNT>& students) {
    // TODO: 가장 낮은 점수의 학생을 찾아 반환하세요.
    double lowest_points = students[0].points;
    double lowest_id = students[0].id;
    for (const auto& s : students) {
        if (s.points <= lowest_points) {
            lowest_points = s.points;
            lowest_id = s.id;
        }
    }
    return students[(int)lowest_id-1];
}

const Student& get_highest_points(const std::array<Student, STUDENT_COUNT>& students) {
    // TODO: 가장 높은 점수의 학생을 찾아 반환하세요.
    double highest_points = students[0].points;
    for (const auto& s : students) {
        if (s.points > highest_points) {
            highest_points = s.points;
        }
    }
    return students[0];
}

void my_sort(std::array<Student, STUDENT_COUNT>& students) {
    // TODO: points 오름차순으로 정렬하세요.
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.points < b.points;
    });
    (void)students;
}

void print(const Student& s) {
    std::cout << "ID: " << s.id
              << ", Name: " << s.name
              << ", Points: " << s.points << '\n';
}



