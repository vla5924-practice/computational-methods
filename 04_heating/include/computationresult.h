#pragma once

#include <QVector>

struct ComputationResult
{
    QVector<double> x;
    QVector<double> phi;
    QVector<double> grid;
    QVector<double> grid_a;

    ComputationResult(int size) : x(size), phi(size), grid(size), grid_a(size){}

    ComputationResult() = default;
    ComputationResult(const ComputationResult&) = default;
    ComputationResult(ComputationResult&&) = default;
    ~ComputationResult() = default;
};
