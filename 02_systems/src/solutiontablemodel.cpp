#include "solutiontablemodel.h"

SolutionTableModel::SolutionTableModel(const std::vector<Solution>& solutions,
                                       QObject *parent)
    : QAbstractTableModel(parent), m_solutions(solutions)
{
    m_eq_count = static_cast<int>(m_solutions[0].column.size());
    for (auto& solution : m_solutions)
        if (solution.column.size() != m_solutions[0].column.size())
            solution.column.resize(m_eq_count, 0);
}

int SolutionTableModel::rowCount(const QModelIndex &) const
{
    return m_eq_count + 1;
}

int SolutionTableModel::columnCount(const QModelIndex &) const
{
    return static_cast<int>(m_solutions.size());
}

QVariant SolutionTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    int row = index.row();
    int column = index.column();
    return row >= m_eq_count ? m_solutions[column].duration : m_solutions[column].column[row];
}

QVariant SolutionTableModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Vertical)
        return column >= m_eq_count ? QString("Duration") : "X" + QString::fromStdString(std::to_string(column + 1));
    int method = m_solutions[column].method;
    if (method == GaussMethod)
        return "Gauss method";
    if (method == KramerMethod)
        return "Kramer method";
    if (method == SeidelMethod)
        return "Seidel method";
    if (method == SimpleIterationMethod)
        return "Simple iteration method";
    if (method == UpperRelaxationMethod)
        return "Upper relaxation method";
    if (method == JacobiMethod)
        return "Jacobi method";
    return "Unknown method";
}
