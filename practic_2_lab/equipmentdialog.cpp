#include "equipmentdialog.h"
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

EquipmentDialog::EquipmentDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Оборудование");

    nameEdit      = new QLineEdit(this);
    typeEdit      = new QLineEdit(this);
    locationEdit  = new QLineEdit(this);
    quantitySpin  = new QSpinBox(this);
    conditionEdit = new QLineEdit(this);

    quantitySpin->setRange(0, 999);

    auto *form = new QFormLayout();
    form->addRow("Название:", nameEdit);
    form->addRow("Тип:", typeEdit);
    form->addRow("Местоположение:", locationEdit);
    form->addRow("Количество:", quantitySpin);
    form->addRow("Состояние:", conditionEdit);

    auto *btnOk = new QPushButton("OK");
    auto *btnCancel = new QPushButton("Отмена");

    auto *buttons = new QHBoxLayout();
    buttons->addStretch();
    buttons->addWidget(btnOk);
    buttons->addWidget(btnCancel);

    auto *main = new QVBoxLayout(this);
    main->addLayout(form);
    main->addLayout(buttons);

    connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void EquipmentDialog::setItem(const EquipmentItem &it)
{
    nameEdit->setText(it.name);
    typeEdit->setText(it.type);
    locationEdit->setText(it.location);
    quantitySpin->setValue(it.quantity);
    conditionEdit->setText(it.condition);
}

EquipmentItem EquipmentDialog::getItem()
{
    // Проверка всех полей
    if (nameEdit->text().trimmed().isEmpty() ||
        typeEdit->text().trimmed().isEmpty() ||
        locationEdit->text().trimmed().isEmpty() ||
        conditionEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Все поля должны быть заполнены!");
        return EquipmentItem{}; // пустой объект → MainWindow не добавит запись
    }

    if (quantitySpin->value() < 0) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Количество не может быть отрицательным!");
        return EquipmentItem{};
    }

    // Если всё корректно — возвращаем запись
    EquipmentItem it;
    it.name = nameEdit->text();
    it.type = typeEdit->text();
    it.location = locationEdit->text();
    it.quantity = quantitySpin->value();
    it.condition = conditionEdit->text();
    return it;
}

