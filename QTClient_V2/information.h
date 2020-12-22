#ifndef INFORMATION_H
#define INFORMATION_H

#include <QObject>

class Information : public QObject
{
    Q_OBJECT
public:
    enum{INFO_OCCUPIED,INFO_FREED};
    explicit Information(QObject *parent = nullptr);
    Information(int status,QString info);
    QString getInfo() const;
    void setInfo(const QString &value);

private:
    int status;
    QString info;
signals:

};

#endif // INFORMATION_H
