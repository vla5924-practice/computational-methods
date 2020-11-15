#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(const SplineChart* chart, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    connect(chart, &SplineChart::proceed, this, &LoadingDialog::updateState);
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}

void LoadingDialog::updateState(int current, int total, const QString &message)
{
    if (current > total)
    {
        emit done(QDialog::Accepted);
        return;
    }
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(current);
    ui->label->setText(message);
}
