#pragma once

#include <QString>

class AbstractEquationSystem
{
protected:
    QString m_f1;
    QString m_f2;
    QString m_f3;

public:
    AbstractEquationSystem() = default;
    virtual ~AbstractEquationSystem() = default;

    virtual double f1(double x, double y, double z) const = 0;
    virtual double f2(double x, double y, double z) const = 0;
    virtual double f3(double x, double y, double z) const = 0;

    const QString& f1Str() const;
    const QString& f2Str() const;
    const QString& f3Str() const;
};
