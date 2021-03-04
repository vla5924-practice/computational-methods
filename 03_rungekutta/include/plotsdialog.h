#pragma once

#include <QDialog>

#include "qcustomplot.h"
#include "abstractplot.h"

namespace Ui {
class PlotsDialog;
}

class PlotsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotsDialog(const std::vector<std::array<double, 4>>& approx,
                         AbstractAccurateSolution* accur,
                         QWidget *parent = nullptr);
    ~PlotsDialog();

public slots:
    void showFullPlot();

private:
    Ui::PlotsDialog *ui;
};
