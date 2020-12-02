#ifndef METHOD_H
#define METHOD_H

enum Method
{
    GaussMethod = 0,
    KramerMethod = 1,
    SeidelMethod = 2,
    SimpleIterationMethod = 3,
    UpperRelaxationMethod = 4,
    LUDecompositionMethod = 5
};

constexpr int METHODS_COUNT = 6;

#endif // METHOD_H
