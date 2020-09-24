
#include "matrix.hpp"
#include <iostream>
#include <fstream>

matrix::matrix(const std::filesystem::path &p)
{
    std::ifstream f(p);
    f >> sor;
    f >> oszlop;
    size_t sum = sor * oszlop;
    array = new int[sum];


    for (size_t i = 0; i<sor; i++)
    {
        for (size_t j = 0; j<oszlop; j++)
        {
            f >> array[j*sor+i];
        }
    }
}

matrix matrix::operator+(const matrix &m) const noexcept {

    int *res = new int[sor*oszlop];

    for (size_t i =0; i<sor*oszlop; i++)
    {
        res[i] = array[i] + m.array[i];
    }
    matrix resolution(res, sor, oszlop);
    return resolution;
}

matrix matrix::operator*(const matrix &m) const noexcept {
    int *res = new int[sor*m.oszlop];

    for (size_t i = 0; i < sor; i++) {
        for (size_t j = 0; j < m.oszlop; j++) {
            int sum = 0;
            for (size_t k = 0; k < oszlop; k++)
                sum = sum + at(i,k) * m.at(k,j);
            res[j*sor+i] = sum;
        }
    }
    matrix resolution(res, sor, m.oszlop);
    return resolution;
}

int & matrix::at(size_t r, size_t c) {

    if (r >= sor || c >= oszlop) {
        throw std::out_of_range("Rossz indexpar.");
    }
    return array[c*sor+r];
}
const int & matrix::at(size_t r, size_t c) const {

    if (r >= sor || c >= oszlop) {
        throw std::out_of_range("Rossz indexpar.");
    }
    return array[c*sor+r];
}

std::pair<size_t, size_t> matrix::size() const noexcept
{
    return std::make_pair(sor,oszlop);
}

void matrix::transpose() noexcept
{
    int *new_array = new int[sor*oszlop];
    int k = 0;
    for(size_t i = 0; i < sor; i++){
        for (size_t j = 0; j < oszlop; j++){
            new_array[k] = at(i,j);
            k++;
        }
    }
    delete[] array;
    array = new_array;
    size_t tmp = sor;
    sor = oszlop;
    oszlop = tmp;
}

void matrix::print() const noexcept {

    std::cout << std::endl;

    for (size_t i=0; i<sor; i++)
    {
        for (size_t j=0; j<oszlop; j++)
        {
            std::cout << at(i,j) <<" ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

matrix::~matrix() noexcept {
    delete[] array;
}
matrix::matrix(int *a, size_t s, size_t o) {
    array =  a;
    sor = s;
    oszlop = o;
}
matrix::matrix(const matrix &m) {
    sor = m.sor;
    oszlop = m.oszlop;
    array = new int[sor*oszlop];
    std::copy_n(m.array,sor*oszlop,array);
}
matrix & matrix::operator=(const matrix &m)
{
    if(&m == this)
        return *this;
    if(sor != m.sor || oszlop != m.oszlop)
    {
        delete[] array;
        sor = m.sor;
        oszlop = m.oszlop;
        array = new int[sor*oszlop];
    }
    std::copy_n(m.array,sor*oszlop,array);
    return *this;
}
matrix::matrix(matrix&&m) noexcept {
//    delete[] array;
//    array = nullptr;
//    sor = 0;
//    oszlop = 0;
    array = m.array;
    sor = m.sor;
    oszlop = m.oszlop;

    m.array = nullptr;
    m.sor = 0;
    m.oszlop = 0;
}
matrix & matrix::operator=(matrix &&m) noexcept {
    if (this != &m)
    {
        delete[] array;

        array = m.array;
        sor = m.sor;
        oszlop = m.oszlop;

        m.array = nullptr;
        m.sor = 0;
        m.oszlop = 0;
    }
    return *this;
}




