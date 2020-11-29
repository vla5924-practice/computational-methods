#ifndef LESYSTEMSOLVER_H
#define LESYSTEMSOLVER_H

#include "matrix.h"

class LESystemSolver
{
public:
    virtual Column solve(const Matrix& A, const Column& b) = 0;
};

#endif // LESYSTEMSOLVER_H
