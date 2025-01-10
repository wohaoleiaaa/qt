#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QTabWidget>

ReplaceDialog::ReplaceDialog(QWidget *parent, QTabWidget *tabWidget)
    : QDialog(parent),
      ui(new Ui::ReplaceDialog),
      pTabWidget(tabWidget)
{
    ui->setupUi(this);

    // 默认选择向下查找
    ui->rbDown->setChecked(true);

    // 去掉帮助按钮×旁边的？
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

// 获取当前活动的 QPlainTextEdit
QPlainTextEdit* ReplaceDialog::getCurrentTextEdit() {
    if (!pTabWidget) {
        return nullptr;
    }

    QWidget *currentWidget = pTabWidget->currentWidget();
    if (!currentWidget) {
        return nullptr;
    }

    return qobject_cast<QPlainTextEdit*>(currentWidget);
}

void ReplaceDialog::on_btFindNext_clicked()//查找下一个
{
    QPlainTextEdit *currentTextEdit = getCurrentTextEdit();
    if (!currentTextEdit) {
        QMessageBox::warning(this, "错误", "没有找到有效的文本编辑器！");
        return;
    }

    QString target = ui->searchText->text();
    if (target.isEmpty()) {
        QMessageBox::warning(this, "错误", "查找内容不能为空！");
        return;
    }

    QString text = currentTextEdit->toPlainText();
    QTextCursor cursor = currentTextEdit->textCursor();
    int index = -1;

    // 判断查找方向
    if (ui->rbDown->isChecked()) {
        // 向下查找
        index = text.indexOf(target, cursor.position(),
                             ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            cursor.setPosition(index);
            cursor.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            currentTextEdit->setTextCursor(cursor);
        }
    } else if (ui->rbUp->isChecked()) {
        // 向上查找
        index = text.lastIndexOf(target, cursor.position() - 1,
                                 ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            cursor.setPosition(index + target.length());
            cursor.setPosition(index, QTextCursor::KeepAnchor);
            currentTextEdit->setTextCursor(cursor);
        }
    }

    // 如果没有找到目标文本
    if (index < 0) {
        QMessageBox msg(this);
        msg.setWindowTitle("提示");
        msg.setText(QString("未找到: ") + target);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}

void ReplaceDialog::on_btReplace_clicked()//替换
{
    QPlainTextEdit *currentTextEdit = getCurrentTextEdit();
    if (!currentTextEdit) {
        QMessageBox::warning(this, "错误", "没有找到有效的文本编辑器！");
        return;
    }

    QString target = ui->searchText->text();
    QString to = ui->targetText->text();

    if (target.isEmpty() || to.isEmpty()) {
        QMessageBox::warning(this, "错误", "查找内容和替换内容不能为空！");
        return;
    }

    QTextCursor cursor = currentTextEdit->textCursor();
    QString selectedText = cursor.selectedText();

    // 如果选中的文本与查找内容匹配，则替换
    if (selectedText == target) {
        cursor.insertText(to);
    }

    // 查找下一个匹配项
    on_btFindNext_clicked();
}

void ReplaceDialog::on_btReplaceAll_clicked()//全部替换
{
    QPlainTextEdit *currentTextEdit = getCurrentTextEdit();
    if (!currentTextEdit) {
        QMessageBox::warning(this, "错误", "没有找到有效的文本编辑器！");
        return;
    }

    QString target = ui->searchText->text();
    QString to = ui->targetText->text();

    if (target.isEmpty() || to.isEmpty()) {
        QMessageBox::warning(this, "错误", "查找内容和替换内容不能为空！");
        return;
    }

    QString text = currentTextEdit->toPlainText();
    text.replace(target, to, ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

    // 更新文本编辑器内容
    currentTextEdit->setPlainText(text);
}

void ReplaceDialog::on_btCancel_clicked()
{
    this->close();  // 关闭替换对话框
}
