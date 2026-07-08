#pragma once

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger
{
public:
    static void log(const QString& text) {
        QFile file("hotelbooking.log");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        // В Qt 6 setCodec() больше нет — удалено
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
            << " - " << text << '\n';
    }
};

