#pragma once

#include <QVector>
#include <QString>
#include "booking.h"

class IBookingObserver {
public:
    virtual void onBookingAdded(const Booking& b) = 0;
    virtual void onBookingRemoved(int index) = 0;
    virtual void onBookingsChanged() = 0;
    virtual ~IBookingObserver() = default;
};

class BookingService {
public:
    void addObserver(IBookingObserver* obs);
    void removeObserver(IBookingObserver* obs);

    void add(const Booking& b);
    void remove(int index);

    QVector<Booking> all() const;
    void clear();
    void sortByCustomer();
    void sortByNights();

    int findByCustomer(const QString& name) const;

private:
    QVector<Booking> bookings;
    QVector<IBookingObserver*> observers;

    void notifyAdded(const Booking& b);
    void notifyRemoved(int index);
    void notifyChanged();
};
