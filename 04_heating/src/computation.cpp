#include "computation.h"

#include <cmath>

constexpr double PI = 3.14;

double Computation::phiFunction(double x) const
{
    return 1.0 / m_l + m_phi1 * std::cos(PI * x / m_l) + m_phi2 * std::cos(2.0 * PI * x / m_l);
}

double Computation::bFunction(double x) const
{
    return m_b0 + m_b1 * std::cos(PI * x / m_l) + m_b2 * std::cos(2.0 * PI * x / m_l);
}

double Computation::simpsonMethod(const std::vector<std::vector<double>>& grid, const std::vector<double>& b, int j) const
{
    double value = b[0] * grid[0][j];

    for (int i = 1; i < m_count_l - 1; i++)
    {
        if (i % 2 == 0)
            value += 2.0 * b[i + 1] * grid[i + 1][j];
        else
            value += 4.0 * b[i] * grid[i][j];
    }

    value += b[m_count_l - 1] * grid[m_count_l - 1][j];
    value = value * m_step_l / 3.0;

    return value;
}

double Computation::simpsonMethodW(const std::vector<std::vector<double>>& w, int j) const
{
    double value = w[0][j];

    for (int i = 1; i < m_count_l - 1; i++)
    {
        if (i % 2 == 0)
            value += 2.0 * w[i + 1][j];
        else
            value += 4.0 * w[i][j];
    }

    value += w[m_count_l - 1][j];
    value = value * m_step_l / 3.0;

    return value;
}

Computation::Computation(double b0, double b1, double b2, double phi1, double phi2, double t, double l, double step_t,
                         double step_l, QObject *parent) : QThread(parent), m_phi1(phi1), m_phi2(phi2), m_b0(b0),
                         m_b1(b1), m_b2(b2), m_t(t), m_l(l), m_step_t(step_t), m_step_l(step_l), m_count_t(0),
                         m_count_l(0)
{
    m_count_t = static_cast<int>(m_t / m_step_t) + 1;
    m_count_l = static_cast<int>(m_l / m_step_l) + 1;
}

std::vector<double> Computation::tridiagonalMatrixAlgorithm(double A, double B, double C, double AL, double C0, const std::vector<double>& F) const
{
    std::vector<double> y(m_count_l);
    std::vector<double> alpha(m_count_l);
    std::vector<double> beta(m_count_l);

    alpha[0] = -1.0 * C0 / B;
    beta[0] = F[0] / B;

    for (int i = 1; i < m_count_l - 1; i++)
    {
        alpha[i] = -1.0 * C / (A * alpha[i - 1] + B);
        beta[i] = (F[i] - A * beta[i - 1]) / (A * alpha[i - 1] + B);
    }

    y[m_count_l - 1] = (F[m_count_l - 1] - AL * beta[m_count_l - 2]) / (AL * alpha[m_count_l - 2] + B);

    for (int i = m_count_l - 2; i >= 0; i--)
        y[i] = alpha[i] * y[i + 1] + beta[i];

    return y;
}

void Computation::run()
{
    int maximum = 2 * m_count_l + m_count_t * (2 * m_count_l);
    emit progressChanged(0, maximum);
    int current_progress = 0;

    std::vector<double> b(m_count_l);
    std::vector<double> phi(m_count_l);

    std::vector<std::vector<double>> grid(m_count_l);
    for (auto& row : grid)
        row.resize(m_count_t, 0.0);

    std::vector<std::vector<double>> grid_a(m_count_l);
    for (auto& row : grid_a)
        row.resize(m_count_t, 0.0);

    std::vector<double> y;
    std::vector<double> y_a;
    std::vector<double> F(m_count_l);
    std::vector<double> F_a(m_count_l);

    for (int i = 0; i < m_count_l; i++)
    {
        phi[i] = phiFunction(i * m_step_l);
        b[i] = bFunction(i * m_step_l);
        grid[i][0] = phi[i];
        grid_a[i][0] = phi[i];
        emit progressChanged(++current_progress, maximum);
    }

    double r = m_coeff * m_coeff * m_step_t / (m_step_l * m_step_l);
    double A = r;
    double B = -1.0 - 2.0 * r;
    double C = r;
    double AL = 2.0 * r;
    double C0 = 2.0 * r;

    for (int j = 0; j < m_count_t - 1; j++)
    {
        double integral = simpsonMethod(grid, b, j);
        for (int i = 0; i < m_count_l; i++)
        {
            F[i] = -1.0 * grid[i][j] * (1.0 + m_step_t * b[i] - m_step_t * integral);
            F_a[i] = -1.0 * grid_a[i][j] * (1.0 + m_step_t * b[i]);
            emit progressChanged(++current_progress, maximum);
        }
        y = tridiagonalMatrixAlgorithm(A, B, C, AL, C0, F);
        y_a = tridiagonalMatrixAlgorithm(A, B, C, AL, C0, F_a);
        for (int i = 0; i < m_count_l; i++)
        {
            grid[i][j + 1] = y[i];
            grid_a[i][j + 1] = y_a[i];
            emit progressChanged(++current_progress, maximum);
        }
    }

    double square = simpsonMethodW(grid_a, m_count_t - 1);
    for (int i = 0; i < m_count_l; i++)
    {
        grid_a[i][m_count_t - 1] = grid_a[i][m_count_t - 1] / square;
        emit progressChanged(++current_progress, maximum);
    }

    ComputationResult result(m_count_l);
    for (int i = 0; i < m_count_l; i++)
    {
        result.x[i] = i * m_step_l;
        result.phi[i] = phi[i];
        result.grid[i] = grid[i][m_count_t - 1];
        result.grid_a[i] = grid_a[i][m_count_t - 1];
    }

    emit progressChanged(maximum, maximum);
    emit resultReady(result);
}
