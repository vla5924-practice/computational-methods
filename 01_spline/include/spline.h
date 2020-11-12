#pragma once

#include <stdexcept>
#include <vector>
#include <algorithm>

#include <QPointF>

constexpr size_t SPLINE_COUNT_POINTS_MIN = 4;

class Spline
{
protected:
    std::vector<QPointF> m_points;

    std::vector<double> m_a;
    std::vector<double> m_b;
    std::vector<double> m_c;
    std::vector<double> m_d;

public:
    Spline();
    ~Spline();

    void insert(const QPointF& point);

    const std::vector<QPointF>& points() const;
    double interpolatedValue(size_t i, double x) const;

protected:
    void update();
    void tridiagonalMatrixAlgorithm();
};
