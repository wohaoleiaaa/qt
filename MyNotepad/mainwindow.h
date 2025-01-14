#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QLabel>
#include <QTabWidget>
#include <QPlainTextEdit>
#include "syntaxhighlighter.h"
#include <QRegularExpression>
#include <QDesktopServices>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QMouseEvent>
#include "historydialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionFind_triggered();

    void on_actionReplace_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_textEdit_textChanged();  // 文本内容变化时的槽函数

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionLightTheme_triggered();

    void on_actionDarkTheme_triggered();

    void on_actionFontColor_triggered();

    void on_actionToolBgdColor_triggered();

    void on_actionFontBgdColor_triggered();

    void on_actionWrap_triggered();

    void on_actionFont_triggered();

    void on_actiontoolbar_triggered();

    void on_actionStatusbar_triggered();

    void on_actionSelectAll_triggered();

    void on_actionExit_triggered();

    void onTabChanged(int index);  // 标签页切换时触发

    void on_textEdit_cursorPositionChanged();


    void on_actionShowline_triggered(bool checked);

    void on_actionHistory_triggered();  // 打开历史记录对话框

    void onHistoryItemSelected(const QString &filePath);  // 处理用户选择的历史记录

    void on_actionAddBookmark_triggered();

    void on_actionRemoveBookmark_triggered();

    void on_actionGotoBookmark_triggered();

    void on_actionAddFavorite_triggered();

    void on_actionRemoveFavorite_triggered();

    void on_actionOpenFavorite_triggered();

private:
    Ui::MainWindow *ui;

    QLabel *statusLabel;      // 用于显示总长度和总行数
    QLabel *statusCursorLabel; // 用于显示行号和列号

    QString filePath;

    bool textChanged;

    bool userEditConfirmed();

    QTabWidget *tabWidget;  // 用于管理标签页

    void createNewTab();  // 新建标签页的函数声明

    SyntaxHighlighter *currentHighlighter;  // 当前标签页的语法高亮器


    void setLightTheme();  // 设置浅色主题
    void setDarkTheme();   // 设置深色主题

    bool isWrapEnabled;  // 记录当前是否启用自动换行

    void highlightLinks(QPlainTextEdit *textEdit); // 高亮显示超链接

    QStringList historyList;  // 保存历史记录
    void saveHistory();  // 保存历史记录到文件
    void loadHistory();  // 从文件加载历史记录
    void updateHistory(const QString &filePath);  // 更新历史记录

    QMap<int, QString> bookmarks;  // 存储书签，键为行号，值为书签描述
    void saveBookmarks();  // 保存书签到 QSettings
    void loadBookmarks();  // 从 QSettings 加载书签

    QStringList favorites;  // 存储收藏的文件路径
    void saveFavorites();  // 保存收藏夹到 QSettings
    void loadFavorites();  // 从 QSettings 加载收藏夹

};
#endif // MAINWINDOW_H
