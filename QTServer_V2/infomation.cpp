#include "infomation.h"

Infomation::Infomation(QObject *parent) : QObject(parent)
{
    this->status=INFO_FREED;
    message="";
}

int Infomation::getStatus()
{
    return this->status;
}

void Infomation::setStatus(int status)
{
    this->status=status;
}

QString Infomation::getMessage()
{
    return this->message;
}

void Infomation::setMessage(const QString &message)
{
    this->message=message;
}

