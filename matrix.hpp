#ifndef ADATALG_KHF01_MATRIX_HPP
#define ADATALG_KHF01_MATRIX_HPP

#include <filesystem>

class matrix {
  size_t sor,oszlop;
    int *array;
public:
  // Rule of 5
  ~matrix() noexcept;
  matrix(const matrix &m);
  matrix &operator=(const matrix &m);
  matrix(matrix &&) noexcept;
  matrix &operator=(matrix &&) noexcept;
  matrix(int *, size_t, size_t);

  explicit matrix(const std::filesystem::path &p);
  [[nodiscard]] matrix operator+(const matrix &m) const noexcept;
  [[nodiscard]] matrix operator*(const matrix &m) const noexcept;
  [[nodiscard]] int &at(size_t r, size_t c);
  [[nodiscard]] const int &at(size_t r, size_t c) const;
  [[nodiscard]] std::pair<size_t, size_t> size() const noexcept;
  void transpose() noexcept;

  void print() const noexcept;
};

#endif // ADATALG_KHF01_MATRIX_HPP
