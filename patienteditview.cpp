#include "patienteditview.h"
#include "ui_patienteditview.h"
#include <QSqlTableModel>
#include "idatabase.h"
#include <QDebug>
#include <QSqlError>

PatientEditView::PatientEditView(QWidget *parent , int index) :
    QWidget(parent),
    ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel;
    dataMapper->setModel(IDatabase::getInstance().patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard, tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight, tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight, tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditMobile, tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDateEditDOB, tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);

}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()
{
//    IDatabase::getInstance().submitPatientEdit();

//    emit goPreviousView();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel;

    // 获取当前记录的索引
    int currentIndex = dataMapper->currentIndex();

    // 标记字段是否被修改
    bool isModified = false;

    // 检查字段并手动更新字段
    if (ui->dbEditName->text() != tabModel->data(tabModel->index(currentIndex, tabModel->fieldIndex("NAME"))).toString()) {
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("NAME")), ui->dbEditName->text());
        isModified = true;
    }

    if (ui->dbSpinHeight->value() != tabModel->data(tabModel->index(currentIndex, tabModel->fieldIndex("HEIGHT"))).toDouble()) {
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("HEIGHT")), ui->dbSpinHeight->value());
        isModified = true;
    }

    if (ui->dbSpinWeight->value() != tabModel->data(tabModel->index(currentIndex, tabModel->fieldIndex("WEIGHT"))).toDouble()) {
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("WEIGHT")), ui->dbSpinWeight->value());
        isModified = true;
    }

    if (ui->dbEditMobile->text() != tabModel->data(tabModel->index(currentIndex, tabModel->fieldIndex("MOBILEPHONE"))).toString()) {
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("MOBILEPHONE")), ui->dbEditMobile->text());
        isModified = true;
    }

    if (ui->dbDateEditDOB->date() != tabModel->data(tabModel->index(currentIndex, tabModel->fieldIndex("DOB"))).toDate()) {
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("DOB")), ui->dbDateEditDOB->date());
        isModified = true;
    }

    if (ui->dbComboSex->currentText() != tabModel->data(tabModel->index(currentIndex, tabModel->fieldIndex("SEX"))).toString()) {
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("SEX")), ui->dbComboSex->currentText());
        isModified = true;
    }

    // 只有在数据发生更改时才提交
    if (isModified) {
        if (tabModel->submitAll()) {
            qDebug() << "数据已保存到数据库";
            tabModel->select();  // 重新加载数据
            dataMapper->setCurrentIndex(currentIndex);  // 保持当前索引
        } else {
            QSqlError error = tabModel->lastError();
            qDebug() << "保存数据失败：" << error.text();
        }
    } else {
        qDebug() << "没有字段被修改，提交失败";
    }
}


void PatientEditView::on_pushButton_2_clicked()
{
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();

}




