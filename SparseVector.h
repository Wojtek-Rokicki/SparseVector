#ifndef PROJEKT_2_PROI_SPARSEVECTOR_H
#define PROJEKT_2_PROI_SPARSEVECTOR_H

#include <unordered_map>
#include <iostream>
#include <cstdlib>


class SparseVector{
    public:
    
    std::unordered_map <int, double> svector;
    
    SparseVector();
    
    SparseVector & operator=(const SparseVector &v1);
    SparseVector operator+(const SparseVector &v1);
    SparseVector operator+=(const SparseVector &v1);
    SparseVector operator-(const SparseVector &v1);
    SparseVector operator-=(const SparseVector &v1);
    SparseVector operator*(const SparseVector &v1);
    SparseVector operator*=(const SparseVector &v1);
    
    bool operator==(const SparseVector &v1);
    bool operator!=(const SparseVector &v1);

    friend std::ostream & operator<<(std::ostream & os, const SparseVector & v1);
    friend std::istream & operator>>(std::istream & is, SparseVector & v1);

    double read(int key);
    void change(int key, double value);
    
    //Funkcja wyparta przez przeciazenie operatora <<
    //void show();

};

#endif