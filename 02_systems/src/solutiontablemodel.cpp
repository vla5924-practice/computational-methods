#include "solutiontablemodel.h"

SolutionTableModel::SolutionTableModel(const std::vector<Column>& solutions,
                                       const std::vector<double>& durations, QObject *parent)
    : QAbstractTableModel(parent), m_solutions(solutions), m_durations(durations)
{
    m_eq_count = static_cast<int>(m_solutions[0].size());
}

int SolutionTableModel::rowCount(const QModelIndex &) const
{
    return m_eq_count + 1;
}

int SolutionTableModel::columnCount(const QModelIndex &) const
{
    return static_cast<int>(m_durations.size());
}

QVariant SolutionTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    int row = index.row();
    int column = index.column();
    return row >= m_eq_count ? m_durations[column] : m_solutions[column][row];
}

QVariant SolutionTableModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Vertical)
        return column >= m_eq_count ? QString("Duration") : "x" + QString::fromStdString(std::to_string(column + 1));
    if (column == 0)
        return "Gauss";
    return "method name";
}
