#pragma once

#include <array>
#include <vector>

#include <QAbstractTableModel>

class SolutionTableModel : public QAbstractTableModel
{
    Q_OBJECT

    int m_count;
    std::vector<std::array<double, 4>> m_solutions;

public:
    explicit SolutionTableModel(const std::vector<std::array<double, 4>>& solutions, QObject *parent = nullptr);
    ~SolutionTableModel() = default;

protected:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
