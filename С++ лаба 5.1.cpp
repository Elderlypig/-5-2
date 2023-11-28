#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

class Employee {
public:
    std::string name;
    int department;
    std::string position;
    std::chrono::system_clock::time_point start_date;

    Employee(std::string name, int department, std::string position, std::chrono::system_clock::time_point start_date) {
        this->name = name;
        this->department = department;
        this->position = position;
        this->start_date = start_date;
    }
};

std::vector<Employee> getLongServingEmployees(int department, const std::vector<Employee>& employees) {
    std::vector<Employee> long_serving_employees;
    auto today = std::chrono::system_clock::now();
    for (const auto& employee : employees) {
        if (employee.department == department) {
            auto years_of_service = std::chrono::duration_cast<std::chrono::duration<int, std::ratio<31556952>>>(today - employee.start_date).count();
            if (years_of_service > 20) {
                long_serving_employees.push_back(employee);
            }
        }
    }
    return long_serving_employees;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<Employee> employees = {
        Employee("Мохов Глеб Генадьевич", 1, "Менеджер", std::chrono::system_clock::now() - std::chrono::hours(24 * 365 * 20)),
        Employee("Прокуда Егор Михайлович", 2, "Разработчик", std::chrono::system_clock::now() - std::chrono::hours(24 * 365 * 10)),
        Employee("Зательмаер Николь Викторовна", 1, "Бухгалтер", std::chrono::system_clock::now() - std::chrono::hours(24 * 365 * 25)),
        Employee("Мороз Ксения Ивановна", 3, "Аналитик", std::chrono::system_clock::now() - std::chrono::hours(24 * 365 * 30))
    };

    std::vector<Employee> long_serving_employees = getLongServingEmployees(1, employees);

    // Запись данных в файл
    std::ofstream out("file.txt");
    for (const auto& employee : long_serving_employees) {
        out << employee.name << std::endl;
    }
    out.close();

    // Чтение данных из файла
    std::ifstream in("file.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << std::endl;
    }
    in.close();

    return 0;
}
