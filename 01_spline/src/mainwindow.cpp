#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_add_point, &QAction::triggered, this, &MainWindow::showAddPointDialog);

    p_chart = new SplineChart();
    ui->chart_view->setChart(p_chart);
}

MainWindow::~MainWindow()
{
    delete p_chart;

    delete ui;
}

void MainWindow::showAddPointDialog()
{
    PointDialog dialog;
    dialog.exec();
    if (dialog.result() == QDialog::Accepted)
    {
        m_spline.insert(dialog.resultPointF());
        p_chart->load(m_spline);
    }
}
