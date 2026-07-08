// booking.h
#pragma once

#include <QString>
#include <QDataStream>
#include <QTextStream>

class Booking
{
public:
    QString customerName;   // ФИО клиента
    QString hotelName;      // Название гостиницы
    int nights = 0;         // Количество ночей
    double pricePerNight = 0.0; // Цена за ночь
    QString roomType;       // Тип номера (доп. поле)

    Booking() = default;

    double totalPrice() const {
        return nights * pricePerNight;
    }

    // Бинарная сериализация
    friend QDataStream& operator<<(QDataStream& out, const Booking& b) {
        out << b.customerName
            << b.hotelName
            << b.nights
            << b.pricePerNight
            << b.roomType;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Booking& b) {
        in >> b.customerName
            >> b.hotelName
            >> b.nights
            >> b.pricePerNight
            >> b.roomType;
        return in;
    }

    // Текстовая сериализация (простая, построчная)
    void writeText(QTextStream& out) const {
        out << customerName << '\n'
            << hotelName << '\n'
            << nights << '\n'
            << pricePerNight << '\n'
            << roomType << '\n';
    }

    bool readText(QTextStream& in) {
        if (in.atEnd()) return false;
        customerName = in.readLine();
        if (in.atEnd()) return false;
        hotelName = in.readLine();
        if (in.atEnd()) return false;
        QString nightsStr = in.readLine();
        if (in.atEnd()) return false;
        QString priceStr = in.readLine();
        if (in.atEnd()) return false;
        roomType = in.readLine();

        bool okN = false, okP = false;
        nights = nightsStr.toInt(&okN);
        pricePerNight = priceStr.toDouble(&okP);
        return okN && okP;
    }
};
