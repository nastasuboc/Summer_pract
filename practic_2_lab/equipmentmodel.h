#ifndef EQUIPMENTMODEL_H
#define EQUIPMENTMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QString>

struct EquipmentItem {
    int id;
    QString name;
    QString type;
    QString location;
    int quantity;
    QString condition;
};

class EquipmentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EquipmentModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void addItem(const EquipmentItem &item);
    EquipmentItem itemAt(int row) const;

    bool saveToJson(const QString &fileName, QString &error) const;
    bool loadFromJson(const QString &fileName, QString &error);

    bool saveToCsv(const QString &fileName, QString &error) const;
    bool loadFromCsv(const QString &fileName, QString &error);

private:
    QVector<EquipmentItem> m_items;
    bool isRowValid(int row) const;
};

#endif // EQUIPMENTMODEL_H
