// flashlist.h
#pragma once
#include <fstream>

class List {
public:
    struct Flash {
    private:
        char* name;
        long price;
        double size;
    public:
        Flash(const char* Name = "", long Price = 0, double Size = 0.0);
        Flash(const Flash& other);
        Flash& operator=(const Flash& other);
        long getPrice() const;
        const char* getName() const { return name; }
        double getSize() const { return size; }
        void print(std::ostream& out);
        ~Flash();
    };

    class Node {
    public:
        Node* pNext;
        Node* pPrev;
        Flash data;
        Node(const Flash& data = Flash(), Node* pNext = nullptr, Node* pPrev = nullptr);
    };

    List();
    ~List();
    void push_back(const Flash& data);
    void push_front(const Flash& data);
    void insert(const Flash& data, int index);
    void pop_back();
    void pop_front();
    void remove_at(int index);
    void clear();
    void sort();
    void printFile(std::ofstream& fout);
    void loadfromfile(std::ifstream& fin);
    void sortBySize();
    int size;
    Node* head;
    Node* tail;
};
