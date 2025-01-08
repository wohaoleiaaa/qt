#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    // 去掉帮助按钮×旁边的？
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}
