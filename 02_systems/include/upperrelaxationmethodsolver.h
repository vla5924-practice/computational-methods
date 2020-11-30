#ifndef UPPERRELAXATIONMETHODSOLVER_H
#define UPPERRELAXATIONMETHODSOLVER_H

#include <random>

#include "lesystemsolver.h"

class UpperRelaxationMethodSolver : public LESystemSolver
{
public:
    UpperRelaxationMethodSolver() = default;
    ~UpperRelaxationMethodSolver() = default;

    Column solve(const Matrix& A,
                 const Column& b,
                 const Column& x = Column(),
                 double epsilon = 0) override;
    bool needApproximation() override;
};

#endif // UPPERRELAXATIONMETHODSOLVER_H
