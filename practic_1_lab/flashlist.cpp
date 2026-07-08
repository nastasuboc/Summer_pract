// flashlist.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "flashlist.h"
#include <iostream>
#include <cstring>

List::Node::Node(const Flash& data, Node* pNext, Node* pPrev)
{
    this->data = data;
    this->pNext = pNext;
    this->pPrev = pPrev;
}

List::Flash::Flash(const char* Name, long Price, double Size)
{
    name = new char[strlen(Name) + 1];
    strcpy(name, Name);
    price = Price;
    size = Size;
}

List::Flash::Flash(const Flash& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    price = other.price;
    size = other.size;
}

List::Flash& List::Flash::operator=(const Flash& other)
{
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        price = other.price;
        size = other.size;
    }
    return *this;
}

long List::Flash::getPrice() const {
    return price;
}

void List::Flash::print(std::ostream& out) {
    out << "Имя: " << name << "\nЦена: " << price << "\nРазмер:" << size << "\n\n";
}

List::Flash::~Flash() {
    delete[] name;
}

List::List() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}

List::~List() {
    clear();
}

void List::push_back(const Flash& data) {
    Node* NewNode = new Node(data);
    if (head == nullptr) {
        head = NewNode;
        tail = NewNode;
    } else {
        tail->pNext = NewNode;
        NewNode->pPrev = tail;
        tail = NewNode;
    }
    ++size;
}

void List::push_front(const Flash& data) {
    Node* NewNode = new Node(data);
    if (head == nullptr) {
        head = NewNode;
        tail = NewNode;
    } else {
        head->pPrev = NewNode;
        NewNode->pNext = head;
        head = NewNode;
    }
    ++size;
}

void List::insert(const Flash& data, int index) {
    if (index < 1 || index > size + 1) {
        throw "Неверный индекс!\n";
    }
    if (index == 1) {
        push_front(data);
        return;
    }
    if (index == size + 1) {
        push_back(data);
        return;
    }
    Node* current = head;
    for (int i = 1; i < index; ++i) {
        current = current->pNext;
    }
    Node* NewNode = new Node(data);
    NewNode->pPrev = current->pPrev;
    NewNode->pNext = current;
    current->pPrev->pNext = NewNode;
    current->pPrev = NewNode;
    ++size;
}

void List::pop_back() {
    if (size == 0) {
        throw "Список пуст! \n";
    }
    Node* temp = tail;
    if (tail->pPrev != nullptr) {
        tail = tail->pPrev;
        tail->pNext = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete temp;
    --size;
}

void List::pop_front() {
    if (size == 0) {
        throw "Список пуст! \n";
    }
    Node* temp = head;
    if (size == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->pNext;
        head->pPrev = nullptr;
    }
    delete temp;
    --size;
}

void List::remove_at(int index) {
    if (size == 0) {
        throw "Список пуст!\n";
    }
    if (index < 1 || index > size) {
        throw "Неверный индекс!\n";
    }
    if (index == 1) {
        pop_front();
        return;
    }
    if (index == size) {
        pop_back();
        return;
    }
    Node* current = head;
    for (int i = 1; i < index; ++i) {
        current = current->pNext;
    }
    current->pPrev->pNext = current->pNext;
    current->pNext->pPrev = current->pPrev;
    delete current;
    --size;
}

void List::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->pNext;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void List::sort() {
    if (size == 0) {
        throw "Список пуст! \n";
    }
    if (size == 1) {
        return;
    }
    bool swaped;
    do {
        swaped = false;
        Node* current = head;
        while (current->pNext != nullptr) {
            if (current->data.getPrice() > current->pNext->data.getPrice()) {
                Flash temp = current->data;
                current->data = current->pNext->data;
                current->pNext->data = temp;
                swaped = true;
            }
            current = current->pNext;
        }
    } while (swaped);
}

void List::printFile(std::ofstream& fout) {
    if (size == 0) {
        throw "Список пуст!\n";
    }
    Node* current = head;
    while (current != nullptr) {
        current->data.print(fout);
        current = current->pNext;
    }
}

void List::loadfromfile(std::ifstream& fin) {
    char name[251];
    long price;
    double size;
    while (fin >> name >> price >> size) {
        this->push_back(Flash(name, price, size));
    }
}
void List::sortBySize()
{
    if (size == 0) {
        throw "Список пуст!\n";
    }
    if (size == 1) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->pNext != nullptr) {
            if (current->data.getSize() > current->pNext->data.getSize()) {
                Flash temp = current->data;
                current->data = current->pNext->data;
                current->pNext->data = temp;
                swapped = true;
            }
            current = current->pNext;
        }
    } while (swapped);
}
