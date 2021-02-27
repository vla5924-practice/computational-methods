#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(AbstractEquationSystem* system, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(410, 450);
    ui->setupUi(this);
    ui->solution->hide();

    m_system = system;
    m_solution = nullptr;

    connect(ui->action_start, &QAction::triggered, this, &MainWindow::startOver);
    connect(ui->solve, &QPushButton::clicked, this, &MainWindow::solve);
    connect(ui->clear, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->action_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::startOver()
{

}

void MainWindow::clear()
{

}

void MainWindow::solve()
{

}
