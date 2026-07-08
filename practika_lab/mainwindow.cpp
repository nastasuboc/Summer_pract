#include "mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QCloseEvent>
#include <QSettings>

#include "logger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createUi();
    createMenus();
    readSettings();
}

void MainWindow::createUi()
{
    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    // Поля ввода
    customerEdit = new QLineEdit(this);
    customerEdit->setPlaceholderText(tr("ФИО клиента"));

    hotelEdit = new QLineEdit(this);
    hotelEdit->setPlaceholderText(tr("Название гостиницы"));

    nightsSpin = new QSpinBox(this);
    nightsSpin->setRange(1, 60);
    nightsSpin->setValue(1);

    priceSpin = new QDoubleSpinBox(this);
    priceSpin->setRange(10.0, 10000.0);
    priceSpin->setDecimals(2);
    priceSpin->setValue(100.0);

    roomTypeCombo = new QComboBox(this);
    roomTypeCombo->addItems({tr("Стандарт"), tr("Делюкс"), tr("Люкс")});

    auto *formLayout = new QHBoxLayout();
    formLayout->addWidget(customerEdit);
    formLayout->addWidget(hotelEdit);
    formLayout->addWidget(nightsSpin);
    formLayout->addWidget(priceSpin);
    formLayout->addWidget(roomTypeCombo);

    layout->addLayout(formLayout);

    // Таблица записей
    table = new QTableWidget(this);
    table->setColumnCount(6);
    QStringList headers;
    headers << tr("Клиент")
            << tr("Гостиница")
            << tr("Ночей")
            << tr("Цена/ночь")
            << tr("Тип номера")
            << tr("Итоговая цена");
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    layout->addWidget(table);

    setCentralWidget(central);
    setWindowTitle(tr("Бронирование гостиницы"));
}

void MainWindow::createMenus()
{
    // Меню Файл
    QMenu *fileMenu = menuBar()->addMenu(tr("Файл"));

    QAction *newAct = fileMenu->addAction(tr("Новый"), this, &MainWindow::newFile);
    newAct->setShortcut(QKeySequence::New);

    fileMenu->addSeparator();

    fileMenu->addAction(tr("Открыть (текст)"), this, &MainWindow::loadText);
    fileMenu->addAction(tr("Открыть (бинарный)"), this, &MainWindow::loadBinary);

    QAction *saveTextAct = fileMenu->addAction(tr("Сохранить (текст)"), this, &MainWindow::saveText);
    saveTextAct->setShortcut(QKeySequence::Save);

    fileMenu->addAction(tr("Сохранить (бинарный)"), this, &MainWindow::saveBinary);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("Выход"), this, [this]() {
        close();
    });
    exitAct->setShortcut(QKeySequence::Quit);

    // Меню Правка
    QMenu *editMenu = menuBar()->addMenu(tr("Правка"));

    editMenu->addAction(tr("Добавить запись"), this, &MainWindow::addBooking);
    editMenu->addAction(tr("Удалить запись"), this, &MainWindow::deleteSelected);
    editMenu->addSeparator();
    editMenu->addAction(tr("Поиск по клиенту"), this, &MainWindow::searchByCustomer);
    editMenu->addSeparator();
    editMenu->addAction(tr("Сортировка по клиенту"), this, &MainWindow::sortByCustomer);
    editMenu->addAction(tr("Сортировка по ночам"), this, &MainWindow::sortByNights);

    // Меню Справка
    QMenu *helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(tr("О программе"), this, &MainWindow::about);
}

bool MainWindow::validateForm() const
{
    if (customerEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, tr("Ошибка ввода"),
                             tr("Поле \"Клиент\" не должно быть пустым."));
        return false;
    }
    if (hotelEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, tr("Ошибка ввода"),
                             tr("Поле \"Гостиница\" не должно быть пустым."));
        return false;
    }
    if (nightsSpin->value() <= 0) {
        QMessageBox::warning(nullptr, tr("Ошибка ввода"),
                             tr("Количество ночей должно быть больше нуля."));
        return false;
    }
    if (priceSpin->value() <= 0.0) {
        QMessageBox::warning(nullptr, tr("Ошибка ввода"),
                             tr("Цена за ночь должна быть больше нуля."));
        return false;
    }
    return true;
}

void MainWindow::appendBookingToTable(const Booking& b)
{
    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row, 0, new QTableWidgetItem(b.customerName));
    table->setItem(row, 1, new QTableWidgetItem(b.hotelName));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(b.nights)));
    table->setItem(row, 3, new QTableWidgetItem(QString::number(b.pricePerNight, 'f', 2)));
    table->setItem(row, 4, new QTableWidgetItem(b.roomType));
    table->setItem(row, 5, new QTableWidgetItem(QString::number(b.totalPrice(), 'f', 2)));
}

void MainWindow::refreshTable()
{
    table->setRowCount(0);
    for (const Booking& b : bookings) {
        appendBookingToTable(b);
    }
}

void MainWindow::newFile()
{
    auto reply = QMessageBox::question(this, tr("Новый файл"),
                                       tr("Очистить текущие данные?"),
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        bookings.clear();
        refreshTable();
        customerEdit->clear();
        hotelEdit->clear();
        nightsSpin->setValue(1);
        priceSpin->setValue(100.0);
        roomTypeCombo->setCurrentIndex(0);
        modified = false;
        Logger::log("Создан новый файл бронирований");
    }
}

void MainWindow::addBooking()
{
    if (!validateForm())
        return;

    Booking b;
    b.customerName = customerEdit->text().trimmed();
    b.hotelName = hotelEdit->text().trimmed();
    b.nights = nightsSpin->value();
    b.pricePerNight = priceSpin->value();
    b.roomType = roomTypeCombo->currentText();

    bookings.append(b);
    appendBookingToTable(b);
    modified = true;
    Logger::log("Добавлена запись бронирования");
}

void MainWindow::deleteSelected()
{
    int row = table->currentRow();
    if (row < 0 || row >= bookings.size())
        return;

    auto reply = QMessageBox::question(this, tr("Подтверждение"),
                                       tr("Удалить выбранную запись?"),
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        bookings.removeAt(row);
        table->removeRow(row);
        modified = true;
        Logger::log("Удалена запись №" + QString::number(row + 1));
    }
}

void MainWindow::saveText()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить (текст)"),
                                                    lastFileName, tr("Text files (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Ошибка файла"),
                              tr("Не удалось открыть файл для записи."));
        return;
    }

    QTextStream out(&file);

    out << bookings.size() << '\n';
    for (const Booking& b : bookings) {
        b.writeText(out);
    }

    file.close();
    lastFileName = fileName;
    modified = false;
    Logger::log("Сохранение в текстовый файл: " + fileName);
}

void MainWindow::loadText()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть (текст)"),
                                                    lastFileName, tr("Text files (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Ошибка файла"),
                              tr("Не удалось открыть файл для чтения."));
        return;
    }

    QTextStream in(&file);

    int count = 0;
    in >> count;
    in.readLine();

    QVector<Booking> loaded;
    for (int i = 0; i < count; ++i) {
        Booking b;
        if (!b.readText(in)) {
            QMessageBox::warning(this, tr("Ошибка данных"),
                                 tr("Ошибка чтения записи №%1").arg(i + 1));
            break;
        }
        loaded.append(b);
    }

    file.close();

    bookings = loaded;
    refreshTable();
    lastFileName = fileName;
    modified = false;
    Logger::log("Загрузка из текстового файла: " + fileName);
}

void MainWindow::saveBinary()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить (бинарный)"),
                                                    lastFileName, tr("Binary files (*.bin)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Ошибка файла"),
                              tr("Не удалось открыть файл для записи."));
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_5);
    out << static_cast<quint32>(bookings.size());
    for (const Booking& b : bookings) {
        out << b;
    }

    file.close();
    lastFileName = fileName;
    modified = false;
    Logger::log("Сохранение в бинарный файл: " + fileName);
}

void MainWindow::loadBinary()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть (бинарный)"),
                                                    lastFileName, tr("Binary files (*.bin)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Ошибка файла"),
                              tr("Не удалось открыть файл для чтения."));
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_5);

    quint32 count = 0;
    in >> count;

    QVector<Booking> loaded;
    for (quint32 i = 0; i < count; ++i) {
        Booking b;
        in >> b;
        if (in.status() != QDataStream::Ok) {
            QMessageBox::warning(this, tr("Ошибка данных"),
                                 tr("Ошибка чтения записи №%1").arg(i + 1));
            break;
        }
        loaded.append(b);
    }

    file.close();

    bookings = loaded;
    refreshTable();
    lastFileName = fileName;
    modified = false;
    Logger::log("Загрузка из бинарного файла: " + fileName);
}

void MainWindow::searchByCustomer()
{
    QString name = QInputDialog::getText(this, tr("Поиск"),
                                         tr("Введите имя клиента:"));
    if (name.isEmpty())
        return;

    for (int i = 0; i < bookings.size(); ++i) {
        if (bookings[i].customerName.compare(name, Qt::CaseInsensitive) == 0) {
            table->selectRow(i);
            Logger::log("Поиск по клиенту: " + name);
            return;
        }
    }

    QMessageBox::information(this, tr("Результат поиска"),
                             tr("Запись с таким клиентом не найдена."));
}

void MainWindow::sortByCustomer()
{
    std::sort(bookings.begin(), bookings.end(),
              [](const Booking& a, const Booking& b) {
                  return a.customerName.toLower() < b.customerName.toLower();
              });
    refreshTable();
    modified = true;
    Logger::log("Сортировка по клиенту");
}

void MainWindow::sortByNights()
{
    std::sort(bookings.begin(), bookings.end(),
              [](const Booking& a, const Booking& b) {
                  return a.nights < b.nights;
              });
    refreshTable();
    modified = true;
    Logger::log("Сортировка по ночам");
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("О программе"),
                       tr("Учебное приложение\n\"Бронирование гостиницы\"\n"
                          "Ввод, редактирование, сохранение и загрузка\n"
                          "текстовых и числовых данных (QTextStream, QDataStream)."));
}

void MainWindow::readSettings()
{
    QSettings settings("MyUniversity", "HotelBooking");
    restoreGeometry(settings.value("geometry").toByteArray());
    lastFileName = settings.value("lastFile").toString();
}

void MainWindow::writeSettings()
{
    QSettings settings("MyUniversity", "HotelBooking");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("lastFile", lastFileName);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (modified) {
        auto reply = QMessageBox::question(this, tr("Несохранённые данные"),
                                           tr("Есть несохранённые изменения. Выйти без сохранения?"),
                                           QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            event->ignore();
            return;
        }
    }
    writeSettings();
    QMainWindow::closeEvent(event);
}
