#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QTabWidget>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr, QTabWidget *tabWidget = nullptr);  // 构造函数
    ~SearchDialog();  // 析构函数

private slots:
    void on_btFindNext_clicked();  // 查找下一个
    void on_btCancel_clicked();    // 取消

private:
    Ui::SearchDialog *ui;  // UI 对象
    QTabWidget *pTabWidget;  // 指向主窗口的 QTabWidget
    QPlainTextEdit* getCurrentTextEdit();  // 获取当前活动的 QPlainTextEdit
};

#endif // SEARCHDIALOG_H
