#ifndef DATAREQUESTDIALOG_H
#define DATAREQUESTDIALOG_H

#include <QDialog>

#include "firstapproximationtablemodel.h"

namespace Ui {
class DataRequestDialog;
}

class DataRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataRequestDialog(int eq_count, QWidget *parent = nullptr);
    ~DataRequestDialog();

    const Column& resultColumn() const;

private:
    Ui::DataRequestDialog *ui;
    FirstApproximationTableModel *m_model;
};

#endif // DATAREQUESTDIALOG_H
