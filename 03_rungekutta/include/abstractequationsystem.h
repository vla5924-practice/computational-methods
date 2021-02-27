#pragma once

#include <string>

class AbstractEquationSystem
{
protected:
    std::string m_f1;
    std::string m_f2;
    std::string m_f3;

public:
    AbstractEquationSystem() = default;
    virtual ~AbstractEquationSystem() = default;

    virtual double f1(double x, double y, double z) const = 0;
    virtual double f2(double x, double y, double z) const = 0;
    virtual double f3(double x, double y, double z) const = 0;

    const std::string& f1Str() const;
    const std::string& f2Str() const;
    const std::string& f3Str() const;
};
