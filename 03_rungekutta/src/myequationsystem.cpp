#include "myequationsystem.h"

MyEquationSystem::MyEquationSystem()
{
    m_f1 = "y";
    m_f2 = "x";
    m_f3 = "x + y + z";
}

double MyEquationSystem::f1(double, double y, double) const
{
    return y;
}

double MyEquationSystem::f2(double x, double, double) const
{
    return x;
}

double MyEquationSystem::f3(double x, double y, double z) const
{
    return x + y + z;
}
