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
    anpi::Matrix<float> Q;
    anpi::Matrix<float> R;
    std::cout << "\nValor de A\n";
    imprimir(A);
    anpi::qr(A,Q,R);
    std::cout << "\nValor de Q\n";
    imprimir(Q);
    std::cout << "\nValor de R\n";
    imprimir(R);
    anpi::Matrix<float> Ar = Q*R;
  	std::cout << "\nValor de Ar\n";
    imprimir(Ar);
  return EXIT_FAILURE;
}
  
