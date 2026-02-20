#include "matrix.hpp"
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <utility>

using mat = Matrix<float>;

template <typename T> class ColumnVector : public Matrix<T> {
public:
  ColumnVector(size_t n) : Matrix<T>(n, 1) {}

  ColumnVector(const Matrix<T> &m) : Matrix<T>(m) {
    assert(m.getDim().second == 1 &&
           "Matrix must be n x 1 to become a ColumnVector");
  }

  T &operator[](size_t i) { return Matrix<T>::operator[](i, 0); }

  T operator[](size_t i) const { return Matrix<T>::operator[](i, 0); }

  using Matrix<T>::operator*;
  T operator*(const ColumnVector<T> &other) const {
    assert(this->getDim().first == other.getDim().first &&
           "Vectors must be the same length");

    T dotProduct = 0;
    size_t length = this->getDim().first;

    for (size_t i = 0; i < length; ++i) {
      dotProduct += (*this)[i] * other[i];
    }

    return dotProduct;
  }

  double determinant() const = delete;

  Matrix<T> get_minor(size_t row_to_remove,
                      size_t col_to_remove) const = delete;
};

using vec = ColumnVector<float>;

vec calculateForLowerTriangular(const mat &A, const vec &b) {
  assert(A.getDim().first == A.getDim().second &&
         A.getDim().second == b.getDim().first &&
         "Matrix vector size mismatch");

  const size_t n = b.getDim().first;

  vec soln(n);

  for (size_t i = 0; i < n; i++) {
    float xi = 0;
    for (size_t j = 0; j < n; j++) {
      if (j > i) {
        if (A[i, j] != 0)
          throw std::runtime_error("Not a lower triangular matrix");
      } else if (i == j) {
        xi += b[i];
      } else {
        xi -= A[i, j] * soln[j];
      }
    }
		if(A[i,i] == 0){
			throw std::runtime_error("Not invertible");
		}
		soln[i] = xi / A[i,i];
  }
	
	return soln;
}

// L U

int main() {
	mat A(2,2);

	A[0,0] = 2;
	A[1,0] = 1;
	A[1,1] = 2;

	vec b(2);

	b[0] = 3;
	b[1] = 4;

	vec ans = calculateForLowerTriangular(A,b);

	ans.display();
}
