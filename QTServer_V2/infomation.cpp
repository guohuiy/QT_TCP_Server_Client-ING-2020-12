#include "infomation.h"

Infomation::Infomation(QObject *parent) : QObject(parent)
{
    message="";
}


QString Infomation::getMessage()
{
    return this->message;
}

void Infomation::setMessage(const QString &message)
{
    this->message=message;
}

