#pragma once

#include <array>
#include <vector>

#include "abstractequationsystem.h"

class RKMethodSolver
{
    AbstractEquationSystem* m_system;

public:
    RKMethodSolver(AbstractEquationSystem* system);
    ~RKMethodSolver() = default;

    std::vector<std::array<double, 4>> solve(double a, double b, int n,
                                             const std::array<double, 3>& init_conditions);
};
