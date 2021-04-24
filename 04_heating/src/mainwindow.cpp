#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <limits>

#include <QAction>
#include <QCheckBox>
#include <QMessageBox>
#include <QPushButton>

#include "aboutdialog.h"
#include "computation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button_start, &QPushButton::clicked, this, &MainWindow::startComputation);
    connect(ui->check_show, &QCheckBox::toggled, this, &MainWindow::toggleGreenPlot);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startComputation()
{
    double T = ui->param_t->value();
    double L = ui->param_l->value();
    double tau = ui->step_t->value();
    double h = ui->step_x->value();

    if (T < std::numeric_limits<double>::epsilon() || L < std::numeric_limits<double>::epsilon() || tau < std::numeric_limits<double>::epsilon() || h < std::numeric_limits<double>::epsilon())
    {
        QMessageBox::warning(this, "Invalid parameters", "All these values must be greater than zero: rod length (L), heating time (T), x step size, t step size.");
        return;
    }

    m_start = std::chrono::high_resolution_clock::now();
    ui->comp_time->setText("Computing...");
    ui->button_start->setEnabled(false);
    ui->check_show->setChecked(false);

    double b0 = ui->param_b0->value();
    double b1 = ui->param_b1->value();
    double b2 = ui->param_b2->value();
    double phi1 = ui->param_phi1->value();
    double phi2 = ui->param_phi2->value();

    Computation* comp = new Computation(b0, b1, b2, phi1, phi2, T, L, tau, h, this);
    connect(comp, &Computation::progressChanged, this, &MainWindow::changeComputationProgress);
    connect(comp, &Computation::resultReady, this, &MainWindow::processComputationResult);
    connect(comp, &Computation::finished, comp, &QObject::deleteLater);
    comp->start();
}

void MainWindow::changeComputationProgress(int current, int total)
{
    if (current == 0)
    {
        ui->progress->setMinimum(0);
        ui->progress->setMaximum(total);
    }
    ui->progress->setValue(current);
}

void MainWindow::processComputationResult(ComputationResult result)
{
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(result.x, result.phi);
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->addGraph();
    ui->plot->graph(1)->setData(result.x, result.grid);
    ui->plot->graph(1)->setPen(QPen(Qt::red));
    ui->plot->addGraph();
    ui->plot->graph(2)->setData(result.x, result.grid_part_a);
    ui->plot->graph(2)->setPen(QPen(Qt::green));
    ui->plot->graph(2)->setVisible(false);
    ui->plot->xAxis->setLabel("t");
    ui->plot->yAxis->setLabel("x");
    ui->plot->graph(1)->rescaleAxes();
    ui->plot->graph(0)->rescaleAxes(true);
    ui->plot->graph(2)->rescaleAxes(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot->replot();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - m_start;
    QString str = QString::number(duration.count() / 1000., 'g', 4) + " s.";
    ui->comp_time->setText(str);
    ui->button_start->setEnabled(true);
    ui->check_show->setEnabled(true);
}

void MainWindow::toggleGreenPlot()
{
    if (ui->plot->graphCount() >= 3)
    {
        ui->plot->graph(2)->setVisible(!ui->plot->graph(2)->visible());
        ui->plot->replot();
    }
}

void MainWindow::showAboutDialog()
{
    AboutDialog dialog;
    dialog.exec();
}
