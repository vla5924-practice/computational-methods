#pragma once

#include <stdexcept>
#include <vector>
#include <algorithm>

#include <QPointF>

class Spline
{
protected:
    std::vector<QPointF> m_points;

    std::vector<double> m_a;
    std::vector<double> m_b;
    std::vector<double> m_c;
    std::vector<double> m_d;

public:
    Spline() = default;
    ~Spline() = default;

    void insert(const QPointF& point);
    void removeAll();

    const std::vector<QPointF>& points() const;
    double interpolatedValue(size_t i, double x) const;
    bool available() const;

protected:
    void update();
    void tridiagonalMatrixAlgorithm();
};
