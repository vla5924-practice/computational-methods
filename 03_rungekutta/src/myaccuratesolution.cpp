#include "myaccuratesolution.h"

#include <cmath>

MyAccurateSolution::MyAccurateSolution(const std::array<double, 3> &init_conditions, double t)
{
    c1 = std::exp(-t) * (init_conditions[0] + init_conditions[1]) / 2;
    c2 = std::exp(t) * (init_conditions[0] - init_conditions[1]) / 2;
    c3 = std::exp(-t) * init_conditions[2] - 2 * c1 * t;

    m_f1 = QString::number(c1, 'g', 2) + "e<sup>t</sup> + (" + QString::number(c2, 'g', 2) + ") * e<sup>-t</sup>";
    m_f2 = QString::number(c1, 'g', 2) + "e<sup>t</sup> - (" + QString::number(c2, 'g', 2) + ") * e<sup>-t</sup>";
    m_f3 = QString::number(c3, 'g', 2) + "e<sup>t</sup> + 2 * (" + QString::number(c1, 'g', 2) + ") * te<sup>t</sup>";
}

double MyAccurateSolution::f1(double t) const
{
    return c1 * std::exp(t) + c2 * std::exp(-t);
}

double MyAccurateSolution::f2(double t) const
{
    return c1 * std::exp(t) - c2 * std::exp(-t);
}

double MyAccurateSolution::f3(double t) const
{
    return std::exp(t) * (c3 + 2 * c1 * t);
}
