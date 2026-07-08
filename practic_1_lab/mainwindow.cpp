#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "student.h"
#include "aspirant.h"
#include "worker.h"
#include "stringtasks.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>

// =========================================================
//                      КОНСТРУКТОР
// =========================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ================= ЛАБА 1 =================

    QGridLayout* formLayout = new QGridLayout;

    formLayout->addWidget(new QLabel("Имя:"), 0, 0);
    lineName = new QLineEdit;
    formLayout->addWidget(lineName, 0, 1);

    formLayout->addWidget(new QLabel("Возраст:"), 1, 0);
    spinAge = new QSpinBox;
    spinAge->setMinimum(0);
    formLayout->addWidget(spinAge, 1, 1);

    formLayout->addWidget(new QLabel("Тип:"), 2, 0);
    comboType = new QComboBox;
    comboType->addItems({"Студент", "Аспирант", "Рабочий"});
    formLayout->addWidget(comboType, 2, 1);

    lblCourse = new QLabel("Курс:");
    formLayout->addWidget(lblCourse, 3, 0);
    spinCourse = new QSpinBox;
    spinCourse->setMinimum(1);
    formLayout->addWidget(spinCourse, 3, 1);

    lblGroup = new QLabel("Группа:");
    formLayout->addWidget(lblGroup, 4, 0);
    lineGroup = new QLineEdit;
    formLayout->addWidget(lineGroup, 4, 1);

    lblDiplom = new QLabel("Диплом:");
    formLayout->addWidget(lblDiplom, 5, 0);
    lineDiplom = new QLineEdit;
    formLayout->addWidget(lineDiplom, 5, 1);

    lblStag = new QLabel("Стаж:");
    formLayout->addWidget(lblStag, 6, 0);
    spinStag = new QSpinBox;
    spinStag->setMinimum(0);
    formLayout->addWidget(spinStag, 6, 1);

    lblWorkplace = new QLabel("Место работы:");
    formLayout->addWidget(lblWorkplace, 7, 0);
    lineWorkplace = new QLineEdit;
    formLayout->addWidget(lineWorkplace, 7, 1);

    lblPosition = new QLabel("Должность:");
    formLayout->addWidget(lblPosition, 8, 0);
    linePosition = new QLineEdit;
    formLayout->addWidget(linePosition, 8, 1);

    lblSalary = new QLabel("Зарплата:");
    formLayout->addWidget(lblSalary, 9, 0);
    spinSalary = new QDoubleSpinBox;
    spinSalary->setMinimum(0.0);
    formLayout->addWidget(spinSalary, 9, 1);

    tablePeople = new QTableWidget;
    tablePeople->setColumnCount(4);
    tablePeople->setHorizontalHeaderLabels({"Имя", "Возраст", "Тип", "Инфо"});
    tablePeople->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    btnAdd = new QPushButton("Добавить");
    btnDelete = new QPushButton("Удалить");
    btnClear = new QPushButton("Очистить");
    btnCompare = new QPushButton("Сравнить возраст");

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::addPerson);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::deletePerson);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::clearPeople);
    connect(btnCompare, &QPushButton::clicked, this, &MainWindow::comparePeople);

    connect(comboType, &QComboBox::currentTextChanged,
            this, &MainWindow::updatePersonFields);

    QHBoxLayout* buttons1 = new QHBoxLayout;
    buttons1->addWidget(btnAdd);
    buttons1->addWidget(btnDelete);
    buttons1->addWidget(btnClear);
    buttons1->addWidget(btnCompare);

    QHBoxLayout* top1 = new QHBoxLayout;
    top1->addLayout(formLayout);
    top1->addWidget(tablePeople);

    QVBoxLayout* lab1 = new QVBoxLayout;
    lab1->addLayout(top1);
    lab1->addLayout(buttons1);

    ui->tabWidget->widget(0)->setLayout(lab1);

    updatePersonFields();

    // ================= ЛАБА 2 =================

    lineString1 = new QLineEdit;
    lineString2 = new QLineEdit;
    labelResult = new QLabel("Результат будет здесь");

    btnCompareStrings = new QPushButton("Сравнить строки");
    btnConcat = new QPushButton("Объединить");
    btnClearStrings = new QPushButton("Очистить");

    connect(btnCompareStrings, &QPushButton::clicked, this, &MainWindow::compareStrings);
    connect(btnConcat, &QPushButton::clicked, this, &MainWindow::concatStrings);
    connect(btnClearStrings, &QPushButton::clicked, this, &MainWindow::clearStrings);

    QHBoxLayout* buttons2 = new QHBoxLayout;
    buttons2->addWidget(btnCompareStrings);
    buttons2->addWidget(btnConcat);
    buttons2->addWidget(btnClearStrings);

    QVBoxLayout* lab2 = new QVBoxLayout;
    lab2->addWidget(new QLabel("Строка 1:"));
    lab2->addWidget(lineString1);
    lab2->addWidget(new QLabel("Строка 2:"));
    lab2->addWidget(lineString2);
    lab2->addWidget(labelResult);
    lab2->addLayout(buttons2);

    ui->tabWidget->widget(1)->setLayout(lab2);

    // ================= ЛАБА 3 =================

    lineItemName = new QLineEdit;
    spinPrice = new QDoubleSpinBox;
    spinVolume = new QSpinBox;

    spinPrice->setMinimum(0.0);
    spinVolume->setMinimum(0);

    QFormLayout* form3 = new QFormLayout;
    form3->addRow("Название:", lineItemName);
    form3->addRow("Цена:", spinPrice);
    form3->addRow("Объём:", spinVolume);

    tableFlashList = new QTableWidget;
    tableFlashList->setColumnCount(3);
    tableFlashList->setHorizontalHeaderLabels({"Название", "Цена", "Объём"});
    tableFlashList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    btnAddItem = new QPushButton("Добавить");
    btnDeleteItem = new QPushButton("Удалить");
    btnSortPrice = new QPushButton("Сортировать по цене");
    btnSortVolume = new QPushButton("Сортировать по объёму");
    btnSearchItem = new QPushButton("Поиск по названию");

    connect(btnAddItem, &QPushButton::clicked, this, &MainWindow::addItem);
    connect(btnDeleteItem, &QPushButton::clicked, this, &MainWindow::deleteItem);
    connect(btnSortPrice, &QPushButton::clicked, this, &MainWindow::sortByPrice);
    connect(btnSortVolume, &QPushButton::clicked, this, &MainWindow::sortByVolume);
    connect(btnSearchItem, &QPushButton::clicked, this, &MainWindow::searchItem);

    QHBoxLayout* buttons3 = new QHBoxLayout;
    buttons3->addWidget(btnAddItem);
    buttons3->addWidget(btnDeleteItem);
    buttons3->addWidget(btnSortPrice);
    buttons3->addWidget(btnSortVolume);
    buttons3->addWidget(btnSearchItem);

    QVBoxLayout* lab3 = new QVBoxLayout;
    lab3->addLayout(form3);
    lab3->addWidget(tableFlashList);
    lab3->addLayout(buttons3);

    ui->tabWidget->widget(2)->setLayout(lab3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// =========================================================
//                      ЛАБА 1 — ЛЮДИ
// =========================================================

void MainWindow::updatePersonFields()
{
    QString type = comboType->currentText();

    bool isStudent  = (type == "Студент");
    bool isAspirant = (type == "Аспирант");
    bool isWorker   = (type == "Рабочий");

    lblCourse->setVisible(isStudent || isAspirant);
    spinCourse->setVisible(isStudent || isAspirant);

    lblGroup->setVisible(isStudent || isAspirant);
    lineGroup->setVisible(isStudent || isAspirant);

    lblDiplom->setVisible(isAspirant);
    lineDiplom->setVisible(isAspirant);

    lblStag->setVisible(isWorker);
    spinStag->setVisible(isWorker);

    lblWorkplace->setVisible(isWorker);
    lineWorkplace->setVisible(isWorker);

    lblPosition->setVisible(isWorker);
    linePosition->setVisible(isWorker);

    lblSalary->setVisible(isWorker);
    spinSalary->setVisible(isWorker);

    // очищаем скрытые поля
    if (!isStudent && !isAspirant) {
        spinCourse->setValue(1);
        lineGroup->clear();
    }
    if (!isAspirant) {
        lineDiplom->clear();
    }
    if (!isWorker) {
        spinStag->setValue(0);
        lineWorkplace->clear();
        linePosition->clear();
        spinSalary->setValue(0.0);
    }
}

void MainWindow::addPerson()
{
    QString name = lineName->text();
    int age      = spinAge->value();
    QString type = comboType->currentText();

    if (name.isEmpty() || age <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные имя и возраст");
        return;
    }

    std::string out;

    if (type == "Студент") {
        Student s(name.toStdString(), age,
                  spinCourse->value(),
                  lineGroup->text().toStdString());
        s.toString(out);
    }
    else if (type == "Аспирант") {
        Aspirant a(name.toStdString(), age,
                   spinCourse->value(),
                   lineGroup->text().toStdString(),
                   lineDiplom->text().toStdString());
        a.toString(out);
    }
    else {
        Worker w(name.toStdString(), age,
                 spinStag->value(),
                 lineWorkplace->text().toStdString(),
                 linePosition->text().toStdString(),
                 spinSalary->value());
        w.toString(out);
    }

    int row = tablePeople->rowCount();
    tablePeople->insertRow(row);

    tablePeople->setRowHeight(row, 120); // инфо видно полностью

    tablePeople->setItem(row, 0, new QTableWidgetItem(name));
    tablePeople->setItem(row, 1, new QTableWidgetItem(QString::number(age)));
    tablePeople->setItem(row, 2, new QTableWidgetItem(type));

    QTableWidgetItem* infoItem = new QTableWidgetItem(QString::fromStdString(out));
    infoItem->setTextAlignment(Qt::AlignLeft | Qt::AlignTop);
    infoItem->setData(Qt::TextWordWrap, false);
    infoItem->setToolTip(infoItem->text());
    tablePeople->setItem(row, 3, infoItem);
}

void MainWindow::deletePerson()
{
    int row = tablePeople->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите строку для удаления");
        return;
    }
    tablePeople->removeRow(row);
}

void MainWindow::clearPeople()
{
    tablePeople->setRowCount(0);

    lineName->clear();
    spinAge->setValue(0);
    comboType->setCurrentIndex(0);
    spinCourse->setValue(1);
    lineGroup->clear();
    lineDiplom->clear();
    spinStag->setValue(0);
    lineWorkplace->clear();
    linePosition->clear();
    spinSalary->setValue(0.0);

    updatePersonFields();
}

void MainWindow::comparePeople()
{
    QList<QTableWidgetSelectionRange> ranges = tablePeople->selectedRanges();

    if (ranges.size() == 0 || ranges[0].rowCount() < 2) {
        QMessageBox::information(this, "Сравнение", "Выберите два человека в таблице");
        return;
    }

    int row1 = ranges[0].topRow();
    int row2 = ranges[0].topRow() + 1;

    QString info1 = tablePeople->item(row1, 3)->text();
    QString info2 = tablePeople->item(row2, 3)->text();

    int age1 = tablePeople->item(row1, 1)->text().toInt();
    int age2 = tablePeople->item(row2, 1)->text().toInt();

    QString result;

    result += "Человек 1:\n" + info1 + "\n\n";
    result += "Человек 2:\n" + info2 + "\n\n";

    if (age1 > age2)
        result += "Возраст: Человек 1 старше.\n";
    else if (age1 < age2)
        result += "Возраст: Человек 2 старше.\n";
    else
        result += "Возраст: одинаковый.\n";

    QMessageBox::information(this, "Сравнение", result);
}


// =========================================================
//                      ЛАБА 2 — СТРОКИ
// =========================================================

void MainWindow::compareStrings()
{
    QString s1 = lineString1->text();
    QString s2 = lineString2->text();

    if (s1.isEmpty() || s2.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Обе строки должны быть непустыми");
        return;
    }

    if (s1 == s2)
        labelResult->setText("Строки равны");
    else
        labelResult->setText("Строки не равны");
}

void MainWindow::concatStrings()
{
    QString s1 = lineString1->text();
    QString s2 = lineString2->text();

    labelResult->setText("Результат: " + s1 + s2);
}

void MainWindow::clearStrings()
{
    lineString1->clear();
    lineString2->clear();
    labelResult->setText("Результат будет здесь");
}

// =========================================================
//                      ЛАБА 3 — FLASHLIST
// =========================================================

void MainWindow::updateFlashTable()
{
    tableFlashList->setRowCount(myList.size);
    List::Node* cur = myList.head;
    int row = 0;
    while (cur) {
        tableFlashList->setItem(row, 0,
                                new QTableWidgetItem(cur->data.getName()));
        tableFlashList->setItem(row, 1,
                                new QTableWidgetItem(QString::number(cur->data.getPrice())));
        tableFlashList->setItem(row, 2,
                                new QTableWidgetItem(QString::number(cur->data.getSize())));
        cur = cur->pNext;
        ++row;
    }
}

void MainWindow::addItem()
{
    QString name = lineItemName->text();
    long   price = static_cast<long>(spinPrice->value());
    double size  = static_cast<double>(spinVolume->value());

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название не может быть пустым");
        return;
    }

    myList.push_back(List::Flash(name.toStdString().c_str(), price, size));
    updateFlashTable();
}

void MainWindow::deleteItem()
{
    int row = tableFlashList->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите строку для удаления");
        return;
    }

    try {
        myList.remove_at(row + 1); // индексы в List с 1
        updateFlashTable();
    } catch (const char* msg) {
        QMessageBox::warning(this, "Ошибка", QString::fromUtf8(msg));
    }
}

void MainWindow::sortByPrice()
{
    try {
        myList.sort();
        updateFlashTable();
    } catch (const char* msg) {
        QMessageBox::warning(this, "Ошибка", QString::fromUtf8(msg));
    }
}

void MainWindow::sortByVolume()
{
    try {
        myList.sortBySize();
        updateFlashTable();
    } catch (const char* msg) {
        QMessageBox::warning(this, "Ошибка", QString::fromUtf8(msg));
    }
}

void MainWindow::searchItem()
{
    QString name = lineItemName->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название для поиска");
        return;
    }

    for (int row = 0; row < tableFlashList->rowCount(); ++row) {
        if (tableFlashList->item(row, 0)->text() == name) {
            tableFlashList->selectRow(row);
            return;
        }
    }

    QMessageBox::information(this, "Поиск по названию", "Элемент не найден");
}
