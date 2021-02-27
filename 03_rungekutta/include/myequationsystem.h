#pragma once

#include "abstractequationsystem.h"

class MyEquationSystem : public AbstractEquationSystem
{
public:
    MyEquationSystem();
    ~MyEquationSystem() = default;

    double f1(double x, double y, double z) const override;
    double f2(double x, double y, double z) const override;
    double f3(double x, double y, double z) const override;
};
