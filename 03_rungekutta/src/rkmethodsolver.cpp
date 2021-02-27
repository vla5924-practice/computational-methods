#include "rkmethodsolver.h"

constexpr double NO_PARAM = 0; // TODO: Impl f1 and f2 use as f3 in RKMethodSolver::solve

RKMethodSolver::RKMethodSolver(AbstractEquationSystem *system)
{
    m_system = system;
}

std::vector<std::array<double, 4>> RKMethodSolver::solve(double a, double b, int n,
                                                         const std::array<double, 3> &init_conditions)
{
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
        K[0][0] = m_system->f1(NO_PARAM, y_prev, NO_PARAM);
        K[0][1] = m_system->f1(NO_PARAM, y_prev + h / 2, NO_PARAM);
        K[0][2] = m_system->f1(NO_PARAM, y_prev + h * K[0][1] / 2, NO_PARAM);
        K[0][3] = m_system->f1(NO_PARAM, y_prev + h * K[0][2], NO_PARAM);
        x = x_prev + (K[0][0] + 2 * K[0][1] + 2 * K[0][2] + K[0][3]) * h / 6;

        K[1][0] = m_system->f2(x_prev, NO_PARAM, NO_PARAM);
        K[1][1] = m_system->f2(x_prev + h / 2, NO_PARAM, NO_PARAM);
        K[1][2] = m_system->f2(x_prev + h * K[1][1] / 2, NO_PARAM, NO_PARAM);
        K[1][3] = m_system->f2(x_prev + h * K[1][2], NO_PARAM, NO_PARAM);
        y = y_prev + (K[1][0] + 2 * K[1][1] + 2 * K[1][2] + K[1][3]) * h / 6;

        K[2][0] = m_system->f3(x_prev, y_prev, z_prev);
        K[2][1] = m_system->f3(x_prev + h / 2, y_prev + h * K[1][0] / 2, z_prev + h * K[2][0] / 2);
        K[2][2] = m_system->f3(x_prev + h * K[0][1] / 2, y_prev + h * K[1][1] / 2, z_prev + h * K[2][1] / 2);
        K[2][3] = m_system->f3(x_prev + h * K[0][2], y_prev + h * K[1][2] / 2, z_prev + h * K[2][2] / 2);
        z = z_prev + (K[2][0] + 2 * K[2][1] + 2 * K[2][2] + K[2][3]) * h / 6;

        result.push_back({ x, y, z, t });
        t += h;

        x_prev = x;
        y_prev = y;
        z_prev = z;
    }
    return result;
}
