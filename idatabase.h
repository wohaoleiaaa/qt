#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include <QSqlTableModel>
#include <QItemSelectionModel>

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

public:
    bool initPatientModel();
    int addNewPatient();
    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();


    QSqlTableModel *patientTabModel;//数据模型

    QItemSelectionModel *thePatientSelection;//选择模型





};

#endif // IDATABASE_H
