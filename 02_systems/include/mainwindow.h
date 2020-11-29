#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>

#include <QMainWindow>
#include <QInputDialog>
#include <QWidget>

#include "systemtablemodel.h"

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

private:
    Ui::MainWindow *ui;
    std::list<QWidget*> m_workspace;
    int m_eq_count;
    SystemTableModel *m_system;
};

#endif // MAINWINDOW_H
