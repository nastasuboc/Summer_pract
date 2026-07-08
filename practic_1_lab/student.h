#pragma once
#include "abstracthuman.h"

class Student : public AbstractHuman
{
protected:
    int course;
    std::string group;

public:
    Student(const std::string& Name, int Age, int Course, const std::string& Group);

    void toString(std::string& out) const override;
};
