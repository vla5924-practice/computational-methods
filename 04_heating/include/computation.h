#pragma once

#include <vector>

#include <QThread>

#include "computationresult.h"

class Computation : public QThread
{
    Q_OBJECT

    double phi1, phi2;  // коэффициенты для функции phi
    double b0, b1, b2;  // коэффициенты для функции b
    double T;  // время воздействия
    double L;  // длина стержня
    double tau;  // величина шага по времени tau
    double h;  // величина шага по длине стержня х
    double coeff = 1.0;  // a в уравнении (1) в методичке
    int TCount;  // число шагов по времени tau
    int LCount;  // число шагов по длине стержня х

    std::vector<std::vector<double>> grid;
    std::vector<std::vector<double>> grid_part_a;
    std::vector<double> b;
    std::vector<double> phi;

    void run() override;

    double function_phi(double x) const;
    double function_b(double x) const;
    double SimpsonMethod(int j) const;
    double SimpsonMethod_W(const std::vector<std::vector<double>>& w, int j) const;
    std::vector<double> TridiagonalMatrixAlgorithm(double A, double B, double C, double AL, double C0, const std::vector<double>& F) const;

public:
    Computation(double b0, double b1, double b2, double phi1, double phi2, double T, double L, double tau, double h, QObject* parent = nullptr);
    ~Computation() = default;

signals:
    void progressChanged(int current, int total);
    void resultReady(ComputationResult result);
};
