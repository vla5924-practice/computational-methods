#pragma once

#include <chrono>

#include <QMainWindow>

#include "computationresult.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startComputation();
    void changeComputationProgress(int current, int total);
    void processComputationResult(ComputationResult result);
    void toggleGreenPlot();
    void showAboutDialog();

private:
    Ui::MainWindow *ui;

    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};
