﻿#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();

private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

private:
    Ui::setting *ui;
};

#endif // SETTING_H
