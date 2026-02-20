#pragma once
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

template <typename T> class Matrix {
private:
  std::pair<size_t, size_t> m_dim;
  std::vector<T> m_data;

public:
  Matrix(size_t n, size_t m) : m_dim({n, m}), m_data(n * m, 0) {};

  Matrix(std::pair<size_t, size_t> dim)
      : m_dim(dim), m_data(dim.first * dim.second, 0) {};

  std::pair<size_t, size_t> getDim() const { return m_dim; }

  T &operator[](size_t i, size_t j) {
    assert(0 <= i && i < m_dim.first && 0 <= j && j < m_dim.second);
    return m_data[i * m_dim.second + j];
  }

  T operator[](size_t i, size_t j) const {
    assert(0 <= i && i < m_dim.first && 0 <= j && j < m_dim.second);
    return m_data[i * m_dim.second + j];
  }

  Matrix operator+(const Matrix &other) {
    assert(m_dim == other.m_dim);

    Matrix<T> result(m_dim);
    for (size_t i = 0; i < m_data.size(); i++)
      result.m_data[i] = m_data[i] + other.m_data[i];

    return result;
  }

  friend bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    if (lhs.getDim() != rhs.getDim())
      return false;

    for (size_t i = 0; i < lhs.m_data.size(); ++i) {
      if (lhs.m_data[i] != rhs.m_data[i])
        return false;
    }
    return true;
  }

  Matrix operator*(const Matrix &other) {
    assert(m_dim.second == other.m_dim.first);

    Matrix<T> result(m_dim.first, other.m_dim.second);

    for (size_t i = 0; i < m_dim.first; i++) {
      for (size_t j = 0; j < other.m_dim.second; j++) {
        result[i, j] = 0;
        for (size_t k = 0; k < m_dim.second; k++) {
          result[i, j] += (*this)[i, k] * other[k, j];
        }
      }
    }

    return result;
  }

  Matrix get_minor(size_t row_to_remove, size_t col_to_remove) const {
    assert(m_dim.first > 1 && m_dim.second > 1);
    Matrix<T> result(m_dim.first - 1, m_dim.second - 1);
    size_t target_row = 0;
    for (size_t i = 0; i < m_dim.first; ++i) {
      if (i == row_to_remove)
        continue;
      size_t target_col = 0;
      for (size_t j = 0; j < m_dim.second; ++j) {
        if (j == col_to_remove)
          continue;
        result[target_row, target_col] = (*this)[i, j];
        target_col++;
      }
      target_row++;
    }
    return result;
  }

  double determinant() const {
    assert(m_dim.first == m_dim.second);
    size_t n = m_dim.first;
    std::vector<std::vector<double>> temp(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        temp[i][j] = static_cast<double>((*this)[i, j]);
      }
    }

    double det = 1.0;
    for (size_t i = 0; i < n; ++i) {
      size_t pivot = i;
      while (pivot < n && std::abs(temp[pivot][i]) < 1e-9)
        pivot++;

      if (pivot == n)
        return 0.0;
      if (pivot != i) {
        std::swap(temp[i], temp[pivot]);
        det *= -1.0;
      }

      det *= temp[i][i];
      for (size_t j = i + 1; j < n; ++j) {
        double factor = temp[j][i] / temp[i][i];
        for (size_t k = i + 1; k < n; ++k) {
          temp[j][k] -= factor * temp[i][k];
        }
      }
    }
    return det;
  }

  void display() const {
    for (size_t i = 0; i < m_dim.first; i++) {
      std::cout << "[ ";
      for (size_t j = 0; j < m_dim.second; j++) {
        std::cout << std::left << std::setw(5) << (*this)[i, j];
      }
      std::cout << "]" << std::endl;
    }
  }
};
