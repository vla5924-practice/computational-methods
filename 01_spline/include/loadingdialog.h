#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QString>

#include "splinechart.h"

namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(const SplineChart* chart, QWidget *parent = nullptr);
    ~LoadingDialog();

public slots:
    void updateState(int current, int total, const QString& message);

private:
    Ui::LoadingDialog *ui;
};

#endif // LOADINGDIALOG_H
