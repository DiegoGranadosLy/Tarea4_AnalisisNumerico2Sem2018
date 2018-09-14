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

template<class T>
void imprimir(anpi::Matrix<T> c){
	for (unsigned int i=0;i<c.rows();i++){
  		for (unsigned int j=0;j<c.cols();j++){
  			std::cout << c[i][j] << "	";
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
  	// anpi::Matrix<float> A = { {-1,-2,1,2},
   //                          { 2, 0,1,2},
   //                          {-1,-1,0,1},
   //                          { 1, 1,1,1} };

	anpi::Matrix<float> B ={{ 1,-1, 3, 6},
							{ 2,-3, 1,-5},
							{-6, 5, 4, 1},
							{-1,-2,-1, 2} };

	// anpi::Matrix<float> C = A*B; 
	// imprimir(C);

	// anpi::Matrix<float> LU;
  
  	// std::vector<size_t> p;
    anpi::Matrix<float> LU(B.rows(),B.cols(),float(0));
    anpi::Matrix<float> L (B.rows(),B.cols(),float(0));
    anpi::Matrix<float> U (B.rows(),B.cols(),float(0));
    std::vector<size_t> p;
    p.push_back(0);
    p.push_back(1);
    p.push_back(2);
    p.push_back(3);
    std::cout << "\nValor de B\n";
    imprimir(B);
    // anpi::luCrout(B,LU,p);
    anpi::unpackDoolittle(B,L,U);
  	// anpi::luDoolittle(B,LU,p);
  	std::cout << "\nValor de L\n";
    imprimir(L);
    std::cout << "\nValor de U\n";
    imprimir(U);
  return EXIT_FAILURE;
}
  
