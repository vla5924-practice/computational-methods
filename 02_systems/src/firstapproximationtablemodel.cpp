#include "firstapproximationtablemodel.h"

FirstApproximationTableModel::FirstApproximationTableModel(int eq_count, QObject *parent)
    : QAbstractTableModel(parent), m_eq_count(eq_count), m_column(eq_count, 0.0)
{
}

const Column &FirstApproximationTableModel::column() const
{
    return m_column;
}

int FirstApproximationTableModel::rowCount(const QModelIndex &) const
{
    return 1;
}

int FirstApproximationTableModel::columnCount(const QModelIndex &) const
{
    return m_eq_count;
}

QVariant FirstApproximationTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    int column = index.column();
    return m_column[column];
}

bool FirstApproximationTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;
    int column = index.column();
    double &cell = m_column[column];
    bool ok = false;
    double newValue = value.toDouble(&ok);
    if (ok)
    {
        cell = newValue;
        emit dataChanged(index, index);
        return true;
    }
    QMessageBox::warning(nullptr, "Error", "\"" + value.toString() + "\" is not a correct number.");
    return false;
}

Qt::ItemFlags FirstApproximationTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}

QVariant FirstApproximationTableModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return "x" + QString::fromStdString(std::to_string(column + 1));
    return QVariant();
}
