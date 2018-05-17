#include "base64.h"
#include <QByteArray>
#include <QTextStream>
#include <QFile>
#include <QDebug>

base64::base64()
{
}

QByteArray base64::read(){
QByteArray data;
QFile file("/home/racso/Project#2/Bella.mp3");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    qDebug()<<"No se encuentra el archivo" ;

QTextStream in(&file);
while (!in.atEnd()) {
    QString line = in.readLine();
    data.append(line.toUtf8().toBase64());
}

file.close();
return data;
}

