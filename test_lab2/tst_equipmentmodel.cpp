#include <QtTest>
#include "equipmentmodel.h"

class TestEquipmentModel : public QObject
{
    Q_OBJECT

private slots:

    // --- 1. Добавление записи ---
    void testAddItem()
    {
        EquipmentModel model;

        int oldCount = model.rowCount();

        EquipmentItem it;
        it.id = 999;
        it.name = "Тестовый прибор";
        it.type = "Тип";
        it.location = "Лаборатория";
        it.quantity = 5;
        it.condition = "Исправен";

        model.addItem(it);

        QCOMPARE(model.rowCount(), oldCount + 1);

        EquipmentItem added = model.itemAt(model.rowCount() - 1);
        QCOMPARE(added.name, QString("Тестовый прибор"));
        QCOMPARE(added.quantity, 5);
    }

    // --- 2. Редактирование записи ---
    void testEditItem()
    {
        EquipmentModel model;

        QModelIndex idx = model.index(0, 1); // колонка "Название"
        QVERIFY(idx.isValid());

        model.setData(idx, "Новое имя", Qt::EditRole);

        EquipmentItem it = model.itemAt(0);
        QCOMPARE(it.name, QString("Новое имя"));
    }

    // --- 3. Удаление записи ---
    void testRemoveItem()
    {
        EquipmentModel model;

        int oldCount = model.rowCount();
        QVERIFY(oldCount > 0);

        model.removeRow(0);

        QCOMPARE(model.rowCount(), oldCount - 1);
    }

    // --- 4. Сохранение и загрузка JSON ---
    void testSaveLoadJson()
    {
        EquipmentModel model;

        QString error;
        QString file = "test_equipment.json";

        QVERIFY(model.saveToJson(file, error));

        EquipmentModel loaded;
        QVERIFY(loaded.loadFromJson(file, error));

        QCOMPARE(loaded.rowCount(), model.rowCount());

        EquipmentItem a = model.itemAt(0);
        EquipmentItem b = loaded.itemAt(0);

        QCOMPARE(a.name, b.name);
        QCOMPARE(a.quantity, b.quantity);
    }

    // --- 5. Сохранение и загрузка CSV ---
    void testSaveLoadCsv()
    {
        EquipmentModel model;

        QString error;
        QString file = "test_equipment.csv";

        QVERIFY(model.saveToCsv(file, error));

        EquipmentModel loaded;
        QVERIFY(loaded.loadFromCsv(file, error));

        QCOMPARE(loaded.rowCount(), model.rowCount());

        EquipmentItem a = model.itemAt(0);
        EquipmentItem b = loaded.itemAt(0);

        QCOMPARE(a.type, b.type);
        QCOMPARE(a.condition, b.condition);
    }
};

QTEST_MAIN(TestEquipmentModel)
#include "tst_equipmentmodel.moc"
