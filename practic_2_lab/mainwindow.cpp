#include "mainwindow.h"
#include "equipmentmodel.h"
#include "equipmentdialog.h"

#include <QTableView>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_model(new EquipmentModel(this)),
    m_proxy(new QSortFilterProxyModel(this)),
    m_view(new QTableView(this)),
    m_search(new QLineEdit(this))
{
    m_proxy->setSourceModel(m_model);
    m_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxy->setFilterKeyColumn(1);

    setupUi();
    setupMenu();
}

void MainWindow::setupUi()
{
    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    m_search->setPlaceholderText("Поиск по названию...");
    connect(m_search, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);
    layout->addWidget(m_search);

    m_view->setModel(m_proxy);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

    // Растягиваем столбцы
    m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // --- СОРТИРОВКА ПО ЛЮБОМУ СТОЛБЦУ ---
    m_view->setSortingEnabled(true);
    m_view->horizontalHeader()->setSectionsClickable(true);
    m_view->horizontalHeader()->setSortIndicatorShown(true);


    layout->addWidget(m_view);

    auto *btnAdd = new QPushButton("Добавить");
    auto *btnEdit = new QPushButton("Редактировать");
    auto *btnRemove = new QPushButton("Удалить");

    auto *btns = new QHBoxLayout();
    btns->addWidget(btnAdd);
    btns->addWidget(btnEdit);
    btns->addWidget(btnRemove);
    btns->addStretch();

    layout->addLayout(btns);

    setCentralWidget(central);

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddItem);
    connect(btnEdit, &QPushButton::clicked, this, &MainWindow::onEditItem);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::onRemoveItem);
}

void MainWindow::setupMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("Файл");

    fileMenu->addAction("Сохранить JSON", this, &MainWindow::onSaveJson);
    fileMenu->addAction("Загрузить JSON", this, &MainWindow::onLoadJson);
    fileMenu->addAction("Сохранить CSV", this, &MainWindow::onSaveCsv);
    fileMenu->addAction("Загрузить CSV", this, &MainWindow::onLoadCsv);
}

void MainWindow::onSearchChanged(const QString &text)
{
    m_proxy->setFilterFixedString(text);
}

void MainWindow::onAddItem()
{
    EquipmentDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        EquipmentItem it = dlg.getItem();
        if (it.name.isEmpty())
            return;
        m_model->addItem(it);
    }
}



void MainWindow::onEditItem()
{
    QModelIndex proxyIndex = m_view->currentIndex();
    if (!proxyIndex.isValid()) {
        QMessageBox::warning(this, "Редактирование", "Выберите строку");
        return;
    }

    int row = m_proxy->mapToSource(proxyIndex).row();
    EquipmentItem it = m_model->itemAt(row);

    EquipmentDialog dlg(this);
    dlg.setItem(it);

    if (dlg.exec() == QDialog::Accepted) {
        EquipmentItem newItem = dlg.getItem();
        m_model->setData(m_model->index(row, 1), newItem.name, Qt::EditRole);
        m_model->setData(m_model->index(row, 2), newItem.type, Qt::EditRole);
        m_model->setData(m_model->index(row, 3), newItem.location, Qt::EditRole);
        m_model->setData(m_model->index(row, 4), newItem.quantity, Qt::EditRole);
        m_model->setData(m_model->index(row, 5), newItem.condition, Qt::EditRole);

    }
}

void MainWindow::onRemoveItem()
{
    QModelIndex proxyIndex = m_view->currentIndex();
    if (!proxyIndex.isValid()) {
        QMessageBox::warning(this, "Удаление", "Выберите строку");
        return;
    }

    int row = m_proxy->mapToSource(proxyIndex).row();
    m_model->removeRow(row);
}

void MainWindow::onSaveJson()
{
    QString file = QFileDialog::getSaveFileName(this, "Сохранить JSON", "", "JSON (*.json)");
    if (file.isEmpty()) return;

    QString error;
    if (!m_model->saveToJson(file, error))
        QMessageBox::critical(this, "Ошибка", error);
}

void MainWindow::onLoadJson()
{
    QString file = QFileDialog::getOpenFileName(this, "Загрузить JSON", "", "JSON (*.json)");
    if (file.isEmpty()) return;

    QString error;
    if (!m_model->loadFromJson(file, error))
        QMessageBox::critical(this, "Ошибка", error);
}

void MainWindow::onSaveCsv()
{
    QString file = QFileDialog::getSaveFileName(this, "Сохранить CSV", "", "CSV (*.csv)");
    if (file.isEmpty()) return;

    QString error;
    if (!m_model->saveToCsv(file, error))
        QMessageBox::critical(this, "Ошибка", error);
}

void MainWindow::onLoadCsv()
{
    QString file = QFileDialog::getOpenFileName(this, "Загрузить CSV", "", "CSV (*.csv)");
    if (file.isEmpty()) return;

    QString error;
    if (!m_model->loadFromCsv(file, error))
        QMessageBox::critical(this, "Ошибка", error);
}
