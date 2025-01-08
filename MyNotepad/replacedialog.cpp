#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);

    // 去掉帮助按钮×旁边的？
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}
