/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: 
 * @Date  : 24.02.2018
 */

#include <cstdlib>
#include <iostream>
#include <vector>

#include "LUDoolittle.hpp"
#include "LUCrout.hpp"
#include "QR.hpp"

template<class T>
void imprimir(anpi::Matrix<T> c){
	for (unsigned int i=0;i<c.rows();i++){
  	for (unsigned int j=0;j<c.cols();j++){
  	 std::cout << c[i][j] << "			";
  	}
  	std::cout << "\n";
  }
}

void imprimir(std::vector<float> res){
	for(unsigned int i=0;i<=res.size()-1;i++){
    	std::cout << res[i] << "	";
    }
    std::cout << "\n";
}

int main() {

  // Some example code
  anpi::Matrix<float> A = { { 2, 0,1,2},
                          { 1, 1,1,1},
                          {-1,-2,1,2},
                          {-1,-1,0,1} };


  	std::vector<size_t> p;
    anpi::Matrix<float> LU;
    anpi::Matrix<float> L;
    anpi::Matrix<float> U;
    anpi::Matrix<float> inv;
    anpi::Matrix<float> Ar;

    std::cout << "\nValor de A\n";
    imprimir(A);
    anpi::luDoolittle(A,LU,p);
    anpi::unpackDoolittle(LU,L,U);
    anpi::luinv(inv,LU);
    std::cout << "\nValor de L\n";
    imprimir(L);
    std::cout << "\nValor de U\n";
    imprimir(U);
    std::cout << "\nValor de Inv\n";
    imprimir(inv);
    Ar = A*inv;
  	std::cout << "\nValor de Ar\n";
    imprimir(Ar);
  return EXIT_FAILURE;
}
  
