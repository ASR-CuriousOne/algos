#pragma once
#include "matrix.hpp"
#include <expected>
#include <filesystem>
#include <fstream>

std::expected<Mat, std::string>
readMatrixFromFile(const std::filesystem::path &filename) {

  std::ifstream file(filename);
  if (!file.is_open()) {
    return std::unexpected("Could not open matrix file: " + filename.string());
  }

  size_t rows, cols;
  if (!(file >> rows >> cols)) {
    return std::unexpected("Failed to read matrix dimensions from " +
                           filename.string());
  }

  Mat M(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      file >> M[i, j];
    }
  }
  return M;
}

std::expected<Vec, std::string>
readVectorFromFile(const std::filesystem::path &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return std::unexpected("Could not open vector file: " +
                             filename.string());
  }

  size_t size;
  if (!(file >> size)) {
    return std::unexpected("Failed to read vector size from " +
                             filename.string());
  }

  Vec v(size);
  for (size_t i = 0; i < size; ++i) {
    file >> v[i];
  }
  return v;
}
