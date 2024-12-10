#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patienteditview.h"
#include  "patientview.h"
#include "welcomeview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientEditView();
    void goPatientView();
    void goPreviousView();


private:

    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterView *ui;

    LoginView * loginView;
    WelcomeView * welcomeView;
    DoctorView * doctorView;
    DepartmentView * departmentView;
    PatientEditView * patientEditView;
    PatientView * patientView;


};
#endif // MASTERVIEW_H
