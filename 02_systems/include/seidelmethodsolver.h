#ifndef SEIDELMETHODSOLVER_H
#define SEIDELMETHODSOLVER_H

#include "lesystemsolver.h"

class SeidelMethodSolver : public LESystemSolver
{
public:
    SeidelMethodSolver() = default;
    ~SeidelMethodSolver() = default;

    Column solve(const Matrix& A,
                 const Column& b,
                 const Column& x = Column(),
                 double epsilon = 0) override;
    bool needApproximation() override;
};

#endif // SEIDELMETHODSOLVER_H
