#pragma once

#include "abstractaccuratesolution.h"

class MyAccurateSolution : public AbstractAccurateSolution
{
    double c1;
    double c2;
    double c3;

public:
    MyAccurateSolution(double t_start, const std::array<double, 3>& init_conditions);
    ~MyAccurateSolution() = default;

    double f1(double t) const;
    double f2(double t) const;
    double f3(double t) const;
};
