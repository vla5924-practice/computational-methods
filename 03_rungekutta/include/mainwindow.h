#pragma once

#include <list>
#include <array>
#include <chrono>
#include <stdexcept>

#include <QMainWindow>
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QResizeEvent>

#include "abstractequationsystem.h"
#include "solutiontablemodel.h"
#include "rkmethodsolver.h"
#include "aboutdialog.h"
#include "helpdialog.h"

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
    void clear();
    void solve();

private:
    Ui::MainWindow *ui;
    AbstractEquationSystem *m_system;
    SolutionTableModel *m_solution;
};
