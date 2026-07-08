#include "worker.h"

Worker::Worker(const std::string& Name, int Age, int Stag,
               const std::string& Workplace, const std::string& Position, double Salary)
    : AbstractHuman(Name, Age), stag(Stag), workplace(Workplace),
    position(Position), salary(Salary)
{
}

void Worker::toString(std::string& out) const
{
    out = "Рабочий:\n";
    out += "Имя: " + name + "\n";
    out += "Возраст: " + std::to_string(age) + "\n";
    out += "Стаж: " + std::to_string(stag) + "\n";
    out += "Место работы: " + workplace + "\n";
    out += "Должность: " + position + "\n";
    out += "Зарплата: " + std::to_string(salary) + "\n";
}
