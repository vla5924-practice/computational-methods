#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p_chart = new SplineChart();
    ui->chart_view->setChart(p_chart);
    connect(ui->action_add_point, &QAction::triggered, this, &MainWindow::showAddPointDialog);
    connect(ui->action_clear_canvas, &QAction::triggered, this, &MainWindow::clearCanvas);
    connect(ui->action_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(p_chart, &SplineChart::splineHovered, this, &MainWindow::statusCoordinates);
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
        try
        {
            m_spline.insert(dialog.resultPointF());
            LoadingDialog l_dialog(p_chart);
            l_dialog.open();
            p_chart->load(m_spline);
        }
        catch (std::logic_error& e)
        {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void MainWindow::showAboutDialog()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::showHelpDialog()
{
    HelpDialog dialog;
    dialog.exec();
}

void MainWindow::clearCanvas()
{
    p_chart->clear();
    m_spline.removeAll();
}

void MainWindow::statusCoordinates(const QPointF &point)
{
    QString coords = QString("Coordinates: %1, %2").arg(point.x(), 0, 'f').arg(point.y(), 0, 'f');
    ui->statusbar->showMessage(coords, 10000);
}
