#ifndef KRAMERMETHODSOLVER_H
#define KRAMERMETHODSOLVER_H

#include "lesystemsolver.h"

class KramerMethodSolver : public LESystemSolver
{
public:
    KramerMethodSolver() = default;
    ~KramerMethodSolver() = default;

    Column solve(const Matrix& A,
                 const Column& b,
                 const Column& = Column(),
                 double = 0) override;
    bool needApproximation() override;
};

#endif // KRAMERMETHODSOLVER_H
