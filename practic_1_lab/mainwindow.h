#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QTableWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "flashlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // ===== ЛАБА 1 =====
    QLineEdit* lineName;
    QSpinBox* spinAge;
    QComboBox* comboType;

    QLabel* lblCourse;
    QSpinBox* spinCourse;

    QLabel* lblGroup;
    QLineEdit* lineGroup;

    QLabel* lblDiplom;
    QLineEdit* lineDiplom;

    QLabel* lblStag;
    QSpinBox* spinStag;

    QLabel* lblWorkplace;
    QLineEdit* lineWorkplace;

    QLabel* lblPosition;
    QLineEdit* linePosition;

    QLabel* lblSalary;
    QDoubleSpinBox* spinSalary;

    QTableWidget* tablePeople;

    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnClear;
    QPushButton* btnCompare;

    void updatePersonFields();

    // ===== ЛАБА 2 =====
    QLineEdit* lineString1;
    QLineEdit* lineString2;
    QLabel* labelResult;

    QPushButton* btnCompareStrings;
    QPushButton* btnConcat;
    QPushButton* btnClearStrings;

    // ===== ЛАБА 3 =====
    QLineEdit* lineItemName;
    QDoubleSpinBox* spinPrice;
    QSpinBox* spinVolume;
    QTableWidget* tableFlashList;

    QPushButton* btnAddItem;
    QPushButton* btnDeleteItem;
    QPushButton* btnSortPrice;
    QPushButton* btnSortVolume;
    QPushButton* btnSearchItem;

    List myList;

private slots:
    // Лаба 1
    void addPerson();
    void deletePerson();
    void clearPeople();
    void comparePeople();

    // Лаба 2
    void compareStrings();
    void concatStrings();
    void clearStrings();

    // Лаба 3
    void addItem();
    void deleteItem();
    void sortByPrice();
    void sortByVolume();
    void searchItem();
    void updateFlashTable();
};

#endif // MAINWINDOW_H
