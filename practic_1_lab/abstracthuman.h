#pragma once
#include <string>

class AbstractHuman
{
protected:
    std::string name;
    int age;
    int id;
    static int count;

public:
    AbstractHuman(const std::string& Name, int Age);
    virtual ~AbstractHuman() = default;

    static int GetCount();
    void SetAge(int Age);

    virtual void toString(std::string& out) const = 0;
};
