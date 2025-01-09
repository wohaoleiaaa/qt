#include "historydialog.h"
#include "ui_historydialog.h"  // 包含 UI 文件生成的类
#include <QSettings>
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


void HistoryDialog::setHistory(const QStringList &history)//++++
{
    historyList = history;  // 初始化 historyList
    ui->historyList->clear();
    ui->historyList->addItems(historyList);
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


void HistoryDialog::onDeleteSelected()//++++
{
    // 获取选中的历史记录项
    QList<QListWidgetItem*> selectedItems = ui->historyList->selectedItems();

    // 遍历选中的项
    for (QListWidgetItem *item : selectedItems) {
        // 从 QListWidget 中删除项
        delete ui->historyList->takeItem(ui->historyList->row(item));

        // 从 historyList 中删除对应的历史记录
        historyList.removeOne(item->text());
    }

    // 保存更新后的历史记录到 QSettings
    saveHistory();
}

// 双击历史记录项
void HistoryDialog::onItemDoubleClicked(QListWidgetItem *item)
{
    // 发射信号，通知主窗口用户选择了某个历史记录
    emit historyItemSelected(item->text());
    close();  // 关闭对话框
}

void HistoryDialog::saveHistory()//++++
{
    QSettings settings("MyCompany", "MyEditor");
    settings.setValue("history", historyList);
}
