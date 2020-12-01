#include "matrix.h"

Column operator*(const double& left, const Column& right) {
  size_t size = right.size();
  Column tmp(size);
  tmp = right;
  for (size_t i = 0; i < size; i++)
    tmp[i] = tmp[i] * left;
  return tmp;
}

Column operator+(const Column &left, const Column &right)
{
    if (left.size() != right.size())
        throw std::runtime_error("Column sum cannot be calculated.");
    size_t size = left.size();
    Column result(size);
    for (size_t i = 0; i < size; i++)
        result[i] = left[i] + right[i];
    return result;
}

Column operator-(const Column &left, const Column &right)
{
    if (left.size() != right.size())
        throw std::runtime_error("Column subtraction cannot be calculated.");
    size_t size = left.size();
    Column result(size);
    for (size_t i = 0; i < size; i++)
        result[i] = left[i] - right[i];
    return result;
}
