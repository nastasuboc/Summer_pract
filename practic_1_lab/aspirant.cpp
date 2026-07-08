#include "aspirant.h"

Aspirant::Aspirant(const std::string& Name, int Age, int Course,
                   const std::string& Group, const std::string& Diplom)
    : Student(Name, Age, Course, Group), diplom(Diplom)
{
}

void Aspirant::toString(std::string& out) const
{
    out = "Аспирант:\n";
    out += "Имя: " + name + "\n";
    out += "Возраст: " + std::to_string(age) + "\n";
    out += "Курс: " + std::to_string(course) + "\n";
    out += "Группа: " + group + "\n";
    out += "Диплом: " + diplom + "\n";
}
