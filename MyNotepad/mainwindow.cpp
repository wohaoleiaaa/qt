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
#include <QPlainTextEdit>
#include "codeeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      tabWidget(new QTabWidget(this)) // 创建 QTabWidget

{
    ui->setupUi(this);
    setCentralWidget(tabWidget); // 设置 QTabWidget 为中央控件

    // 初始化状态栏
    statusLabel = new QLabel(this);  // 用于显示总长度和总行数
    statusCursorLabel = new QLabel(this);  // 用于显示行号和列号
    ui->statusbar->addPermanentWidget(statusLabel);  // 添加到状态栏
    ui->statusbar->addPermanentWidget(statusCursorLabel);  // 添加到状态栏

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("汉俊贤"));
    ui->statusbar->addPermanentWidget(author);


    // 初始化第一个标签页
    createNewTab();  // 默认创建一个新标签页
    // 初始化默认主题
    setLightTheme();  // 或 setDarkTheme();
    // 设置 actionWrap 的初始状态
    ui->actionWrap->setChecked(isWrapEnabled);


    // 手动连接信号与槽
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    if (textEdit) {
        connect(textEdit, &QPlainTextEdit::textChanged, this, &MainWindow::on_textEdit_textChanged);
    }
    // 连接标签页切换信号
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
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


void MainWindow::on_actionFind_triggered() {
    SearchDialog dlg(this, tabWidget);  // 传入 tabWidget
    dlg.exec();
}


void MainWindow::on_actionReplace_triggered()//替换界面
{
    ReplaceDialog dlg(this, tabWidget);  // 传入 tabWidget
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

void MainWindow::on_textEdit_textChanged() {
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        return;  // 如果不是 QPlainTextEdit 类型，直接返回
    }

    // 如果文本是第一次被修改，则在窗口标题前添加 * 符号
    if (!textChanged) {
        QString title = this->windowTitle();
        if (!title.startsWith("*")) {
            this->setWindowTitle("*" + title);  // 添加 * 符号
        }
        textChanged = true;  // 标记文本已被修改
    }

    // 更新状态栏中的文本信息
    int length = currentTextEdit->toPlainText().length();  // 获取文本长度
    int lines = currentTextEdit->document()->lineCount();  // 获取文本行数

    // 更新状态栏中的长度和行数信息
    statusLabel->setText("Length: " + QString::number(length) + "   Lines: " + QString::number(lines));
}

bool MainWindow::userEditConfirmed() {
    // 如果有未保存的更改
    if (textChanged) {
        // 获取当前文件的路径，如果文件路径为空，则使用默认名称 "无标题.txt"
        QString path = (filePath != "") ? filePath : "无标题.txt";

        // 创建一个消息框，提示用户是否保存更改
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);  // 设置图标为问号
        msg.setWindowTitle("保存更改");      // 设置窗口标题
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\"?");  // 设置提示信息
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);  // 设置按钮

        // 显示消息框并获取用户的选择
        int result = msg.exec();

        // 根据用户的选择进行处理
        switch (result) {
        case QMessageBox::Yes:
            // 用户选择保存文件
            if (filePath.isEmpty()) {
                // 如果文件路径为空，调用“另存为”功能
                on_actionSaveAs_triggered();
            } else {
                // 如果文件路径不为空，直接保存文件
                on_actionSave_triggered();
            }
            break;

        case QMessageBox::No:
            // 用户选择不保存文件，重置 textChanged 标志
            textChanged = false;
            break;

        case QMessageBox::Cancel:
            // 用户选择取消操作，返回 false
            return false;
        }
    }

    // 如果没有未保存的更改，或者用户选择保存/不保存，返回 true
    return true;
}


void MainWindow::createNewTab() {
    // 创建新的 CodeEditor 作为文本编辑器
    CodeEditor *newTextEdit = new CodeEditor();

    // 设置语法高亮
    new SyntaxHighlighter(newTextEdit->document());

    // 设置默认换行模式
    newTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);  // 默认启用自动换行

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

    // 设置初始状态为显示行号
    on_actionShowline_triggered(false); // 调用槽函数，不显示行号

    // 连接信号与槽
    connect(newTextEdit, &CodeEditor::textChanged, this, &MainWindow::on_textEdit_textChanged);
    connect(newTextEdit, &CodeEditor::cursorPositionChanged, this, &MainWindow::on_textEdit_cursorPositionChanged);
}


void MainWindow::on_actionUndo_triggered()//撤回
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


void MainWindow::on_actionRedo_triggered()//恢复
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


void MainWindow::on_actionCut_triggered()//剪切
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


void MainWindow::on_actionCopy_triggered()//复制
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


void MainWindow::on_actionPaste_triggered()//粘贴
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


void MainWindow::on_actionLightTheme_triggered() {//浅色主题
    setLightTheme();
}

void MainWindow::on_actionDarkTheme_triggered() {//深色主题
    setDarkTheme();
}


void MainWindow::setLightTheme() {//浅色主题样式表
    qApp->setStyleSheet(R"(
        QPlainTextEdit {
            background-color: white;
            color: black;
        }
        QMenuBar {
            background-color: white;
            color: black;
        }
        QMenuBar::item {
            background-color: white;
            color: black;
        }
        QMenu {
            background-color: white;
            color: black;
        }
        QMenu::item {
            background-color: white;
            color: black;
        }
        QStatusBar {
            background-color: white;
            color: black;
        }
    )");
}

void MainWindow::setDarkTheme() {//深色主题样式表
    qApp->setStyleSheet(R"(
        QPlainTextEdit {
            background-color: #2d2d2d;
            color: #cccccc;
        }
        QMenuBar {
            background-color: #2d2d2d;
            color: #cccccc;
        }
        QMenuBar::item {
            background-color: #2d2d2d;
            color: #cccccc;
        }
        QMenu {
            background-color: #2d2d2d;
            color: #cccccc;
        }
        QMenu::item {
            background-color: #2d2d2d;
            color: #cccccc;
        }
        QStatusBar {
            background-color: #2d2d2d;
            color: #cccccc;
        }
    )");
}

void MainWindow::on_actionFontColor_triggered() {//字体颜色
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("字体颜色"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("字体颜色"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 打开颜色选择对话框
    QColor color = QColorDialog::getColor(Qt::black, this, tr("选择字体颜色"));
    if (color.isValid()) {  // 如果用户选择了有效的颜色
        // 获取当前文本编辑器的默认文本格式
        QTextCharFormat format;
        format.setForeground(color);  // 设置字体颜色

        // 将格式应用到整个文档
        QTextCursor cursor = currentTextEdit->textCursor();
        cursor.select(QTextCursor::Document);  // 选中整个文档
        cursor.mergeCharFormat(format);        // 应用格式
    }
}

void MainWindow::on_actionToolBgdColor_triggered() {//编辑器背景色
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("编辑器背景色"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("编辑器背景色"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 打开颜色选择对话框
    QColor color = QColorDialog::getColor(Qt::white, this, tr("选择编辑器背景色"));
    if (color.isValid()) {  // 如果用户选择了有效的颜色
        // 设置编辑器背景色
        QString styleSheet = QString("QPlainTextEdit { background-color: %1; }").arg(color.name());
        currentTextEdit->setStyleSheet(styleSheet);
    }
}


void MainWindow::on_actionFontBgdColor_triggered() {//字体背景色
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("文本背景色"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("文本背景色"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 打开颜色选择对话框
    QColor color = QColorDialog::getColor(Qt::yellow, this, tr("选择文本背景色"));
    if (color.isValid()) {  // 如果用户选择了有效的颜色
        // 获取当前文本编辑器的光标
        QTextCursor cursor = currentTextEdit->textCursor();

        // 如果用户选中了文本
        if (cursor.hasSelection()) {
            // 创建一个文本格式对象
            QTextCharFormat format;
            format.setBackground(color);  // 设置文本背景色

            // 将格式应用到选中的文本
            cursor.mergeCharFormat(format);
        } else {
            QMessageBox::warning(this, tr("文本背景色"), tr("请先选中文本！"));
        }
    }
}


void MainWindow::on_actionWrap_triggered() {//自动换行
    // 切换换行状态
    isWrapEnabled = !isWrapEnabled;

    // 遍历所有标签页
    for (int i = 0; i < tabWidget->count(); ++i) {
        QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(tabWidget->widget(i));
        if (textEdit) {
            // 设置自动换行模式
            if (isWrapEnabled) {
                textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);  // 启用自动换行
            } else {
                textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);  // 禁用自动换行
            }
        }
    }

    // 更新按钮状态
    ui->actionWrap->setChecked(isWrapEnabled);
}


void MainWindow::on_actionFont_triggered() {//字体
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("字体设置"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("字体设置"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 打开字体选择对话框
    bool ok;
    QFont font = QFontDialog::getFont(&ok, currentTextEdit->font(), this, tr("选择字体"));
    if (ok) {  // 如果用户点击了“确定”按钮
        // 将选择的字体应用到当前文本编辑器
        currentTextEdit->setFont(font);
    }
}

void MainWindow::on_actiontoolbar_triggered()//工具栏
{

    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actiontoolbar->setChecked(!visible);

}


void MainWindow::on_actionStatusbar_triggered()//状态栏
{

    bool visible = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionStatusbar->setChecked(!visible);

}



void MainWindow::on_actionSelectAll_triggered() {//全选
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        QMessageBox::warning(this, tr("全选"), tr("没有找到有效的文本编辑器！"));
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        QMessageBox::warning(this, tr("全选"), tr("当前标签页不是文本编辑器！"));
        return;  // 如果不是 QPlainTextEdit 类型，显示警告并返回
    }

    // 选中所有文本
    currentTextEdit->selectAll();
}


void MainWindow::on_actionExit_triggered() {//退出
    // 检查是否有未保存的更改
    if (!userEditConfirmed()) {
        return;  // 如果用户取消退出操作，直接返回
    }

    // 退出应用程序
    QApplication::quit();
}

void MainWindow::on_textEdit_cursorPositionChanged() {
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->currentWidget();
    if (!currentWidget) {
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        return;  // 如果不是 QPlainTextEdit 类型，直接返回
    }

    // 获取光标位置信息
    QTextCursor cursor = currentTextEdit->textCursor();
    int line = cursor.blockNumber() + 1;  // 获取当前行号（从 1 开始）
    int column = cursor.columnNumber() + 1;  // 获取当前列号（从 1 开始）

    // 更新状态栏中的光标位置信息
    statusCursorLabel->setText("Ln: " + QString::number(line) + "   Col: " + QString::number(column));
}

void MainWindow::onTabChanged(int index) {
    // 获取当前激活的标签页
    QWidget *currentWidget = tabWidget->widget(index);
    if (!currentWidget) {
        return;  // 如果没有找到有效的标签页，直接返回
    }

    // 假设当前标签页是 QPlainTextEdit 类型的文本编辑器
    QPlainTextEdit *currentTextEdit = qobject_cast<QPlainTextEdit*>(currentWidget);
    if (!currentTextEdit) {
        return;  // 如果不是 QPlainTextEdit 类型，直接返回
    }

    // 更新状态栏信息
    on_textEdit_textChanged();  // 更新总长度和总行数
    on_textEdit_cursorPositionChanged();  // 更新行号和列号
}

void MainWindow::on_actionShowline_triggered(bool checked)//显示行号
{
    // 遍历所有标签页
    for (int i = 0; i < tabWidget->count(); ++i) {
        CodeEditor *codeEditor = qobject_cast<CodeEditor*>(tabWidget->widget(i));
        if (codeEditor) {
            codeEditor->setLineNumberAreaVisible(checked); // 设置行号区域的显示状态
        }
    }
}

