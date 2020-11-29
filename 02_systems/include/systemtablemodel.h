#ifndef SYSTEMTABLEMODEL_H
#define SYSTEMTABLEMODEL_H

#include <vector>

#include <QAbstractTableModel>
#include <QMessageBox>

using Matrix = std::vector<std::vector<double>>;
using Column = std::vector<double>;

class SystemTableModel : public QAbstractTableModel
{
    Q_OBJECT

    int m_eq_count;
    Matrix m_matrix;
    Column m_column;

public:
    explicit SystemTableModel(int eq_count = 1, QObject *parent = nullptr);
    ~SystemTableModel() = default;

protected:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // SYSTEMTABLEMODEL_H
