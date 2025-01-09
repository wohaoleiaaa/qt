#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QListWidgetItem>
// 包含 UI 文件生成的类
namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QWidget *parent = nullptr); // 构造函数
    ~HistoryDialog(); // 析构函数

    void setHistory(const QStringList &history);      // 设置历史记录
    QStringList getHistory() const;                   // 获取历史记录

signals:
    void historyItemSelected(const QString &filePath); // 信号：用户选择了某个历史记录

private slots:
    void onDeleteSelected();  // 删除选中的历史记录
    void onItemDoubleClicked(QListWidgetItem *item); // 双击历史记录项

private:
    Ui::HistoryDialog *ui;  // 指向 UI 的指针
};

#endif // HISTORYDIALOG_H
