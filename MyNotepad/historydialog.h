#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H
#include <QDialog>
#include <QStringList>
#include <QListWidgetItem>
namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    ~HistoryDialog();

    void setHistory(const QStringList &history);      // 设置历史记录
    QStringList getHistory() const;                   // 获取历史记录

signals:
    void historyItemSelected(const QString &filePath); // 信号：用户选择了某个历史记录

private slots:
    void onDeleteSelected();  // 删除选中的历史记录
    void onItemDoubleClicked(QListWidgetItem *item); // 双击历史记录项

private:
    Ui::HistoryDialog *ui;
    QStringList historyList;  // 存储历史记录的列表

    void saveHistory();  // 保存历史记录到 QSettings
};

#endif
