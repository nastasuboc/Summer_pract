#ifndef EQUIPMENTDIALOG_H
#define EQUIPMENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include "equipmentmodel.h"

class EquipmentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EquipmentDialog(QWidget *parent = nullptr);

    EquipmentItem getItem();
    void setItem(const EquipmentItem &item);

private:
    QLineEdit *nameEdit;
    QLineEdit *typeEdit;
    QLineEdit *locationEdit;
    QSpinBox  *quantitySpin;
    QLineEdit *conditionEdit;
};

#endif // EQUIPMENTDIALOG_H
