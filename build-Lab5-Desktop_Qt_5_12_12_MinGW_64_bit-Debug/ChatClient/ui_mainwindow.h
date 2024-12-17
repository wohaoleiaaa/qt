/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *saveButton;
    QPushButton *logoutButton;
    QWidget *chatPage;
    QGridLayout *gridLayout;
    QFrame *loginFrame;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *usernameEdit;
    QLineEdit *serverEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(482, 350);
        MainWindow->setStyleSheet(QString::fromUtf8("#titleLabel {\n"
"    background: white;\n"
"    color: blue;\n"
"    font-size: 20px;\n"
"    border: none;\n"
"    border-bottom: 1px solid black;\n"
"    padding: 5px;\n"
"	font 24pt\"\351\273\221\344\275\223\";\n"
"	color:rgb(255,255,255);\n"
"    background-color:rgba(0,170,127,255);\n"
"\n"
"}\n"
"\n"
"#mainFrame {\n"
"    border: none;\n"
"    background: white;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background: rgb(159, 142, 255);\n"
"    border: 1px solid gray;\n"
"    padding: 10px;\n"
"    border-radius: 25px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setLayoutDirection(Qt::LeftToRight);
        titleLabel->setStyleSheet(QString::fromUtf8(""));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        verticalLayout_3 = new QVBoxLayout(loginPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEdit = new QTextEdit(loginPage);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        horizontalLayout->addWidget(textEdit);

        listWidget = new QListWidget(loginPage);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(listWidget);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit = new QLineEdit(loginPage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        saveButton = new QPushButton(loginPage);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout_2->addWidget(saveButton);

        logoutButton = new QPushButton(loginPage);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));

        horizontalLayout_2->addWidget(logoutButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(loginPage);
        chatPage = new QWidget();
        chatPage->setObjectName(QString::fromUtf8("chatPage"));
        gridLayout = new QGridLayout(chatPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        loginFrame = new QFrame(chatPage);
        loginFrame->setObjectName(QString::fromUtf8("loginFrame"));
        loginFrame->setStyleSheet(QString::fromUtf8(""));
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(loginFrame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(loginFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(loginFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        usernameEdit = new QLineEdit(loginFrame);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, usernameEdit);

        serverEdit = new QLineEdit(loginFrame);
        serverEdit->setObjectName(QString::fromUtf8("serverEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, serverEdit);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        pushButton = new QPushButton(loginFrame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        gridLayout->addWidget(loginFrame, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(106, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(106, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 2, 1, 1, 1);

        stackedWidget->addWidget(chatPage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\201\212\345\244\251\345\256\244\345\256\242\346\210\267\347\253\257", nullptr));
        titleLabel->setText(QApplication::translate("MainWindow", "\350\264\244\345\223\245\350\201\212\345\244\251\345\256\244", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        logoutButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\235\200\357\274\232", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\346\230\265\347\247\260\357\274\232", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
