// mainwindow.h
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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

protected:
    void closeEvent(QCloseEvent *event) override;

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

    QVector<Booking> bookings;
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
