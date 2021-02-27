#include "solutiontablemodel.h"

SolutionTableModel::SolutionTableModel(const std::vector<std::array<double, 4>>& solutions,
                                       QObject *parent)
    : QAbstractTableModel(parent), m_solutions(solutions)
{
    m_count = static_cast<int>(m_solutions.size());
}

int SolutionTableModel::rowCount(const QModelIndex &) const
{
    return m_count;
}

int SolutionTableModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant SolutionTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    int row = index.row();
    int column = index.column();
    return m_solutions[row][column];
}

QVariant SolutionTableModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Vertical)
        return column + 1;
    if (column == 0)
        return "x";
    if (column == 1)
        return "y";
    if (column == 2)
        return "z";
    if (column == 3)
        return "t";
    return "..";
}
