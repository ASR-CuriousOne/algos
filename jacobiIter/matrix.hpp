#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T> class Matrix {
private:
  std::pair<size_t, size_t> m_dim;
  std::vector<T> m_data;

public:
  Matrix(size_t n, size_t m) : m_dim({n, m}), m_data(n * m, 0) {};

  Matrix(std::pair<size_t, size_t> dim)
      : m_dim(dim), m_data(dim.first * dim.second, 0) {};

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
