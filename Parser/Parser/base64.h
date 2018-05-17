#ifndef BASE64_H
#define BASE64_H

#include <QByteArray>
#include <QTextStream>
#include <QFile>
#include <QDebug>

class base64
{
      public:
          base64();
          QByteArray read();
};

#endif // BASE64_H
