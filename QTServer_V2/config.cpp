#include "config.h"

Config::Config(QObject *parent) : QObject(parent)
{
    //读取配置文件
    set= new QSettings("./DatabaseConfig.ini");
}

Config::~Config()
{
    delete set;
}

QVariant Config::readConfig(const QString &key)
{
    return set->value(key);

}

void Config::saveConfig()
{
    //数据库
    set->setValue("base","QMYSQL");
    set->setValue("hostname","localhost");
    set->setValue("username","root");
    set->setValue("password","root");
    set->setValue("database","planeticket");
    set->setValue("table","ticket");

    /*服务器端使用的端口*/
    set->setValue("SERVER_PORT_NO",8889);

    /*客户端与服务器端使用的消息类型定义*/
    set->setValue("INITIAL_VALUE",65535);

    /*客户端使用的消息代码含义*/
    set->setValue("DISCONNECT",0);
    set->setValue("BUY_TICKET",1);
    set->setValue("INQUIRE_ONE",2);
    set->setValue("INQUIRE_ALL",3);
    set->setValue("ADD_TICKET",4);
    set->setValue("UPDATE_TICKET",5);
    set->setValue("DELETE_TICKET",6);

    /*服务器端使用的消息代码含义*/
    set->setValue("BUY_SUCCEED",255);
    set->setValue("BUY_FAILED",256);
    set->setValue("INQUIRE_SUCCEED",257);
    set->setValue("UNKNOWN_CODE",258);

}

void Config::addConfig(const QString &key, QVariant &value)
{
    set->setValue(key,value);
}
