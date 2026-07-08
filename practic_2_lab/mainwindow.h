#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTableView;
class QLineEdit;
class QSortFilterProxyModel;
class EquipmentModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddItem();
    void onEditItem();
    void onRemoveItem();
    void onSearchChanged(const QString &text);

    void onSaveJson();
    void onLoadJson();
    void onSaveCsv();
    void onLoadCsv();

private:
    EquipmentModel *m_model;
    QSortFilterProxyModel *m_proxy;
    QTableView *m_view;
    QLineEdit *m_search;

    void setupUi();
    void setupMenu();
};

#endif // MAINWINDOW_H
