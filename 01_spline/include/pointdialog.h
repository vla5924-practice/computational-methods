#pragma once

#include <QDialog>

#include <QPointF>

namespace Ui {
    class PointDialog;
}

class PointDialog : public QDialog
{
    Q_OBJECT

protected:
    QPointF m_point;

public:
    explicit PointDialog(QWidget *parent = nullptr);
    ~PointDialog();

    QPointF resultPointF();

private:
    Ui::PointDialog *ui;
};

