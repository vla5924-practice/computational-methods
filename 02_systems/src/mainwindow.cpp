#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_workspace.push_back(ui->label_system);
    m_workspace.push_back(ui->table_system);
    m_workspace.push_back(ui->combobox_method);
    m_workspace.push_back(ui->pushbutton_solve);
    m_workspace.push_back(ui->pushbutton_solve_all);
    m_workspace.push_back(ui->checkbox_time_measurement);

    m_system = nullptr;
    m_solution = nullptr;

    ui->table_system->horizontalHeader()->setStretchLastSection(false);
    ui->table_system->verticalHeader()->setVisible(true);
    ui->table_system->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->table_system->setSelectionMode(QAbstractItemView::SingleSelection);

    m_solvers[GaussMethod] = new GaussMethodSolver;

    ui->progress->hide();
    ui->label_solution->hide();
    ui->table_solution->hide();
    ui->label_fastest_method->hide();
    hideWorkspace();
    connect(ui->action_start, &QAction::triggered, this, &MainWindow::startOver);
    connect(ui->pushbutton_solve, &QPushButton::clicked, this, &MainWindow::solveWithChosenMethod);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startOver()
{
    bool ok = false;
    int eq_count = QInputDialog::getInt(this,
                                        "Number of unknown variables",
                                        "Enter a number of unknown variables "
                                        "(from 1 to 16, this also will be a number of equations)",
                                        1, 1, 16, 1, &ok);
    if (!ok)
        return;
    m_eq_count = eq_count;
    ui->progress->hide();
    ui->label_solution->hide();
    ui->table_solution->hide();
    showWorkspace();
    if (m_system != nullptr)
        delete m_system;
    m_system = new SystemTableModel(m_eq_count, ui->table_system);
    ui->table_system->setModel(m_system);
}

void MainWindow::showWorkspace()
{
    for (auto& widget : m_workspace)
        widget->show();
}

void MainWindow::hideWorkspace()
{
    for (auto& widget : m_workspace)
        widget->hide();
}

void MainWindow::enableWorkspace()
{
    for (auto& widget : m_workspace)
        widget->setDisabled(false);
}

void MainWindow::disableWorkspace()
{
    for (auto& widget : m_workspace)
        widget->setDisabled(true);
}

void MainWindow::solveWithChosenMethod()
{
    disableWorkspace();
    ui->progress->show();
    int method = ui->combobox_method->currentIndex();
    const Matrix &A = m_system->matrix();
    const Column &b = m_system->column();
    Column result = m_solvers[method]->solve(A, b);

    std::vector<Column> solutions = { {1, 2, 3}, {4, 5, 6}};
    std::vector<double> durations = { 0.1, 2.3 };
    if (m_solution != nullptr)
        delete m_system;
    m_solution = new SolutionTableModel(solutions, durations, ui->table_system);
    ui->table_solution->setModel(m_solution);

    ui->label_solution->show();
    ui->table_solution->show();
    ui->label_fastest_method->show();
    //enableWorkspace();
    //ui->progress->hide();
}
