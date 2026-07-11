#include "bookingservice.h"
#include <algorithm>

void BookingService::addObserver(IBookingObserver* obs) {
    observers.append(obs);
}

void BookingService::removeObserver(IBookingObserver* obs) {
    observers.removeAll(obs);
}

void BookingService::notifyAdded(const Booking& b) {
    for (auto* o : observers) o->onBookingAdded(b);
}
void BookingService::clear() {
    bookings.clear();
    notifyChanged();
}
void BookingService::notifyRemoved(int index) {
    for (auto* o : observers) o->onBookingRemoved(index);
}

void BookingService::notifyChanged() {
    for (auto* o : observers) o->onBookingsChanged();
}

void BookingService::add(const Booking& b) {
    bookings.append(b);
    notifyAdded(b);
    notifyChanged();
}

void BookingService::remove(int index) {
    if (index < 0 || index >= bookings.size()) return;
    bookings.removeAt(index);
    notifyRemoved(index);
    notifyChanged();
}

QVector<Booking> BookingService::all() const {
    return bookings;
}

void BookingService::sortByCustomer() {
    std::sort(bookings.begin(), bookings.end(),
              [](const Booking& a, const Booking& b) {
                  return a.customerName.toLower() < b.customerName.toLower();
              });
    notifyChanged();
}

void BookingService::sortByNights() {
    std::sort(bookings.begin(), bookings.end(),
              [](const Booking& a, const Booking& b) {
                  return a.nights < b.nights;
              });
    notifyChanged();
}

int BookingService::findByCustomer(const QString& name) const {
    for (int i = 0; i < bookings.size(); ++i) {
        if (bookings[i].customerName.compare(name, Qt::CaseInsensitive) == 0)
            return i;
    }
    return -1;
}
