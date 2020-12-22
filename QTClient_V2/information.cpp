#include "information.h"

Information::Information(QObject *parent) : QObject(parent)
{
    status=INFO_FREED;
    info="";
}

Information::Information(int status, QString info)
{
    status=INFO_FREED;
    info="";
}

QString Information::getInfo() const
{
    return info;
}

void Information::setInfo(const QString &value)
{
    info = value;
}
