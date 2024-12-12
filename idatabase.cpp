#include "idatabase.h"
#include <QDebug>
#include <QSqlQuery>

void IDatabase::ininDatabase()//单例模式思想
{

    database = QSqlDatabase::addDatabase("QSQLITE");//添加SQLlite数据库驱动
    QString aFile = "E:/qt/projects/lab4sqlite.db";
    database.setDatabaseName(aFile);

    if(!database.open()){
        qDebug()<<"failed to opeen database";
    }
    else{
        qDebug()<<"open database is ok" << database.connectionName();
    }

}

QString IDatabase::userLogin(QString userName, QString password)
{
    //return "loginOK";

    QSqlQuery query;//查询出当前记录的所有字段
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    qDebug() << query.lastQuery()<<query.first();
    if(query.first() && query.value("username").isValid()){
        QString passwd = query.value("password").toString();
        if(passwd == password){
            qDebug()<<"login ok";
            return "loginOk";
        }
        else{
            qDebug()<<"wrong Password";
            return "wrongPassword";
        }
    }
    else{
        qDebug()<<"no such user";
        return "wrongUsername";
    }


    return "loginFailed";
}

IDatabase::IDatabase(QObject *parent) : QObject(parent)
{

    ininDatabase();

}
