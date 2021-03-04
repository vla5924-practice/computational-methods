#pragma once

#include <array>

#include <QString>

class AbstractAccurateSolution
{
protected:
    QString m_f1;
    QString m_f2;
    QString m_f3;

public:
    AbstractAccurateSolution() = default;
    ~AbstractAccurateSolution() = default;

    virtual double f1(double t) const = 0;
    virtual double f2(double t) const = 0;
    virtual double f3(double t) const = 0;

    const QString& f1Str() const;
    const QString& f2Str() const;
    const QString& f3Str() const;
};
