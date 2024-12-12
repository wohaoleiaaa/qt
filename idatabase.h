#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>


class IDatabase : public QObject
{
    Q_OBJECT
public:

    static IDatabase &getInstance(){
        static IDatabase instance;
        return instance;
    }

    QString  userLogin(QString userName , QString password);

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &) = delete;
    void operator = (IDatabase const &) = delete ;

    QSqlDatabase database;

    void ininDatabase();//连接数据库

signals:

};

#endif // IDATABASE_H
