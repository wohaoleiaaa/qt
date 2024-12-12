#include "idatabase.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
void IDatabase::ininDatabase()//单例模式思想
{

    database = QSqlDatabase::addDatabase("QSQLITE");//添加SQLlite数据库驱动
    QString aFile = "E:/qt/projects/Lab3/lab4a.db";
    database.setDatabaseName(aFile);

    if(!database.open()){
        qDebug()<<"failed to opeen database";
    }
    else{
        qDebug()<<"open database is ok" << database.connectionName();
    }

}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this , database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);//排序

    if(!(patientTabModel->select()))//查询数据
        return false;

    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;
}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());//在末尾添加一个记录

    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount()-1,1);//创建最后一行的ModelIndex
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
     patientTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query; // 查询出当前记录的所有字段
    query.prepare("select username, password from user where username = :USER");
    query.bindValue(":USER", userName);

    // 执行查询
    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError().text();
        return "loginFailed";
    }

    // 如果查询成功，获取结果
    if (query.first()) {
        // 打印调试信息
        qDebug() << "Username found: " << query.value("username").toString();

        // 获取密码并移除可能的空格
        QString passwd = query.value("password").toString().trimmed();
        qDebug() << "Password from database: " << passwd;

        // 比较输入的密码和数据库中的密码
        if (passwd == password) {
            qDebug() << "Login OK";
            return "loginOk";
        } else {
            qDebug() << "Wrong password entered";
            return "wrongPassword";
        }
    } else {
        qDebug() << "No user found with that username.";
        return "wrongUsername";
    }

    // 默认返回值
    return "loginFailed";
}

IDatabase::IDatabase(QObject *parent) : QObject(parent)
{

    ininDatabase();

}
