#include "abstracthuman.h"

int AbstractHuman::count = 0;

AbstractHuman::AbstractHuman(const std::string& Name, int Age)
    : name(Name), age(Age), id(++count)
{
}

int AbstractHuman::GetCount()
{
    return count;
}

void AbstractHuman::SetAge(int Age)
{
    if (Age > 0)
        age = Age;
}
