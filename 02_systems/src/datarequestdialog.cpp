#include "datarequestdialog.h"
#include "ui_datarequestdialog.h"

DataRequestDialog::DataRequestDialog(int eq_count, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataRequestDialog)
{
    ui->setupUi(this);

    m_model = new FirstApproximationTableModel(eq_count);

    ui->table_approx->setModel(m_model);
    ui->table_approx->horizontalHeader()->setStretchLastSection(false);
    ui->table_approx->verticalHeader()->setVisible(true);
    ui->table_approx->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->table_approx->setSelectionMode(QAbstractItemView::SingleSelection);
}

DataRequestDialog::~DataRequestDialog()
{
    delete ui;
    delete m_model;
}

const Column &DataRequestDialog::resultColumn() const
{
    return m_model->column();
}
