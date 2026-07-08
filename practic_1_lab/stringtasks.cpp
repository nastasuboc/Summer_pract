// stringtasks.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "stringtasks.h"
#include <cstring>
#include <cctype>

bool isInteger(const char* token)
{
    if (token == nullptr || *token == '\0') return false;
    int i = 0;
    if (token[0] == '-' || token[0] == '+') i++;
    for (; token[i] != '\0'; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(token[i]))) return false;
    }
    return true;
}

bool isPalindrome(const char* token)
{
    if (!token) return false;
    size_t len = std::strlen(token);
    for (size_t i = 0; i < len / 2; ++i) {
        if (token[i] != token[len - 1 - i]) return false;
    }
    return true;
}

void BinarySort(char* token)
{
    if (!token) return;
    size_t len = std::strlen(token);
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j + 1 < len; ++j) {
            if (token[j] > token[j + 1]) {
                std::swap(token[j], token[j + 1]);
            }
        }
    }
}

StringResults processString(const std::string& line1,
                            const std::string& line2,
                            const std::string& line3)
{
    StringResults res{};
    std::vector<char*> tokens;

    // Разбиение line1 на лексемы по line2 (разделители)
    {
        std::string delims = line2.empty() ? " " : line2;
        std::string s = line1;
        size_t start = s.find_first_not_of(delims);
        while (start != std::string::npos) {
            size_t end = s.find_first_of(delims, start);
            if (end == std::string::npos) end = s.size();
            std::string token = s.substr(start, end - start);
            char* c = new char[token.size() + 1];
            std::strcpy(c, token.c_str());
            tokens.push_back(c);
            start = s.find_first_not_of(delims, end);
        }
    }

    // Лексемы - целые числа из 10-ной с/с
    {
        char words[256];
        words[0] = '\0';
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (isInteger(tokens[i])) {
                std::strcat(words, tokens[i]);
                std::strcat(words, " ");
            }
        }
        res.integersLine = words;
    }

    // Число лексем не являющихся палиндромами
    {
        int sum = 0;
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (!isPalindrome(tokens[i])) {
                ++sum;
            }
        }
        res.nonPalindromeCount = sum;
    }

    // Формирование новой строки из не-палиндромов
    {
        std::string newString;
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (!isPalindrome(tokens[i])) {
                newString += tokens[i];
                newString += " ";
            }
        }
        if (!newString.empty()) newString.pop_back();
        res.newString = newString;
    }

    // Бинарная сортировка строки (каждой лексемы)
    {
        std::vector<std::string> sorted;
        for (size_t i = 0; i < tokens.size(); ++i) {
            BinarySort(tokens[i]);
            sorted.push_back(tokens[i]);
        }
        res.binarySortedTokens = sorted;
    }

    // Добавили после 1 лексемы строку Hello!!!
    {
        std::string strok(line3);
        std::string delims = line2.empty() ? " " : line2;
        size_t start = strok.find_first_not_of(delims);
        size_t end = strok.find_first_of(delims, start);
        if (start != std::string::npos) {
            if (end == std::string::npos) { end = strok.size(); }
            strok.insert(end, "Hello!!!");
        }
        res.insertedHello = strok;

        // Строка после удаления 3 числа в 10с/с
        int flag = 0;
        size_t start_position = 0;
        size_t end_position = 0;
        for (std::string::size_type i = 0; i < strok.size(); ++i) {
            if (std::isdigit(static_cast<unsigned char>(strok[i])) ||
                (strok[i] == '-' && i + 1 < strok.size() &&
                 std::isdigit(static_cast<unsigned char>(strok[i + 1])))) {
                start_position = i;
                while (i < strok.size() &&
                       std::isdigit(static_cast<unsigned char>(strok[i]))) {
                    i++;
                }
                end_position = i;
                ++flag;
            }
            if (flag == 3) {
                break;
            }
        }
        if (flag == 3 && end_position > start_position) {
            strok.erase(start_position, end_position - start_position);
        }
        res.erasedThirdNumber = strok;

        // Преобразовали string в char (просто сохраним строку)
        const char* cstr = strok.c_str();
        (void)cstr; // уже есть в erasedThirdNumber
    }

    // Лексемы, содержащие подстроку 'a'
    {
        std::string withA;
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (std::strstr(tokens[i], "a") != nullptr) {
                withA += tokens[i];
                withA += " ";
            }
        }
        res.tokensWithA = withA;
    }

    // Сравнение первых 5 символов line1 и integersLine
    {
        int k = std::strncmp(line1.c_str(), res.integersLine.c_str(), 5);
        res.firstFiveEqual = (k == 0);
    }

    // Освобождение памяти
    for (size_t i = 0; i < tokens.size(); ++i) {
        delete[] tokens[i];
        tokens[i] = nullptr;
    }

    return res;
}
