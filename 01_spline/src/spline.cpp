#include "spline.h"

Spline::Spline()
{

}

Spline::~Spline()
{

}

void Spline::insert(const QPointF& point)
{
    auto iterator = m_points.begin();
    while (iterator != m_points.end() && iterator->x() < point.x())
    {
        iterator++;
    }
    m_points.insert(iterator, point);
    // hmm...
    if (m_points.size() > 2)
        update();
}

const std::vector<QPointF>& Spline::points() const
{
    return m_points;
}

const std::vector<double> Spline::a()
{
    return m_a;
}

const std::vector<double> Spline::b()
{
    return m_b;
}

const std::vector<double> Spline::c()
{
    return m_c;
}

const std::vector<double> Spline::d()
{
    return m_d;
}

void Spline::update()
{
    m_a = std::vector<double>(m_points.size());
    m_b = std::vector<double>(m_points.size());
    m_c = std::vector<double>(m_points.size());
    m_d = std::vector<double>(m_points.size());
    std::vector<double> h(m_points.size());

    for (size_t i = 1; i < h.size(); i++)
    {
        h[i] = m_points[i].x() - m_points[i - 1].x();
    }

    m_c[0] = m_c[m_c.size() - 1] = 0;
    tridiagonalMatrixAlgorithm(h);

    for (size_t i = 1; i < m_points.size(); i++)
    {
        m_a[i] = m_points[i].y();
        m_d[i] = (m_c[i] - m_c[i - 1]) / (3 * h[i]);
        m_b[i] = (m_a[i] - m_a[i - 1]) / h[i] + ((2 * m_c[i] + m_c[i - 1]) / 3) * h[i];
    }
}

void Spline::tridiagonalMatrixAlgorithm(const std::vector<double>& h)
{
    size_t count_points = m_points.size();
    std::vector<std::array<double, 3>> matrix(count_points);

    matrix[1] = { 0, 2 * h[2] + 2 * h[1], h[2] };
    for (size_t i = 2; i < count_points - 2; i++)
        matrix[i] = { h[i], 2 * h[i + 1] + 2 * h[i], h[i + 1] };
    matrix[count_points - 2] = { h[count_points - 2], 2 * h[count_points - 1] + 2 * h[count_points - 2], 0 };

    std::vector<double> vector(count_points - 1);
    for (size_t i = 1; i < count_points - 1; i++)
    {
        double k1 = (m_points[i + 1].y() - m_points[i].y()) / h[i + 1];
        double k2 = (m_points[i].y() - m_points[i - 1].y()) / h[i];
        vector[i] = 3 * (k1 - k2);
    }

    size_t n = count_points - 2;
    std::vector<double> a(count_points - 1);
    std::vector<double> b(count_points - 1);
    std::vector<double> pre_result(count_points - 1);

    double y = matrix[1][1];
    a[1] = -matrix[1][2] / y;
    b[1] = vector[1] / y;
    for (size_t i = 2; i < n; i++)
    {
        y = matrix[i][1] + matrix[i][0] * a[i - 1];
        a[i] = -matrix[i][2] / y;
        b[i] = (vector[i] - matrix[i][0] * b[i - 1]) / y;
    }

    pre_result[n] = (vector[n] - matrix[n][0] * b[n - 1]) / (matrix[n][1] + matrix[n][0] * a[n - 1]);
    for (size_t i = n - 1; i >= 1; i--)
        pre_result[i] = a[i] * pre_result[i + 1] + b[i];

    for (size_t i = 1; i < count_points - 1; i++)
        m_c[i] = pre_result[i];
}
