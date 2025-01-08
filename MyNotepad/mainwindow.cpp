#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>
#include <QTabWidget>
#include "syntaxhighlighter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      tabWidget(new QTabWidget(this)) // 创建 QTabWidget

{
    ui->setupUi(this);
    setCentralWidget(tabWidget); // 设置 QTabWidget 为中央控件


    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("汉俊贤"));
    ui->statusbar->addPermanentWidget(author);


    // 初始化第一个标签页
    createNewTab();  // 默认创建一个新标签页
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()//关于界面
{
    AboutDialog dlg;
    dlg.exec();

}


void MainWindow::on_actionFind_triggered()//查找界面
{
    SearchDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionReplace_triggered()//替换界面
{
    ReplaceDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionNew_triggered() {//新建
    if (!userEditConfirmed()) {
        return;  // 如果当前编辑的文件有更改，确认是否保存后再进行操作
    }

    // 检查当前是否有空的标签页
    bool hasEmptyTab = false;
    for (int i = 0; i < tabWidget->count(); ++i) {
        QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(tabWidget->widget(i));
        if (textEdit && textEdit->toPlainText().isEmpty()) {
            tabWidget->setCurrentIndex(i);
            hasEmptyTab = true;
            break;
        }
    }

    // 如果没有空的标签页，则创建新的标签页
    if (!hasEmptyTab) {
        createNewTab();
    }
}


void MainWindow::createNewTab() {
    // 创建新的 QPlainTextEdit 作为文本编辑器
    QPlainTextEdit *newTextEdit = new QPlainTextEdit();

    // 设置语法高亮(添加了)
    new SyntaxHighlighter(newTextEdit->document());

    // 获取当前标签页的数量
    int tabCount = tabWidget->count();

    // 生成新标签页的名称（标签1、标签2、标签3...）
    QString tabName = tr("标签%1").arg(tabCount + 1);

    // 将新文本编辑器添加到新标签页中
    int index = tabWidget->addTab(newTextEdit, tabName);

    // 设置新标签页为当前选中的标签页
    tabWidget->setCurrentIndex(index);

    // 初始化状态（如清空文本，设置标题等）
    filePath = "";
    textChanged = false;

    // 清除新标签页中的内容
    newTextEdit->clear();

    // 设置窗口标题
    setWindowTitle(tr("新建文本文件~编辑器"));
}
void MainWindow::on_actionOpen_triggered() {//打开
    // 弹出文件选择对话框
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text files (*.txt)"));

    if (filename.isEmpty()) {
        return;  // 如果没有选择文件，则退出
    }

    // 打开文件并读取内容
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Open File"), tr("Unable to open the file."));
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();
    file.close();

    // 检查当前是否有空的标签页
    bool hasEmptyTab = false;
    for (int i = 0; i < tabWidget->count(); ++i) {
        QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(tabWidget->widget(i));
        if (textEdit && textEdit->toPlainText().isEmpty()) {
            // 如果找到空的标签页，则使用它来加载文件内容
            textEdit->setPlainText(text);
            tabWidget->setCurrentIndex(i);
            hasEmptyTab = true;
            break;
        }
    }

    // 如果没有空的标签页，则创建一个新的标签页
    if (!hasEmptyTab) {
        QPlainTextEdit *textEdit = new QPlainTextEdit();
        textEdit->setPlainText(text); // 显示文件内容

        // 将新标签页添加到 QTabWidget
        int index = tabWidget->addTab(textEdit, QFileInfo(filename).fileName());
        tabWidget->setCurrentIndex(index); // 将新标签页设为当前显示的标签页
    }

    // 更新窗口标题
    setWindowTitle(QFileInfo(filename).absoluteFilePath());
}


void MainWindow::on_actionSave_triggered() {//保存
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("保存文件"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的文本编辑器，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("保存文件"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 如果没有文件路径，表示是新建文件，需要弹出保存对话框
    if (filePath.isEmpty()) {
        QString filename = QFileDialog::getSaveFileName(this, tr("保存文件"), ".", tr("Text files (*.txt)"));
        if (filename.isEmpty()) {
            return;  // 如果用户没有选择文件路径，直接返回
        }
        filePath = filename;  // 获取用户选择的文件路径
    }

    // 创建一个文件对象，打开文件以进行写入
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("保存文件"), tr("无法打开文件进行写入！"));
        return;  // 打开文件失败时显示警告，并返回
    }

    // 使用 QTextStream 进行文本写入
    QTextStream out(&file);

    // 获取当前文本编辑器中的内容
    QString content = currentTextEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("保存文件"), tr("文件内容为空，无法保存！"));
        file.close();  // 关闭文件
        return;  // 文件内容为空时不进行保存
    }

    out << content;  // 将文本编辑器中的内容写入文件
    file.flush();  // 刷新文件缓冲区
    file.close();  // 关闭文件

    // 更新窗口标题，显示文件路径
    setWindowTitle(QFileInfo(filePath).absoluteFilePath());

    // 标记文件已保存
    textChanged = false;  // 修改标志设为 false，表示没有更改了
}


void MainWindow::on_actionSaveAs_triggered() {//另存为
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("另存为"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的文本编辑器，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("另存为"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 弹出另存为对话框，选择新的文件路径
    QString filename = QFileDialog::getSaveFileName(this, tr("另存为"), ".", tr("Text files (*.txt)"));
    if (filename.isEmpty()) {
        return;  // 如果用户没有选择文件路径，直接返回
    }

    // 创建一个文件对象，打开文件以进行写入
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("另存为"), tr("无法打开文件进行写入！"));
        return;  // 打开文件失败时显示警告，并返回
    }

    // 使用 QTextStream 进行文本写入
    QTextStream out(&file);

    // 获取当前文本编辑器中的内容
    QString content = currentTextEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("另存为"), tr("文件内容为空，无法保存！"));
        file.close();  // 关闭文件
        return;  // 文件内容为空时不进行保存
    }

    out << content;  // 将文本编辑器中的内容写入文件
    file.flush();  // 刷新文件缓冲区
    file.close();  // 关闭文件

    // 更新窗口标题，显示新文件路径
    setWindowTitle(QFileInfo(filename).absoluteFilePath());

    // 标记文件已保存
    textChanged = false;  // 修改标志设为 false，表示没有更改了
}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){

        QString path = (filePath !="") ? filePath : "无标题.txt";
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\"?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        int r = msg.exec();
        switch(r){
        case QMessageBox::Yes:
            on_actionSaveAs_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }
    return true;
}



void MainWindow::on_actionUndo_triggered()
{
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("撤销"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("撤销"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 调用撤销操作
    currentTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("重做"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("重做"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 调用重做操作
    currentTextEdit->redo();
}


void MainWindow::on_actionCut_triggered()
{
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("剪切"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("剪切"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 调用剪切操作
    currentTextEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("复制"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("复制"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 调用复制操作
    currentTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("粘贴"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("粘贴"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 调用粘贴操作
    currentTextEdit->paste();
}



