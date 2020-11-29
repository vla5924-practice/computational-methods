#include "systemtablemodel.h"


SystemTableModel::SystemTableModel(int eq_count, QObject *parent)
    : QAbstractTableModel(parent), m_eq_count(eq_count), m_column(eq_count, 0.0)
{
    m_matrix.resize(m_eq_count);
    for (auto& row : m_matrix)
    {
        row = std::vector<double>(m_eq_count, 0.0);
    }
}

int SystemTableModel::rowCount(const QModelIndex &) const
{
    return m_eq_count;
}

int SystemTableModel::columnCount(const QModelIndex &) const
{
    return m_eq_count + 1;
}

QVariant SystemTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    int row = index.row();
    int column = index.column();
    if (column >= m_eq_count)
        return QVariant(m_column[row]);
    return QVariant(m_matrix[row][column]);
}

bool SystemTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;
    int row = index.row();
    int column = index.column();
    double &cell = column >= m_eq_count ? m_column[row] : m_matrix[row][column];
    cell = value.toDouble();
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags SystemTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}

QVariant SystemTableModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Vertical)
    {
        return column;
    }

    return "x" + QString(column);
}
