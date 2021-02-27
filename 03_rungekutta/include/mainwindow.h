#pragma once

#include <QMainWindow>
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QResizeEvent>
#include <QJsonArray>
#include <QJsonObject>

#include "config.h"
#include "abstracttelemetry.h"
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
    void solve();

private:
    Ui::MainWindow *ui;
    AbstractEquationSystem *m_system;
    SolutionTableModel *m_solution;
    AbstractTelemetry* m_telemetry;
};
