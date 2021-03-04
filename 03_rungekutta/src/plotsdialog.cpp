#include "plotsdialog.h"
#include "ui_plotsdialog.h"

#include <QVector>
#include <QPushButton>

using namespace QCP;

PlotsDialog::PlotsDialog(const std::vector<std::array<double, 4>>& approx,
                         AbstractAccurateSolution* accur,
                         QWidget *parent)
    : QDialog(parent), ui(new Ui::PlotsDialog)
{
    ui->setupUi(this);
    int steps_count = static_cast<int>(approx.size());
    QVector<double> t(steps_count);
    QVector<double> x_app(steps_count), y_app(steps_count), z_app(steps_count);
    QVector<double> x_acc(steps_count), y_acc(steps_count), z_acc(steps_count);
    for (int i = 0; i < steps_count; i++)
    {
        t[i]     = approx[i][3];
        x_app[i] = approx[i][0];
        y_app[i] = approx[i][1];
        z_app[i] = approx[i][2];
        x_acc[i] = accur->f1(t[i]);
        y_acc[i] = accur->f2(t[i]);
        z_acc[i] = accur->f3(t[i]);
    }

    ui->plot_x->addGraph();
    ui->plot_x->graph(0)->setData(t, x_app);
    ui->plot_x->graph(0)->setPen(QPen(Qt::red));
    ui->plot_x->addGraph();
    ui->plot_x->graph(1)->setData(t, x_acc);
    ui->plot_x->xAxis->setLabel("t");
    ui->plot_x->yAxis->setLabel("x'");
    ui->plot_x->graph(0)->rescaleAxes();
    ui->plot_x->graph(1)->rescaleAxes(true);
    ui->plot_x->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_x->replot();

    ui->plot_y->addGraph();
    ui->plot_y->graph(0)->setData(t, y_app);
    ui->plot_y->graph(0)->setPen(QPen(Qt::red));
    ui->plot_y->addGraph();
    ui->plot_y->graph(1)->setData(t, y_acc);
    ui->plot_y->xAxis->setLabel("t");
    ui->plot_y->yAxis->setLabel("y'");
    ui->plot_y->graph(0)->rescaleAxes();
    ui->plot_y->graph(1)->rescaleAxes(true);
    ui->plot_y->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_y->replot();

    ui->plot_z->addGraph();
    ui->plot_z->graph(0)->setData(t, z_app);
    ui->plot_z->graph(0)->setPen(QPen(Qt::red));
    ui->plot_z->addGraph();
    ui->plot_z->graph(1)->setData(t, z_acc);
    ui->plot_z->xAxis->setLabel("t");
    ui->plot_z->yAxis->setLabel("z'");
    ui->plot_z->graph(0)->rescaleAxes();
    ui->plot_z->graph(1)->rescaleAxes(true);
    ui->plot_z->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_z->replot();

    ui->eq_1->setText(" = " + accur->f1Str());
    ui->eq_2->setText(" = " + accur->f2Str());
    ui->eq_3->setText(" = " + accur->f3Str());

    connect(ui->reset, &QPushButton::clicked, this, &PlotsDialog::showFullPlot);
}

PlotsDialog::~PlotsDialog()
{
    delete ui;
}

void PlotsDialog::showFullPlot()
{
    ui->plot_x->graph(0)->rescaleAxes();
    ui->plot_x->graph(1)->rescaleAxes(true);
    ui->plot_x->replot();
    ui->plot_y->graph(0)->rescaleAxes();
    ui->plot_y->graph(1)->rescaleAxes(true);
    ui->plot_y->replot();
    ui->plot_z->graph(0)->rescaleAxes();
    ui->plot_z->graph(1)->rescaleAxes(true);
    ui->plot_z->replot();
}
