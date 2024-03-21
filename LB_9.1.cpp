#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

enum Specialty {
    ComputerScience,
    Informatics,
    MathAndEconomics,
    PhysicsAndInformatics,
    LaborEducation
};

struct Student {
    std::string surname;
    int course;
    Specialty specialty;
    int physicsGrade;
    int mathGrade;
    union {
        int programmingGrade;
        int numericalMethodsGrade;
        int pedagogyGrade;
    };
};

std::vector<Student> createStudents() {
    int studentCount;
    std::cout << "������ ������� ��������: ";
    std::cin >> studentCount;

    std::vector<Student> students(studentCount);
    for (int i = 0; i < studentCount; ++i) {
        std::cout << "������ ������� ��������: ";
        std::cin >> students[i].surname;
        std::cout << "������ ���� ��������: ";
        std::cin >> students[i].course;
        std::cout << "������ ������������ �������� (0 - ComputerScience, 1 - Informatics, 2 - MathAndEconomics, 3 - PhysicsAndInformatics, 4 - LaborEducation): ";
        int specialty;
        std::cin >> specialty;
        students[i].specialty = static_cast<Specialty>(specialty);
        std::cout << "������ ������ � ������: ";
        std::cin >> students[i].physicsGrade;
        std::cout << "������ ������ � ����������: ";
        std::cin >> students[i].mathGrade;
        switch (students[i].specialty) {
        case ComputerScience:
            std::cout << "������ ������ � �������������: ";
            std::cin >> students[i].programmingGrade;
            break;
        case Informatics:
            std::cout << "������ ������ � ��������� ������: ";
            std::cin >> students[i].numericalMethodsGrade;
            break;
        default:
            std::cout << "������ ������ � ���������: ";
            std::cin >> students[i].pedagogyGrade;
            break;
        }
    }

    return students;
}

void printStudents(const std::vector<Student>& students) {
    std::cout << "�\t�������\t����\t������������\tԳ����\t����������\t�����������/�������������/������� ������/���������\n";
    for (int i = 0; i < students.size(); ++i) {
        std::cout << i + 1 << '\t' << students[i].surname << '\t' << students[i].course << '\t' << students[i].specialty << '\t' << students[i].physicsGrade << '\t' << students[i].mathGrade << '\t';
        switch (students[i].specialty) {
        case ComputerScience:
            std::cout << students[i].programmingGrade;
            break;
        case Informatics:
            std::cout << students[i].numericalMethodsGrade;
            break;
        default:
            std::cout << students[i].pedagogyGrade;
            break;
        }
        std::cout << '\n';
    }
}

int countExcellentStudents(const std::vector<Student>& students) {
    int count = 0;
    for (const auto& student : students) {
        if (student.physicsGrade == 5 && student.mathGrade == 5 &&
            (student.specialty == ComputerScience ? student.programmingGrade == 5 :
                student.specialty == Informatics ? student.numericalMethodsGrade == 5 :
                student.pedagogyGrade == 5)) {
            ++count;
        }
    }
    return count;
}

double calculatePhysics5Percentage(const std::vector<Student>& students) {
    int count = 0;
    for (const auto& student : students) {
        if (student.physicsGrade == 5) {
            ++count;
        }
    }
    return 100.0 * count / students.size();
}

int main() {
    SetConsoleOutputCP(1251);
    auto students = createStudents();
    printStudents(students);

    std::cout << "ʳ������ ��������, �� ������� �� �������: " << countExcellentStudents(students) << '\n';
    std::cout << "������� ��������, �� �������� � ������ ������ �5�: " << calculatePhysics5Percentage(students) << "%\n";

    return 0;
}
