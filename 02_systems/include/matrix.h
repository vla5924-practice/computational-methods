#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using Row = std::vector<double>;
using Column = std::vector<double>;
using Matrix = std::vector<Row>;

Column operator*(const double& left, const Column& right);

#endif // MATRIX_H
