#ifndef FIRSTAPPROXIMATIONTABLEMODEL_H
#define FIRSTAPPROXIMATIONTABLEMODEL_H

#include <QAbstractTableModel>
#include <QMessageBox>

#include "matrix.h"

class FirstApproximationTableModel : public QAbstractTableModel
{
    Q_OBJECT

    int m_eq_count;
    Column m_column;

public:
    explicit FirstApproximationTableModel(int eq_count = 1, QObject *parent = nullptr);
    ~FirstApproximationTableModel() = default;

    const Column &column() const;

protected:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // FIRSTAPPROXIMATIONTABLEMODEL_H
