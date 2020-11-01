#pragma once

#include <stdexcept>
#include <vector>
#include <array>

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
    Spline();
    ~Spline();

    void insert(const QPointF& point);

    const std::vector<QPointF>& points() const;
    const std::vector<double> a();
    const std::vector<double> b();
    const std::vector<double> c();
    const std::vector<double> d();

protected:
    void update();

private:
    void tridiagonalMatrixAlgorithm(const std::vector<double>& h);
};
