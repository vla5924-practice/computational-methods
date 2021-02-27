#include "myequationsystem.h"

MyEquationSystem::MyEquationSystem()
{
    m_f1 = "";
    m_f2 = "";
    m_f3 = "";
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
