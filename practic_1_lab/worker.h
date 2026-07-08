#pragma once
#include "abstracthuman.h"

class Worker : public AbstractHuman
{
private:
    int stag;
    std::string workplace;
    std::string position;
    double salary;

public:
    Worker(const std::string& Name, int Age, int Stag,
           const std::string& Workplace, const std::string& Position, double Salary);

    void toString(std::string& out) const override;
};
