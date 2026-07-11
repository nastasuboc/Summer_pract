/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *inputControls;
    QLabel *lblInput;
    QLineEdit *lineInput;
    QPushButton *btnCheck;
    QTableWidget *tableHistory;
    QWidget *layoutWidget_2;
    QHBoxLayout *topControls;
    QPushButton *btnNewGame;
    QLabel *lblStatus;
    QPushButton *btnRecords;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 40, 371, 31));
        inputControls = new QHBoxLayout(layoutWidget);
        inputControls->setObjectName("inputControls");
        inputControls->setContentsMargins(0, 0, 0, 0);
        lblInput = new QLabel(layoutWidget);
        lblInput->setObjectName("lblInput");

        inputControls->addWidget(lblInput);

        lineInput = new QLineEdit(layoutWidget);
        lineInput->setObjectName("lineInput");
        lineInput->setMaxLength(4);

        inputControls->addWidget(lineInput);

        btnCheck = new QPushButton(layoutWidget);
        btnCheck->setObjectName("btnCheck");

        inputControls->addWidget(btnCheck);

        tableHistory = new QTableWidget(centralwidget);
        if (tableHistory->columnCount() < 2)
            tableHistory->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableHistory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableHistory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableHistory->setObjectName("tableHistory");
        tableHistory->setGeometry(QRect(10, 80, 378, 452));
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 0, 371, 31));
        topControls = new QHBoxLayout(layoutWidget_2);
        topControls->setObjectName("topControls");
        topControls->setContentsMargins(0, 0, 0, 0);
        btnNewGame = new QPushButton(layoutWidget_2);
        btnNewGame->setObjectName("btnNewGame");

        topControls->addWidget(btnNewGame);

        lblStatus = new QLabel(layoutWidget_2);
        lblStatus->setObjectName("lblStatus");

        topControls->addWidget(lblStatus);

        btnRecords = new QPushButton(layoutWidget_2);
        btnRecords->setObjectName("btnRecords");

        topControls->addWidget(btnRecords);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblInput->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270 \321\207\320\270\321\201\320\273\320\276", nullptr));
        btnCheck->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\247\320\270\321\201\320\273\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        btnNewGame->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \320\270\320\263\321\200\320\260", nullptr));
        lblStatus->setText(QCoreApplication::translate("MainWindow", "  \320\230\320\263\321\200\320\260 \320\275\320\265 \320\275\320\260\321\207\320\260\321\202\320\260", nullptr));
        btnRecords->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\272\320\276\321\200\320\264\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
