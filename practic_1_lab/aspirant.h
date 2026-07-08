#pragma once
#include "student.h"

class Aspirant : public Student
{
private:
    std::string diplom;

public:
    Aspirant(const std::string& Name, int Age, int Course,
             const std::string& Group, const std::string& Diplom);

    void toString(std::string& out) const override;
};
