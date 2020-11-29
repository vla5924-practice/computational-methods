#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <array>

#include <QMainWindow>
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>

#include "systemtablemodel.h"
#include "solutiontablemodel.h"
#include "lesystemsolver.h"
#include "gaussmethodsolver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Method
    {
        GaussMethod,
        KramerMethod,
        SeidelMethod,
        SimpleIterationMethod,
        UpperRelaxationMethod
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startOver();
    void showWorkspace();
    void hideWorkspace();
    void enableWorkspace();
    void disableWorkspace();
    void solveWithChosenMethod();

private:
    Ui::MainWindow *ui;
    std::list<QWidget*> m_workspace;
    int m_eq_count;
    SystemTableModel *m_system;
    SolutionTableModel *m_solution;
    std::array<LESystemSolver*, 6> m_solvers;
};

#endif // MAINWINDOW_H
