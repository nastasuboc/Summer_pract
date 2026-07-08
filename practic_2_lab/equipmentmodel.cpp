#include "equipmentmodel.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QBrush>

EquipmentModel::EquipmentModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    for (int i = 0; i < 10; ++i) {
        EquipmentItem it;
        it.id = i + 1;
        it.name = QString("Прибор %1").arg(i + 1);
        it.type = "Осциллограф";
        it.location = "Лаборатория";
        it.quantity = (i % 5) + 1;
        it.condition = "Исправен";
        m_items.append(it);
    }
}

int EquipmentModel::rowCount(const QModelIndex &) const { return m_items.size(); }
int EquipmentModel::columnCount(const QModelIndex &) const { return 6; }

QVariant EquipmentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !isRowValid(index.row()))
        return {};

    const EquipmentItem &it = m_items[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0: return it.id;
        case 1: return it.name;
        case 2: return it.type;
        case 3: return it.location;
        case 4: return it.quantity;
        case 5: return it.condition;
        }
    }
    return {};
}

QVariant EquipmentModel::headerData(int section, Qt::Orientation o, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (o == Qt::Horizontal) {
        switch (section) {
        case 0: return "ID";
        case 1: return "Название";
        case 2: return "Тип";
        case 3: return "Местоположение";
        case 4: return "Количество";
        case 5: return "Состояние";
        }
    }
    return section + 1;
}

Qt::ItemFlags EquipmentModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool EquipmentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole || !isRowValid(index.row()))
        return false;

    EquipmentItem &it = m_items[index.row()];

    switch (index.column()) {
    case 0: it.id = value.toInt(); break;
    case 1: it.name = value.toString(); break;
    case 2: it.type = value.toString(); break;
    case 3: it.location = value.toString(); break;
    case 4: it.quantity = value.toInt(); break;
    case 5: it.condition = value.toString(); break;
    }

    emit dataChanged(index, index);
    return true;
}

bool EquipmentModel::insertRows(int row, int count, const QModelIndex &)
{
    beginInsertRows({}, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        EquipmentItem it{ m_items.size() + 1, "Новое оборудование", "Тип", "Лаборатория", 1, "Исправен" };
        m_items.insert(row, it);
    }
    endInsertRows();
    return true;
}

bool EquipmentModel::removeRows(int row, int count, const QModelIndex &)
{
    beginRemoveRows({}, row, row + count - 1);
    for (int i = 0; i < count; ++i)
        m_items.removeAt(row);
    endRemoveRows();
    return true;
}

void EquipmentModel::addItem(const EquipmentItem &item)
{
    beginInsertRows({}, m_items.size(), m_items.size());
    m_items.append(item);
    endInsertRows();
}

EquipmentItem EquipmentModel::itemAt(int row) const
{
    if (!isRowValid(row)) return {};
    return m_items[row];
}

bool EquipmentModel::isRowValid(int row) const
{
    return row >= 0 && row < m_items.size();
}

bool EquipmentModel::saveToJson(const QString &fileName, QString &error) const
{
    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly)) {
        error = "Не удалось открыть файл";
        return false;
    }

    QJsonArray arr;
    for (auto &it : m_items) {
        QJsonObject o;
        o["id"] = it.id;
        o["name"] = it.name;
        o["type"] = it.type;
        o["location"] = it.location;
        o["quantity"] = it.quantity;
        o["condition"] = it.condition;
        arr.append(o);
    }

    f.write(QJsonDocument(arr).toJson());
    return true;
}

bool EquipmentModel::loadFromJson(const QString &fileName, QString &error)
{
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        error = "Не удалось открыть файл";
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isArray()) {
        error = "Некорректный JSON";
        return false;
    }

    QVector<EquipmentItem> newItems;
    for (auto v : doc.array()) {
        auto o = v.toObject();
        newItems.append({
            o["id"].toInt(),
            o["name"].toString(),
            o["type"].toString(),
            o["location"].toString(),
            o["quantity"].toInt(),
            o["condition"].toString()
        });
    }

    beginResetModel();
    m_items = newItems;
    endResetModel();
    return true;
}

bool EquipmentModel::saveToCsv(const QString &fileName, QString &error) const
{
    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        error = "Не удалось открыть файл";
        return false;
    }

    QTextStream out(&f);
    out << "id;name;type;location;quantity;condition\n";

    for (auto &it : m_items)
        out << it.id << ";" << it.name << ";" << it.type << ";"
            << it.location << ";" << it.quantity << ";" << it.condition << "\n";

    return true;
}

bool EquipmentModel::loadFromCsv(const QString &fileName, QString &error)
{
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = "Не удалось открыть файл";
        return false;
    }

    QTextStream in(&f);
    QVector<EquipmentItem> newItems;

    in.readLine(); // skip header

    while (!in.atEnd()) {
        QStringList p = in.readLine().split(';');
        if (p.size() < 6) continue;

        newItems.append({
            p[0].toInt(),
            p[1],
            p[2],
            p[3],
            p[4].toInt(),
            p[5]
        });
    }

    beginResetModel();
    m_items = newItems;
    endResetModel();
    return true;
}
