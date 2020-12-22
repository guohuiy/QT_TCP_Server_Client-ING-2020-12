#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>

/*完成配置文件操作*/
class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    ~Config();
    QVariant readConfig(const QString &key);
    void saveConfig();
    void addConfig(const QString &key,QVariant &value);

    const int DISCONNECT=0;
private:
    QSettings* set;
signals:

};

#endif // CONFIG_H
