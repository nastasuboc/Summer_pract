#include "student.h"

Student::Student(const std::string& Name, int Age, int Course, const std::string& Group)
    : AbstractHuman(Name, Age), course(Course), group(Group)
{
}

void Student::toString(std::string& out) const
{
    out = "Студент:\n";
    out += "Имя: " + name + "\n";
    out += "Возраст: " + std::to_string(age) + "\n";
    out += "Курс: " + std::to_string(course) + "\n";
    out += "Группа: " + group + "\n";
}
