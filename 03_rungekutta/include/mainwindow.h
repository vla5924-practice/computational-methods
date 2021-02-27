#pragma once

#include <QMainWindow>
#include <QWidget>

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
    void startOver();
    void solve();

private:
    Ui::MainWindow *ui;
    AbstractEquationSystem *m_system;
    SolutionTableModel *m_solution;
};
