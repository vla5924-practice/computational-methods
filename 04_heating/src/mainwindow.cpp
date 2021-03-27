#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

#include "computation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button_start, &QPushButton::clicked, this, &MainWindow::startComputation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startComputation()
{
    m_start = std::chrono::high_resolution_clock::now();
    Computation* comp = new Computation(this);
    connect(comp, &Computation::progressChanged, this, &MainWindow::changeComputationProgress);
    connect(comp, &Computation::resultReady, this, &MainWindow::processComputationResult);
    connect(comp, &Computation::finished, comp, &QObject::deleteLater);
    comp->start();
}

void MainWindow::changeComputationProgress(int current, int total)
{
    if (current == 0) {
        ui->progress->setMinimum(0);
        ui->progress->setMaximum(total);
    }
    ui->progress->setValue(current);
}

void MainWindow::processComputationResult()
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - m_start;
    QString str = QString::number(duration.count() / 1000., 'g', 4) + " s.";
    ui->comp_time->setText(str);
}
