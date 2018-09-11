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

#include "LUDoolittle.hpp"

template<class T>
void imprimir(anpi::Matrix<T> c){
	for (int i=0;i<c.rows();i++){
  		for (int j=0;j<c.cols();j++){
  			std::cout << c[i][j] << "	";
  		}
  		std::cout << "\n";
  	}
}

int main() {

  // Some example code
  	anpi::Matrix<float> A = { {-1,-2,1,2},
                            { 2, 0,1,2},
                            {-1,-1,0,1},
                            { 1, 1,1,1} };
                            
  	anpi::Matrix<float> B = { { 1, 2, 3, 4},
                            { 5, 6, 7, 8},
                            { 9,10,11,12},
                            {13,14,15,16} };

	anpi::Matrix<float> C = A*B; 
	imprimir(C);

	// anpi::Matrix<float> LU;
  
  	// std::vector<size_t> p;
  	// anpi::luDoolittle(A,LU,p);
  
  return EXIT_FAILURE;
}
  
