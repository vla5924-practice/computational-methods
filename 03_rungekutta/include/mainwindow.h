#pragma once

#include <vector>
#include <array>

#include <QMainWindow>
#include <QWidget>

#include "abstractaccuratesolution.h"
#include "abstractequationsystem.h"
#include "solutiontablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AbstractEquationSystem* system, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showAboutDialog();
    void showHelpDialog();
    void showPlotsDialog();
    void startOver();
    void solve();

private:
    Ui::MainWindow *ui;
    AbstractEquationSystem *m_system;
    SolutionTableModel *m_solution;

    std::vector<std::array<double, 4>> m_approx;
    AbstractAccurateSolution* m_accur;
};
