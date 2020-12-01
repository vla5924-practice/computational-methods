#include "mainwindow.h"
#include "ui_mainwindow.h"

constexpr double EPSILON = 1e-4;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setMinimumSize(600, 300);
    ui->setupUi(this);
    m_workspace.push_back(ui->label_system);
    m_workspace.push_back(ui->table_system);
    m_workspace.push_back(ui->combobox_method);
    m_workspace.push_back(ui->pushbutton_solve);
    m_workspace.push_back(ui->pushbutton_solve_all);
    m_workspace.push_back(ui->pushbutton_toggle);

    m_system = nullptr;
    m_solution = nullptr;

    ui->table_system->horizontalHeader()->setStretchLastSection(false);
    ui->table_system->verticalHeader()->setVisible(true);
    ui->table_system->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->table_system->setSelectionMode(QAbstractItemView::SingleSelection);

    m_solvers[GaussMethod] = new GaussMethodSolver;
    m_solvers[KramerMethod] = new KramerMethodSolver;
    m_solvers[SeidelMethod] = new SeidelMethodSolver;
    m_solvers[JacobiMethod] = new JacobiMethodSolver;
    m_solvers[SimpleIterationMethod] = new SimpleIterationMethodSolver;
    m_solvers[UpperRelaxationMethod] = new UpperRelaxationMethodSolver;

    ui->progress->hide();
    ui->label_solution->hide();
    ui->table_solution->hide();
    ui->label_fastest_method->hide();
    hideWorkspace();
    connect(ui->action_start, &QAction::triggered, this, &MainWindow::startOver);
    connect(ui->pushbutton_solve, &QPushButton::clicked, this, &MainWindow::solveWithChosenMethod);
    connect(ui->pushbutton_solve_all, &QPushButton::clicked, this, &MainWindow::solveWithAllMethods);
    connect(ui->pushbutton_toggle, &QPushButton::clicked, this, &MainWindow::toggleSolution);
}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto& solver : m_solvers)
        delete solver;
}

void MainWindow::startOver()
{
    bool ok = false;
    int eq_count = QInputDialog::getInt(this,
                                        "Number of unknown variables",
                                        "Enter a number of unknown variables "
                                        "(from 1 to 16, this also will be a number of equations)",
                                        2, 2, 16, 1, &ok);
    if (!ok)
        return;
    m_eq_count = eq_count;
    ui->progress->hide();
    ui->label_solution->hide();
    ui->table_solution->hide();
    ui->label_fastest_method->hide();
    showWorkspace();
    enableWorkspace();
    if (m_system != nullptr)
        delete m_system;
    m_system = new SystemTableModel(m_eq_count, ui->table_system);
    ui->table_system->setModel(m_system);
    ui->pushbutton_toggle->setDisabled(true);
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
    const Matrix &A = m_system->matrix();
    if (LESystemSolver::determinant(A) == 0)
    {
        QMessageBox::warning(this, "Error", "Matrix determinant equals to zero.");
        return;
    }

    using Clock = std::chrono::high_resolution_clock;
    int method = ui->combobox_method->currentIndex();
    DataRequestDialog dialog(m_eq_count);
    if (m_solvers[method]->needApproximation())
    {
        dialog.exec();
        if (dialog.result() != QDialog::Accepted)
            return;
    }
    disableWorkspace();
    ui->progress->show();
    try {
        const Column &b = m_system->column();
        const Column &x = dialog.resultColumn();
        Clock::time_point t1 = Clock::now();
        Column result = m_solvers[method]->solve(A, b, x, EPSILON);
        Clock::time_point t2 = Clock::now();
        std::chrono::duration<double> duration = t2 - t1;
        if (m_solution != nullptr)
            delete m_solution;
        m_solution = new SolutionTableModel({{ method, result, duration.count() }});
        ui->table_solution->setModel(m_solution);
        ui->label_solution->show();
        ui->table_solution->show();
        ui->label_fastest_method->hide();
    }  catch (std::runtime_error& error) {
        QMessageBox::information(this,
                                 "Warning",
                                 methodName(method) + " cannot be executed. " + error.what());
    }
    enableWorkspace();
    ui->progress->hide();
}

void MainWindow::solveWithAllMethods()
{
    const Matrix &A = m_system->matrix();
    if (LESystemSolver::determinant(A) == 0)
    {
        QMessageBox::warning(this, "Error", "Matrix determinant equals to zero.");
        return;
    }

    using Clock = std::chrono::high_resolution_clock;
    DataRequestDialog dialog(m_eq_count);
    dialog.exec();
    if (dialog.result() != QDialog::Accepted)
        return;
    disableWorkspace();
    ui->progress->show();
    const Column &b = m_system->column();
    const Column &x = dialog.resultColumn();
    std::vector<Solution> solutions;
    double fastest = std::numeric_limits<double>::max();
    int fastest_method = GaussMethod;
    bool was_errors = false;
    QString errors;
    for (int method = 0; method < METHODS_COUNT; method++)
    {
        try {
            Clock::time_point t1 = Clock::now();
            Column result = m_solvers[method]->solve(A, b, x, EPSILON);
            Clock::time_point t2 = Clock::now();
            std::chrono::duration<double> duration = t2 - t1;
            double duration_s = duration.count();
            if (duration_s < fastest)
            {
                fastest = duration_s;
                fastest_method = method;
            }
            solutions.push_back({ method, result, duration_s });
        }  catch (std::runtime_error& error) {
            was_errors = true;
            errors += methodName(method) + " cannot be executed. " + error.what() + "\n";
        }

    }
    if (m_solution != nullptr)
        delete m_solution;
    ui->label_fastest_method->setText("The fastest method is " + methodName(fastest_method) + ".");
    m_solution = new SolutionTableModel(solutions);
    ui->table_solution->setModel(m_solution);
    ui->label_solution->show();
    ui->table_solution->show();
    ui->label_fastest_method->show();
    if (was_errors)
        QMessageBox::information(this, "Warning", errors);
    enableWorkspace();
    ui->progress->hide();
}

void MainWindow::toggleSolution()
{
    bool hidden = ui->table_solution->isHidden();
    if (hidden)
    {
        ui->label_solution->show();
        ui->table_solution->show();
        ui->label_fastest_method->show();
        ui->pushbutton_toggle->setText("Hide last solution");
    }
    else
    {
        ui->label_solution->hide();
        ui->table_solution->hide();
        ui->label_fastest_method->hide();
        ui->pushbutton_toggle->setText("Show last solution");
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->verticalLayoutWidget->setFixedWidth(event->size().width() - 20);
    ui->verticalLayoutWidget->setFixedHeight(event->size().height() - 60);
}

QString MainWindow::methodName(int method)
{
    if (method == GaussMethod)
        return "Gauss method";
    if (method == KramerMethod)
        return "Kramer method";
    if (method == SeidelMethod)
        return "Seidel method";
    if (method == SimpleIterationMethod)
        return "Simple iteration method";
    if (method == UpperRelaxationMethod)
        return "Upper relaxation method";
    if (method == JacobiMethod)
        return "Jacobi method";
    return "Unknown method";
}
