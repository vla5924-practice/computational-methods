#ifndef SOLUTION_H
#define SOLUTION_H

#include "matrix.h"
#include "method.h"

struct Solution
{
    int method;
    Column column;
    double duration = 0;
};

#endif // SOLUTION_H
