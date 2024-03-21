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
    std::cout << "Введіть кількість студентів: ";
    std::cin >> studentCount;

    std::vector<Student> students(studentCount);
    for (int i = 0; i < studentCount; ++i) {
        std::cout << "Введіть прізвище студента: ";
        std::cin >> students[i].surname;
        std::cout << "Введіть курс студента: ";
        std::cin >> students[i].course;
        std::cout << "Введіть спеціальність студента (0 - ComputerScience, 1 - Informatics, 2 - MathAndEconomics, 3 - PhysicsAndInformatics, 4 - LaborEducation): ";
        int specialty;
        std::cin >> specialty;
        students[i].specialty = static_cast<Specialty>(specialty);
        std::cout << "Введіть оцінку з фізики: ";
        std::cin >> students[i].physicsGrade;
        std::cout << "Введіть оцінку з математики: ";
        std::cin >> students[i].mathGrade;
        switch (students[i].specialty) {
        case ComputerScience:
            std::cout << "Введіть оцінку з програмування: ";
            std::cin >> students[i].programmingGrade;
            break;
        case Informatics:
            std::cout << "Введіть оцінку з чисельних методів: ";
            std::cin >> students[i].numericalMethodsGrade;
            break;
        default:
            std::cout << "Введіть оцінку з педагогіки: ";
            std::cin >> students[i].pedagogyGrade;
            break;
        }
    }

    return students;
}

void printStudents(const std::vector<Student>& students) {
    std::cout << "№\tПрізвище\tКурс\tСпеціальність\tФізика\tМатематика\tІнформатика/Програмування/Чисельні методи/Педагогіка\n";
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

    std::cout << "Кількість студентів, які вчаться на “відмінно”: " << countExcellentStudents(students) << '\n';
    std::cout << "Процент студентів, які отримали з фізики оцінку “5”: " << calculatePhysics5Percentage(students) << "%\n";

    return 0;
}
