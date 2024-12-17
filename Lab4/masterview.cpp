#include "masterview.h"
#include "ui_masterview.h"
#include <QtDebug>
#include "idatabase.h"

MasterView::MasterView(QWidget *parent,int index)
    : QWidget(parent),
     ui(new Ui::MasterView)
{
    ui->setupUi(this);

    //去除边框
    this->setWindowFlag(Qt::FramelessWindowHint);

    goLoginView();

    IDatabase::getInstance();//与数据库相关
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug()<<"goLoginView";

    loginView = new LoginView(this);

    pushWidgetToStackView(loginView);

    connect(loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));

}

void MasterView::goWelcomeView()
{
    qDebug()<<"goWelcomeView";

    welcomeView = new WelcomeView(this);

    pushWidgetToStackView(welcomeView);

    connect(welcomeView,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(welcomeView,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
    connect(welcomeView,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));
}

void MasterView::goDoctorView()
{
    qDebug()<<"goDoctorView";

    doctorView = new DoctorView(this);

    pushWidgetToStackView(doctorView);
}

void MasterView::goDepartmentView()
{
    qDebug()<<"goDepartmentView";

    departmentView = new DepartmentView(this);

    pushWidgetToStackView(departmentView);
}

void MasterView::goPatientEditView(int rowNo)
{
    qDebug()<<"goPatientEditView";

    patientEditView = new PatientEditView(this,rowNo);

    pushWidgetToStackView(patientEditView);


    connect(patientEditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));

}

void MasterView::goPatientView()
{
    qDebug()<<"goPatientView";

    patientView = new PatientView(this);

    pushWidgetToStackView(patientView);

    connect(patientView,SIGNAL(goPatientEditView(int)),this,SLOT(goPatientEditView(int)));

}

void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();

    if(count>1){
        ui->stackedWidget->setCurrentIndex(count - 2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(count - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;

    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);

    int count = ui->stackedWidget->count();

    ui->stackedWidget->setCurrentIndex(count - 1);

    ui->labelTitle->setText(widget->windowTitle());
}


void MasterView::on_btBack_clicked()
{
    goPreviousView();
}

//原来的代码错误的地方：进入欢迎界面点了注销之后，进入了登陆界面但是这时候返回可以点
//void MasterView::on_stackedWidget_currentChanged(int arg1)
//{
//    int count =ui->stackedWidget->count();
//    if(count>1)  ui->btBack->setEnabled(true);
//    else
//        ui->btBack->setEnabled(false);

//    QString title = ui->stackedWidget->currentWidget()->windowTitle();

//    if(title =="欢迎"){
//        ui->btLogout->setEnabled(true);
//        ui->btBack->setEnabled(false);
//    }
//    else
//        ui->btLogout->setEnabled(false);
//}



//void MasterView::on_btLogout_clicked()
//{
//    goPreviousView();
//}

//下面是chat的代码加了个在进入登录界面时禁用返回按钮就行了
void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    QString title = ui->stackedWidget->currentWidget()->windowTitle();

    // 1. 登录界面时禁用返回按钮
    if (title == "登录") {
        ui->btBack->setEnabled(false);
    } else if (title == "欢迎") {
        // 2. 欢迎界面时只能启用注销按钮，禁用返回按钮
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    } else {
        // 3. 其他页面时启用返回按钮
        ui->btBack->setEnabled(count > 1);
        ui->btLogout->setEnabled(false);
    }
}

void MasterView::on_btLogout_clicked()
{
    // 退出时跳转到登录界面
    goPreviousView();
    // 在进入登录界面时禁用返回按钮
    ui->btBack->setEnabled(false);
}
