// stringtasks.h
#pragma once
#include <vector>
#include <string>

bool isInteger(const char* token);
bool isPalindrome(const char* token);
void BinarySort(char* token);

struct StringResults {
    std::string integersLine;
    int nonPalindromeCount;
    std::string newString;
    std::vector<std::string> binarySortedTokens;
    std::string insertedHello;
    std::string erasedThirdNumber;
    std::string tokensWithA;
    bool firstFiveEqual;
};

StringResults processString(const std::string& line1,
                            const std::string& line2,
                            const std::string& line3);
