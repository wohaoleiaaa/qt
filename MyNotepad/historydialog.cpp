#include "historydialog.h"
#include "ui_historydialog.h"  // 包含 UI 文件生成的类

// 构造函数
HistoryDialog::HistoryDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);  // 加载 UI 文件

    // 连接信号与槽
    connect(ui->deleteButton, &QPushButton::clicked, this, &HistoryDialog::onDeleteSelected);
    connect(ui->closeButton, &QPushButton::clicked, this, &HistoryDialog::close);
    connect(ui->historyList, &QListWidget::itemDoubleClicked, this, &HistoryDialog::onItemDoubleClicked);
}

// 析构函数
HistoryDialog::~HistoryDialog()
{
    delete ui;
}

// 设置历史记录
void HistoryDialog::setHistory(const QStringList &history)
{
    ui->historyList->clear();
    ui->historyList->addItems(history);
}

// 获取历史记录
QStringList HistoryDialog::getHistory() const
{
    QStringList history;
    for (int i = 0; i < ui->historyList->count(); ++i) {
        history.append(ui->historyList->item(i)->text());
    }
    return history;
}

// 删除选中的历史记录
void HistoryDialog::onDeleteSelected()
{
    // 删除选中的历史记录
    QList<QListWidgetItem*> selectedItems = ui->historyList->selectedItems();
    for (QListWidgetItem *item : selectedItems) {
        delete ui->historyList->takeItem(ui->historyList->row(item));
    }
}

// 双击历史记录项
void HistoryDialog::onItemDoubleClicked(QListWidgetItem *item)
{
    // 发射信号，通知主窗口用户选择了某个历史记录
    emit historyItemSelected(item->text());
    close();  // 关闭对话框
}
