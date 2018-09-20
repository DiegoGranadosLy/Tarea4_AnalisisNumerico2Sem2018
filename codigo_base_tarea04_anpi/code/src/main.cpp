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

  int metodo;
  int dimension;
  //Loop del menu..!!
  while (true) {
    std::cout << std::endl << std::endl << "!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!" << std::endl << std::endl;
    menu:std::cout << "Elegir método de descomposicion: " << std::endl;
    std::cout << "   1) Doolittle." << std::endl;
    std::cout << "   2) Crout." << std::endl;
    std::cout << "   3) QR." << std::endl;
    std::cout << "   4) Salir." << std::endl;

    std::cout << std::endl << "Seleccione un metodo para correr: ";
    std::cin >> metodo;
    
    if (metodo > 4 || metodo < 1) {
      std::cout << "Intentar de nuevo: " << std::endl;
      goto menu;
    }else
      if (metodo == 4) {
        std::cout << "Saliendo..." << std::endl;
        break;
      }

    std::cout << "Dimension de la matriz: ";
    std::cin >> dimension;

  
    switch (metodo) {
      case 1:                           //Algoritmo de biseccion
        std::cout << " Doolitle" << std::endl;
        break;
      case 2:                           //Algoritmo de biseccion
        std::cout << " Crout" << std::endl;
        break;
      case 3:                           //Algoritmo de biseccion
        std::cout << " QR" << std::endl;
        break;
      default:
        break;
    }
  }
  return EXIT_FAILURE;
}
