#include "rkmethodsolver.h"

#include <stdexcept>

RKMethodSolver::RKMethodSolver(AbstractEquationSystem *system)
{
    m_system = system;
}

std::vector<std::array<double, 4>> RKMethodSolver::solve(double a, double b, int n,
                                                         const std::array<double, 3> &init_conditions)
{
    if (n <= 0)
        throw std::runtime_error("Number of steps must be greater than zero.");

    if (b <= a)
        throw std::runtime_error("Ending point must be greater than starting point.");

    double h = (b - a) / n;
    double t = a + h;

    std::vector<std::array<double, 4>> result;
    std::array<std::array<double, 4>, 3> K;
    double x_prev = init_conditions[0];
    double y_prev = init_conditions[1];
    double z_prev = init_conditions[2];
    double x, y, z;

    for (int i = 1; i <= n; i++)
    {
        K[0][0] = h * m_system->f1(x_prev, y_prev, z_prev);
        K[1][0] = h * m_system->f2(x_prev, y_prev, z_prev);
        K[2][0] = h * m_system->f3(x_prev, y_prev, z_prev);

        K[0][1] = h * m_system->f1(x_prev + K[0][0] / 2, y_prev + K[1][0], z_prev + K[2][0] / 2);
        K[1][1] = h * m_system->f2(x_prev + K[0][0] / 2, y_prev + K[1][0], z_prev + K[2][0] / 2);
        K[2][1] = h * m_system->f3(x_prev + K[0][0], y_prev + K[1][0], z_prev + K[2][0] / 2);

        K[0][2] = h * m_system->f1(x_prev + K[0][1] / 2, y_prev + K[1][1] / 2, z_prev + K[2][1] / 2);
        K[1][2] = h * m_system->f2(x_prev + K[0][1] / 2, y_prev + K[1][1] / 2, z_prev + K[2][1] / 2);
        K[2][2] = h * m_system->f3(x_prev + K[0][1], y_prev + K[1][1] / 2, z_prev + K[2][1] / 2);

        K[0][3] = h * m_system->f1(x_prev + K[0][2], y_prev + K[1][2], z_prev + K[2][2]);
        K[1][3] = h * m_system->f2(x_prev + K[0][2], y_prev + K[1][2], z_prev + K[2][2]);
        K[2][3] = h * m_system->f3(x_prev + K[0][2], y_prev + K[1][2], z_prev + K[2][2]);

        x = x_prev + (K[0][0] + 2 * K[0][1] + 2 * K[0][2] + K[0][3]) / 6;
        y = y_prev + (K[1][0] + 2 * K[1][1] + 2 * K[1][2] + K[1][3]) / 6;
        z = z_prev + (K[2][0] + 2 * K[2][1] + 2 * K[2][2] + K[2][3]) / 6;

        result.push_back({ x, y, z, t });
        t += h;

        x_prev = x;
        y_prev = y;
        z_prev = z;
    }
    return result;
}
