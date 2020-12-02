#ifndef LUDECOMPOSITIONMETHODSOLVER_H
#define LUDECOMPOSITIONMETHODSOLVER_H

#include "lesystemsolver.h"

class LUDecompositionMethodSolver : public LESystemSolver
{
    public:
        LUDecompositionMethodSolver() = default;
        ~LUDecompositionMethodSolver() = default;

        Column solve(const Matrix& A,
                     const Column& b,
                     const Column& = Column(),
                     double = 0) override;
        bool needApproximation() override;
};

#endif // LUDECOMPOSITIONMETHOD_H
