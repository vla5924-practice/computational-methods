#pragma once

#include <vector>

#include <QThread>

#include "computationresult.h"

class Computation : public QThread
{
    Q_OBJECT

    double m_phi1, m_phi2;
    double m_b0, m_b1, m_b2;
    double m_t;
    double m_l;
    double m_step_t;
    double m_step_l;
    double m_coeff = 1.0;
    int m_count_t;
    int m_count_l;

    void run() override;

    double phiFunction(double x) const;
    double bFunction(double x) const;
    double simpsonMethod(const std::vector<std::vector<double>>& grid, const std::vector<double>& b, int j) const;
    double simpsonMethodW(const std::vector<std::vector<double>>& w, int j) const;
    std::vector<double> tridiagonalMatrixAlgorithm(double A, double B, double C, double AL, double C0, const std::vector<double>& F) const;

public:
    Computation(double b0, double b1, double b2, double phi1, double phi2, double t, double l, double step_t, double step_l, QObject* parent = nullptr);
    ~Computation() = default;

signals:
    void progressChanged(int current, int total);
    void resultReady(ComputationResult result);
};
