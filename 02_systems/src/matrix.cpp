#include "matrix.h"

Column operator*(const double& left, const Column& right) {
  size_t size = right.size();
  Column tmp(size);
  tmp = right;
  for (size_t i = 0; i < size; i++)
    tmp[i] = tmp[i] * left;
  return tmp;
}
