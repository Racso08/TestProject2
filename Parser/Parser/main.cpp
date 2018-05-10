#include "mainwindow.h"
//#include "base64.h"
#include <QApplication>
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QByteArray data;
    QFile file("/home/racso/Project#2/Bella.mp3");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 2;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        data.append(line.toUtf8().toBase64());
    }

    file.close();

    return a.exec();
}
