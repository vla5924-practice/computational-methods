#include "spline.h"

constexpr size_t SPLINE_COUNT_POINTS_MIN = 4;

void Spline::insert(const QPointF& point)
{
    auto same_x_it = std::find_if(m_points.begin(), m_points.end(),
                                  [point](const QPointF& pt){ return pt.x() == point.x(); });
    if (same_x_it != m_points.end())
        throw std::logic_error("Point with this x coordinate is already exists. Please, try again.");
    auto ins_it = std::find_if_not(m_points.begin(), m_points.end(),
                                   [point](const QPointF& pt){ return pt.x() < point.x(); });
    m_points.insert(ins_it, point);
    if (m_points.size() >= SPLINE_COUNT_POINTS_MIN)
        update();
}

void Spline::removeAll()
{
    m_points.clear();
}

const std::vector<QPointF>& Spline::points() const
{
    return m_points;
}

void Spline::update()
{
    size_t count_points = m_points.size();
    m_a = std::vector<double>(count_points, 0);
    m_b = std::vector<double>(count_points, 0);
    m_c = std::vector<double>(count_points, 0);
    m_d = std::vector<double>(count_points, 0);
    tridiagonalMatrixAlgorithm();
}

void Spline::tridiagonalMatrixAlgorithm()
{
    size_t n = m_points.size() - 1;
    std::vector<double> h(n);
    for (size_t i = 0; i < n; i++)
        h[i] = m_points[i + 1].x() - m_points[i].x();
    std::vector<double> diagMain(n - 1);
    std::vector<double> diagUpper(n - 2);
    std::vector<double> diagLower(n - 2);
    std::vector<double> vec(n - 1);
    for (size_t i = 0; i < n - 1; i++)
    {
        vec[i] = 6 * (h[i] * (m_points[i + 2].y() - m_points[i + 1].y()) - h[i + 1] * (m_points[i + 1].y() - m_points[i].y())) / (h[i + 1] * h[i] * (h[i + 1] + h[i]));
        diagMain[i] = 2;
    }
    for (size_t i = 0; i < n - 2; i++)
    {
        diagUpper[i] = h[i + 2] / (h[i + 1] + h[i + 2]);
        diagLower[i] = h[i + 1] / (h[i + 1] + h[i + 2]);
    }
    std::vector<double> p(n - 2), q(n - 1);
    p[0] = -diagUpper[0] / diagMain[0];
    for (size_t i = 1; i < n - 2; i++)
    {
        double denom_p = diagLower[i - 1] * p[i - 1] + diagMain[i];
        p[i] = -diagUpper[i] / denom_p;
    }
    q[0] = vec[0] / diagMain[0];
    for (size_t i = 1; i < n - 1; i++)
    {
        double denom_q = diagLower[i - 1] * p[i - 1] + diagMain[i];
        q[i] = (vec[i] - diagLower[i - 1] * q[i - 1]) / denom_q;
    }
    m_c[0] = m_c[n] = 0;
    m_c[n - 1] = q[n - 2];
    for (size_t i = n - 2; i > 0; i--)
        m_c[i] = p[i - 1] * m_c[i + 1] + q[i - 1];
    m_d[0] = m_c[1] / h[0];
    m_b[0] = m_c[1] * h[0] / 3 + ((m_points[1].y() - m_points[0].y()) / h[0]);
    for (size_t i = 1; i < n + 1; i++)
    {
        m_a[i] = m_points[i].y();
        m_b[i] = m_c[i] * h[i - 1] / 3 + m_c[i - 1] * h[i - 1] / 6 + ((m_points[i].y() - m_points[i - 1].y()) / h[i - 1]);
        m_d[i] = (m_c[i] - m_c[i - 1]) / h[i - 1];
    }
}

double Spline::interpolatedValue(size_t i, double x) const
{
    double a = m_a[i], b = m_b[i], c = m_c[i], d = m_d[i];
    double delta = x - m_points[i].x();
    return (a + b * delta + (c / 2.) * delta * delta + (d / 6.) * delta * delta * delta);
}

bool Spline::available() const
{
    return m_points.size() >= SPLINE_COUNT_POINTS_MIN;
}
