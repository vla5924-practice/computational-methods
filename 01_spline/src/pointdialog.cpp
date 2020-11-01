#include "pointdialog.h"
#include "ui_pointdialog.h"

PointDialog::PointDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PointDialog)
{
    ui->setupUi(this);
}

PointDialog::~PointDialog()
{
    delete ui;
}

QPointF PointDialog::resultPointF()
{
    QPointF result;
    result.setX(ui->doublespinbox_x->value());
    result.setY(ui->doublespinbox_y->value());
    return result;
}

