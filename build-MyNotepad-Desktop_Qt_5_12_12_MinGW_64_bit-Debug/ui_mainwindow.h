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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFind;
    QAction *actionReplace;
    QAction *actionFont;
    QAction *actionShowline;
    QAction *actionWrap;
    QAction *actiontoolbar;
    QAction *actionStatusbar;
    QAction *actionSelectAll;
    QAction *actionAbout;
    QAction *actionFontColor;
    QAction *actionToolBgdColor;
    QAction *actionFontBgdColor;
    QAction *actionLightTheme;
    QAction *actionDarkTheme;
    QAction *actionHistory;
    QAction *actionAddBookmark;
    QAction *actionRemoveBookmark;
    QAction *actionGotoBookmark;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_E;
    QMenu *menu_O;
    QMenu *menu_V;
    QMenu *menu_H;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 600);
        MainWindow->setMinimumSize(QSize(900, 600));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon3);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon4);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon5);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon6);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon7);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/img/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon8);
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/img/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFind->setIcon(icon9);
        actionReplace = new QAction(MainWindow);
        actionReplace->setObjectName(QString::fromUtf8("actionReplace"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/img/replace.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReplace->setIcon(icon10);
        actionFont = new QAction(MainWindow);
        actionFont->setObjectName(QString::fromUtf8("actionFont"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/img/font.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFont->setIcon(icon11);
        actionShowline = new QAction(MainWindow);
        actionShowline->setObjectName(QString::fromUtf8("actionShowline"));
        actionShowline->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/img/showline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowline->setIcon(icon12);
        actionWrap = new QAction(MainWindow);
        actionWrap->setObjectName(QString::fromUtf8("actionWrap"));
        actionWrap->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/img/wrap.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWrap->setIcon(icon13);
        actiontoolbar = new QAction(MainWindow);
        actiontoolbar->setObjectName(QString::fromUtf8("actiontoolbar"));
        actiontoolbar->setCheckable(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/img/toolbar.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiontoolbar->setIcon(icon14);
        actionStatusbar = new QAction(MainWindow);
        actionStatusbar->setObjectName(QString::fromUtf8("actionStatusbar"));
        actionStatusbar->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/img/statusbar.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStatusbar->setIcon(icon15);
        actionSelectAll = new QAction(MainWindow);
        actionSelectAll->setObjectName(QString::fromUtf8("actionSelectAll"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionFontColor = new QAction(MainWindow);
        actionFontColor->setObjectName(QString::fromUtf8("actionFontColor"));
        actionToolBgdColor = new QAction(MainWindow);
        actionToolBgdColor->setObjectName(QString::fromUtf8("actionToolBgdColor"));
        actionFontBgdColor = new QAction(MainWindow);
        actionFontBgdColor->setObjectName(QString::fromUtf8("actionFontBgdColor"));
        actionLightTheme = new QAction(MainWindow);
        actionLightTheme->setObjectName(QString::fromUtf8("actionLightTheme"));
        actionDarkTheme = new QAction(MainWindow);
        actionDarkTheme->setObjectName(QString::fromUtf8("actionDarkTheme"));
        actionHistory = new QAction(MainWindow);
        actionHistory->setObjectName(QString::fromUtf8("actionHistory"));
        actionAddBookmark = new QAction(MainWindow);
        actionAddBookmark->setObjectName(QString::fromUtf8("actionAddBookmark"));
        actionRemoveBookmark = new QAction(MainWindow);
        actionRemoveBookmark->setObjectName(QString::fromUtf8("actionRemoveBookmark"));
        actionGotoBookmark = new QAction(MainWindow);
        actionGotoBookmark->setObjectName(QString::fromUtf8("actionGotoBookmark"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEdit = new QPlainTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMinimumSize(QSize(2, 0));

        horizontalLayout->addWidget(textEdit);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_E = new QMenu(menubar);
        menu_E->setObjectName(QString::fromUtf8("menu_E"));
        menu_O = new QMenu(menubar);
        menu_O->setObjectName(QString::fromUtf8("menu_O"));
        menu_V = new QMenu(menubar);
        menu_V->setObjectName(QString::fromUtf8("menu_V"));
        menu_H = new QMenu(menubar);
        menu_H->setObjectName(QString::fromUtf8("menu_H"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_E->menuAction());
        menubar->addAction(menu_O->menuAction());
        menubar->addAction(menu_V->menuAction());
        menubar->addAction(menu_H->menuAction());
        menu->addAction(actionNew);
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionSaveAs);
        menu->addSeparator();
        menu->addAction(actionExit);
        menu_E->addAction(actionUndo);
        menu_E->addAction(actionRedo);
        menu_E->addAction(actionCut);
        menu_E->addAction(actionCopy);
        menu_E->addAction(actionPaste);
        menu_E->addSeparator();
        menu_E->addAction(actionFind);
        menu_E->addAction(actionReplace);
        menu_E->addSeparator();
        menu_E->addAction(actionSelectAll);
        menu_O->addAction(actionWrap);
        menu_O->addAction(actionShowline);
        menu_O->addAction(actionFont);
        menu_O->addAction(actionFontColor);
        menu_O->addSeparator();
        menu_O->addAction(actionFontBgdColor);
        menu_O->addAction(actionToolBgdColor);
        menu_O->addAction(actionLightTheme);
        menu_O->addAction(actionDarkTheme);
        menu_V->addAction(actiontoolbar);
        menu_V->addAction(actionStatusbar);
        menu_V->addAction(actionHistory);
        menu_H->addAction(actionAbout);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSaveAs);
        toolBar->addSeparator();
        toolBar->addAction(actionUndo);
        toolBar->addAction(actionRedo);
        toolBar->addAction(actionCut);
        toolBar->addAction(actionCopy);
        toolBar->addAction(actionPaste);
        toolBar->addSeparator();
        toolBar->addAction(actionFind);
        toolBar->addAction(actionReplace);
        toolBar->addSeparator();
        toolBar->addAction(actionFont);
        toolBar->addAction(actionShowline);
        toolBar->addAction(actionWrap);
        toolBar->addSeparator();
        toolBar->addAction(actiontoolbar);
        toolBar->addAction(actionStatusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\226\207\346\234\254\347\274\226\350\276\221\345\231\250", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230(&S)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSaveAs->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272(&A)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSaveAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200(&U)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionUndo->setToolTip(QApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215(&)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRedo->setToolTip(QApplication::translate("MainWindow", "\346\201\242\345\244\215", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionCut->setText(QApplication::translate("MainWindow", "\345\211\252\345\210\207(&T)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCut->setToolTip(QApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        actionCopy->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266(&C)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionPaste->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264(&P)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionPaste->setToolTip(QApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionFind->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFind->setToolTip(QApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionFind->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_NO_SHORTCUT
        actionReplace->setText(QApplication::translate("MainWindow", "\346\233\277\346\215\242(&R)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionReplace->setToolTip(QApplication::translate("MainWindow", "\346\233\277\346\215\242", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionReplace->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_NO_SHORTCUT
        actionFont->setText(QApplication::translate("MainWindow", "\345\255\227\344\275\223(&F)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFont->setToolTip(QApplication::translate("MainWindow", "\345\255\227\344\275\223", nullptr));
#endif // QT_NO_TOOLTIP
        actionShowline->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\241\214\345\217\267(&L)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionShowline->setToolTip(QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\241\214\345\217\267", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionShowline->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_NO_SHORTCUT
        actionWrap->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214(&W)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionWrap->setToolTip(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214", nullptr));
#endif // QT_NO_TOOLTIP
        actiontoolbar->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\240\217(&T)", nullptr));
#ifndef QT_NO_TOOLTIP
        actiontoolbar->setToolTip(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\240\217", nullptr));
#endif // QT_NO_TOOLTIP
        actionStatusbar->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217(&S)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionStatusbar->setToolTip(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217", nullptr));
#endif // QT_NO_TOOLTIP
        actionSelectAll->setText(QApplication::translate("MainWindow", "\345\205\250\351\200\211(&A)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSelectAll->setToolTip(QApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSelectAll->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
#endif // QT_NO_TOOLTIP
        actionFontColor->setText(QApplication::translate("MainWindow", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFontColor->setToolTip(QApplication::translate("MainWindow", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
#endif // QT_NO_TOOLTIP
        actionToolBgdColor->setText(QApplication::translate("MainWindow", "\347\274\226\350\276\221\345\231\250\350\203\214\346\231\257\350\211\262", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToolBgdColor->setToolTip(QApplication::translate("MainWindow", "\347\274\226\350\276\221\345\231\250\350\203\214\346\231\257\350\211\262", nullptr));
#endif // QT_NO_TOOLTIP
        actionFontBgdColor->setText(QApplication::translate("MainWindow", "\345\255\227\344\275\223\350\203\214\346\231\257\350\211\262", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFontBgdColor->setToolTip(QApplication::translate("MainWindow", "\345\255\227\344\275\223\350\203\214\346\231\257\350\211\262", nullptr));
#endif // QT_NO_TOOLTIP
        actionLightTheme->setText(QApplication::translate("MainWindow", "\346\265\205\350\211\262\344\270\273\351\242\230", nullptr));
#ifndef QT_NO_TOOLTIP
        actionLightTheme->setToolTip(QApplication::translate("MainWindow", "\346\265\205\350\211\262\344\270\273\351\242\230", nullptr));
#endif // QT_NO_TOOLTIP
        actionDarkTheme->setText(QApplication::translate("MainWindow", "\346\267\261\350\211\262\344\270\273\351\242\230", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDarkTheme->setToolTip(QApplication::translate("MainWindow", "\346\267\261\350\211\262\344\270\273\351\242\230", nullptr));
#endif // QT_NO_TOOLTIP
        actionHistory->setText(QApplication::translate("MainWindow", "\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
#ifndef QT_NO_TOOLTIP
        actionHistory->setToolTip(QApplication::translate("MainWindow", "\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
#endif // QT_NO_TOOLTIP
        actionAddBookmark->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\271\246\347\255\276", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddBookmark->setToolTip(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\271\246\347\255\276", nullptr));
#endif // QT_NO_TOOLTIP
        actionRemoveBookmark->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\271\246\347\255\276", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRemoveBookmark->setToolTip(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\271\246\347\255\276", nullptr));
#endif // QT_NO_TOOLTIP
        actionGotoBookmark->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\344\271\246\347\255\276", nullptr));
#ifndef QT_NO_TOOLTIP
        actionGotoBookmark->setToolTip(QApplication::translate("MainWindow", "\345\212\240\350\275\275\344\271\246\347\255\276", nullptr));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_E->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", nullptr));
        menu_O->setTitle(QApplication::translate("MainWindow", "\346\240\274\345\274\217(&O)", nullptr));
        menu_V->setTitle(QApplication::translate("MainWindow", "\346\237\245\347\234\213(&V)", nullptr));
        menu_H->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
