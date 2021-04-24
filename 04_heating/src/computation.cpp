#include "computation.h"

#include <cmath>

constexpr double PI = 3.14;

// Функция phi(x) - начальное распределение температуры
double Computation::function_phi(double x) const
{
    return 1.0 / L + phi1 * std::cos(PI * x / L) + phi2 * std::cos(2.0 * PI * x / L);
}

// Функция b(x) - управляющая функция
double Computation::function_b(double x) const
{
    return b0 + b1 * std::cos(PI * x / L) + b2 * std::cos(2.0 * PI * x / L);
}

// Метод Симпсона для вычисления интеграла в части Б
double Computation::SimpsonMethod(int j) const
{
    double value = b[0] * grid[0][j];

    for (int i = 1; i < LCount - 1; i++)
    {
        if (i % 2 == 0)
            value += 2.0 * b[i + 1] * grid[i + 1][j];
        else
            value += 4.0 * b[i] * grid[i][j];
    }

    value += b[LCount - 1] * grid[LCount - 1][j];
    value = value * h / 3.0;

    return value;
}

double Computation::SimpsonMethod_W(const std::vector<std::vector<double>>& w, int j) const
{
    double value = w[0][j];

    for (int i = 1; i < LCount - 1; i++)
    {
        if (i % 2 == 0)
            value += 2.0 * w[i + 1][j];
        else
            value += 4.0 * w[i][j];
    }

    value += w[LCount - 1][j];
    value = value * h / 3.0;

    return value;
}

Computation::Computation(double b0, double b1, double b2, double phi1, double phi2, double T, double L, double tau,
                         double h, QObject *parent) : QThread(parent), b0(b0), b1(b1), b2(b2), phi1(phi1), phi2(phi2),
                         T(T), L(L), tau(tau), h(h), TCount(0), LCount(0)
{

}

// Метод прогонки для 3-х диагональной матрицы
std::vector<double> Computation::TridiagonalMatrixAlgorithm(double A, double B, double C, double AL, double C0, const std::vector<double>& F) const
{
    std::vector<double> y(LCount);
    std::vector<double> alpha(LCount);
    std::vector<double> beta(LCount);

    alpha[0] = -1.0 * C0 / B;
    beta[0] = F[0] / B;

    for (int i = 1; i < LCount - 1; i++)
    {
        alpha[i] = -1.0 * C / (A * alpha[i - 1] + B);
        beta[i] = (F[i] - A * beta[i - 1]) / (A * alpha[i - 1] + B);
    }

    y[LCount - 1] = (F[LCount - 1] - AL * beta[LCount - 2]) / (AL * alpha[LCount - 2] + B);

    for (int i = LCount - 2; i >= 0; i--)
        y[i] = alpha[i] * y[i + 1] + beta[i];

    return y;
}

void Computation::run()
{
    TCount = static_cast<int>(T / tau) + 1;
    LCount = static_cast<int>(L / h) + 1;

    int maximum = 2 * LCount + TCount * (2 * LCount);
    emit progressChanged(0, maximum);
    int current_progress = 0;

    grid.resize(LCount);
    for (auto& row : grid)
        row.resize(TCount, 0.0);
    grid_part_a.resize(LCount);
    for (auto& row : grid_part_a)
        row.resize(TCount, 0.0);
    b.resize(LCount);
    phi.resize(LCount);

    // Инициализация необходимых переменных
    std::vector<double> y;
    std::vector<double> y_part_a;
    std::vector<double> F(LCount);
    std::vector<double> F_part_a(LCount);

    // Первоначальная инициализация функций по интервалам сетки
    for (int i = 0; i < LCount; i++)
    {
        phi[i] = function_phi(i * h);
        b[i] = function_b(i * h);
        grid[i][0] = phi[i];
        grid_part_a[i][0] = phi[i];
        emit progressChanged(++current_progress, maximum);
    }

    // Инициализация коэффициентов для метода прогонки
    double r = coeff * coeff * tau / (h * h);  // Выполняем замену для удобства
    double A = r;
    double B = -1.0 - 2.0 * r;
    double C = r;
    double AL = 2.0 * r;
    double C0 = 2.0 * r;

    // Решение задачи
    for (int j = 0; j < TCount - 1; j++)
    {
        double integral = SimpsonMethod(j);
        for (int i = 0; i < LCount; i++)
        {
            F[i] = -1.0 * grid[i][j] * (1.0 + tau * b[i] - tau * integral);
            F_part_a[i] = -1.0 * grid_part_a[i][j] * (1.0 + tau * b[i]);
            emit progressChanged(++current_progress, maximum);
        }
        y = TridiagonalMatrixAlgorithm(A, B, C, AL, C0, F);
        y_part_a = TridiagonalMatrixAlgorithm(A, B, C, AL, C0, F_part_a);
        for (int i = 0; i < LCount; i++)
        {
            grid[i][j + 1] = y[i];
            grid_part_a[i][j + 1] = y_part_a[i];
            emit progressChanged(++current_progress, maximum);
        }
    }

    // Нахождения решения при помощи части А
    double square = SimpsonMethod_W(grid_part_a, TCount - 1);
    for (int i = 0; i < LCount; i++)
    {
        grid_part_a[i][TCount - 1] = grid_part_a[i][TCount - 1] / square;
        emit progressChanged(++current_progress, maximum);
    }

    ComputationResult result(LCount);
    for (int i = 0; i < LCount; i++)
    {
        result.x[i] = i * h;
        result.phi[i] = phi[i];
        result.grid[i] = grid[i][TCount - 1];
        result.grid_part_a[i] = grid_part_a[i][TCount - 1];
    }

    emit progressChanged(maximum, maximum);
    emit resultReady(result);
}
