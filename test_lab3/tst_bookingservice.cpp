#include <QtTest>
#include "booking.h"
#include "bookingservice.h"

class BookingServiceTest : public QObject
{
    Q_OBJECT

private:
    Booking makeBooking(const QString& customer,
                        const QString& hotel,
                        int nights,
                        double price,
                        const QString& roomType = "Стандарт")
    {
        Booking b;
        b.customerName = customer;
        b.hotelName = hotel;
        b.nights = nights;
        b.pricePerNight = price;
        b.roomType = roomType;
        return b;
    }

private slots:

    void testTotalPrice()
    {
        Booking b = makeBooking("Иванов Иван", "Hilton", 3, 150.0);
        QCOMPARE(b.totalPrice(), 450.0);
    }

    void testAddBooking()
    {
        BookingService service;
        Booking b = makeBooking("Петров Петр", "Marriott", 2, 200.0);

        service.add(b);

        QCOMPARE(service.all().size(), 1);
        QCOMPARE(service.all().first().customerName, QString("Петров Петр"));
        QCOMPARE(service.all().first().hotelName, QString("Marriott"));
    }

    void testRemoveBooking()
    {
        BookingService service;
        service.add(makeBooking("Клиент А", "Hotel A", 1, 100.0));
        service.add(makeBooking("Клиент Б", "Hotel B", 2, 120.0));

        service.remove(0);

        QCOMPARE(service.all().size(), 1);
        QCOMPARE(service.all().first().customerName, QString("Клиент Б"));
    }

    void testFindByCustomer()
    {
        BookingService service;
        service.add(makeBooking("Сидорова Анна", "Hotel X", 5, 90.0));

        int foundIndex = service.findByCustomer("сидорова анна");
        int notFoundIndex = service.findByCustomer("Несуществующий Клиент");

        QCOMPARE(foundIndex, 0);
        QCOMPARE(notFoundIndex, -1);
    }

    void testSortByNights()
    {
        BookingService service;
        service.add(makeBooking("Клиент 1", "Hotel", 5, 100.0));
        service.add(makeBooking("Клиент 2", "Hotel", 1, 100.0));
        service.add(makeBooking("Клиент 3", "Hotel", 3, 100.0));

        service.sortByNights();

        auto list = service.all();
        QCOMPARE(list.at(0).nights, 1);
        QCOMPARE(list.at(1).nights, 3);
        QCOMPARE(list.at(2).nights, 5);
    }
};

QTEST_APPLESS_MAIN(BookingServiceTest)
#include "tst_bookingservice.moc"
