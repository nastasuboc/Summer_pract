#pragma once

#include <QMainWindow>
#include <QVector>

class QLineEdit;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QTableWidget;
class QCloseEvent;

#include "booking.h"
#include "bookingservice.h"

class MainWindow : public QMainWindow, public IBookingObserver
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

    // Observer
    void onBookingAdded(const Booking& b) override;
    void onBookingRemoved(int index) override;
    void onBookingsChanged() override;

private slots:
    void newFile();
    void saveText();
    void loadText();
    void saveBinary();
    void loadBinary();
    void addBooking();
    void deleteSelected();
    void searchByCustomer();
    void sortByCustomer();
    void sortByNights();
    void about();

private:
    // Виджеты формы
    QLineEdit *customerEdit;
    QLineEdit *hotelEdit;
    QSpinBox *nightsSpin;
    QDoubleSpinBox *priceSpin;
    QComboBox *roomTypeCombo;
    QTableWidget *table;

    BookingService service;
    QString lastFileName;
    bool modified = false;

    void createUi();
    void createMenus();
    bool validateForm() const;
    void appendBookingToTable(const Booking& b);
    void refreshTable();
    void readSettings();
    void writeSettings();
};
