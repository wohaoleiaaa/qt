#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QTabWidget>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr, QTabWidget *tabWidget = nullptr);
    ~ReplaceDialog();

private slots:
    void on_btFindNext_clicked();  // 查找下一个
    void on_btReplace_clicked();   // 替换
    void on_btReplaceAll_clicked(); // 全部替换
    void on_btCancel_clicked();    // 取消

private:
    Ui::ReplaceDialog *ui;
    QTabWidget *pTabWidget;
    QPlainTextEdit* getCurrentTextEdit();  // 获取当前活动的 QPlainTextEdit
};

#endif // REPLACEDIALOG_H
