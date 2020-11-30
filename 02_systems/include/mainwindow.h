#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <array>
#include <chrono>

#include <QMainWindow>
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QResizeEvent>

#include "method.h"
#include "systemtablemodel.h"
#include "solutiontablemodel.h"
#include "lesystemsolver.h"
#include "gaussmethodsolver.h"
#include "kramermethodsolver.h"
#include "seidelmethodsolver.h"
#include "simpleiterationmethodsolver.h"
#include "upperrelaxationmethodsolver.h"
#include "jacobimethodsolver.h"
#include "datarequestdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

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
    void solveWithAllMethods();
    void toggleSolution();

protected:
    void resizeEvent(QResizeEvent *event) override;
    static QString methodName(int method);

private:
    Ui::MainWindow *ui;
    std::list<QWidget*> m_workspace;
    int m_eq_count;
    SystemTableModel *m_system;
    SolutionTableModel *m_solution;
    std::array<LESystemSolver*, METHODS_COUNT> m_solvers;
};

#endif // MAINWINDOW_H
