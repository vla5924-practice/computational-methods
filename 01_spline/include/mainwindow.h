#pragma once

#include <QMainWindow>

#include "pointdialog.h"
#include "spline.h"
#include "splinechart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SplineChart *p_chart;
    Spline m_spline;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void showAddPointDialog();
};
