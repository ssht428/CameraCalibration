#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::~setting()
{
    delete ui;
}
/// @brief discard all changes and close dialog
void setting::on_btnCancel_clicked()
{
    this->close();
}
/// @brief save parameters to global setting
void setting::on_btnOK_clicked()
{


    this->close();
}
