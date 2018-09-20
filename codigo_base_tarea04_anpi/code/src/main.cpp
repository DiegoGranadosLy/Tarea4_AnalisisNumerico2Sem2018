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

  unsigned int metodo;
  unsigned int dimension;
  unsigned int tipo;
  //Loop del menu..!!
  while (true) {
    std::cout << std::endl << std::endl << "!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!" << std::endl << std::endl;
    menu:std::cout << "Elegir método de descomposicion: " << std::endl;
    std::cout << "   1) Doolittle." << std::endl;
    std::cout << "   2) Crout." << std::endl;
    std::cout << "   3) QR." << std::endl;
    std::cout << "   4) Solve LU." << std::endl;
    std::cout << "   5) Solve QR." << std::endl;
    std::cout << "   6) Salir." << std::endl;

    std::cout << std::endl << "Seleccione un metodo para correr: ";
    std::cin >> metodo;
    
    if (metodo > 6 || metodo < 1) {
      std::cout << "Intentar de nuevo: " << std::endl;
      goto menu;
    }else
      if (metodo == 6) {
        std::cout << "Saliendo..." << std::endl;
        break;
      }

    std::cout << std::endl << "0:Double \n1:Float \nOtro:Float \n";
    std::cout << std::endl << "Seleccione el tipo de dato:\n";
    std::cin  >> tipo;

    std::cout << "Dimension de la matriz: ";
    std::cin >> dimension;


    anpi::Matrix<double> AD(dimension,dimension,double(0));
    anpi::Matrix<float> AF(dimension,dimension,float(0));
    
    std::vector<size_t> p;
    p.resize(dimension);

    std::cout << "\n\nIngrese los valores de la matriz\n\n";
    if(tipo==0){
      for(unsigned int i=0;i<dimension;++i){
        for(unsigned int j=0;j<dimension;++j){
          std::cout << "\ni: " << i+1 << "  j: " << j+1 << "  =  ";
          std::cin  >> AD[i][j];
          std::cout << "\n";
        }
      }
    }else{
      for(unsigned int i=0;i<dimension;++i){
        for(unsigned int j=0;j<dimension;++j){
          std::cout << "\ni: " << i+1 << "  j: " << j+1 << "  =  ";
          std::cin  >> AF[i][j];
          std::cout << "\n";
        }
      }
    }

  
    switch (metodo) {
      case 1:                                       //Doolittle
        if (tipo == 0){   //Metodo Double
          std::cout << std::endl << " Doolitle double" << std::endl;
          anpi::Matrix<double>  LU;
          anpi::Matrix<double> inv;
          anpi::luDoolittle(AD,LU,p);
          anpi::luinv(inv,LU);
          std::cout << "\n\nValor de A:\n";
          imprimir(AD);
          std::cout << "\n\nValor de LU:\n";
          imprimir(LU);
          std::cout << "\n\nValor de la inversa:\n";
          imprimir(inv);
        }else{            //Metodo float
          std::cout << std::endl << " Doolitle float" << std::endl;
          anpi::Matrix<float> LU;
          anpi::Matrix<float> inv;
          anpi::luDoolittle(AF,LU,p);
          anpi::luinv(inv,LU);
          std::cout << "\n\nValor de A:\n";
          imprimir(AF);
          std::cout << "\n\nValor de LU:\n";
          imprimir(LU);
          std::cout << "\n\nValor de la inversa:\n";
          imprimir(inv);
        }
        break;
      case 2:                                       //Crout
        if (tipo == 0){   //Metodo Double
          std::cout << std::endl << " Crout double" << std::endl;
          anpi::Matrix<double>  LU;
          anpi::Matrix<double> inv;
          anpi::luCrout(AD,LU,p);
          anpi::luinv(inv,LU);
          std::cout << "\n\nValor de A:\n";
          imprimir(AD);
          std::cout << "\n\nValor de LU:\n";
          imprimir(LU);
          std::cout << "\n\nValor de la inversa:\n";
          imprimir(inv);
        }else{            //Metodo float
          std::cout << std::endl << " Crout float" << std::endl;
          anpi::Matrix<float> LU;
          anpi::Matrix<float> inv;
          anpi::luCrout(AF,LU,p);
          anpi::luinv(inv,LU);
          std::cout << "\n\nValor de A:\n";
          imprimir(AF);
          std::cout << "\n\nValor de LU:\n";
          imprimir(LU);
          std::cout << "\n\nValor de la inversa:\n";
          imprimir(inv);
        }
        break;
      case 3:                                       //QR
        if (tipo == 0){   //Metodo Double
          std::cout << std::endl << " QR double" << std::endl;
          anpi::Matrix<double> Q;
          anpi::Matrix<double> R;
          anpi::qr(AD,Q,R);
          std::cout << "\n\nValor de A:\n";
          imprimir(AD);
          std::cout << "\n\nValor de Q:\n";
          imprimir(Q);
          std::cout << "\n\nValor de R:\n";
          imprimir(R);
        }else{            //Metodo float
          std::cout << std::endl << " QR float" << std::endl;
          anpi::Matrix<float> Q;
          anpi::Matrix<float> R;
          anpi::qr(AF,Q,R);
          std::cout << "\n\nValor de A:\n";
          imprimir(AF);
          std::cout << "\n\nValor de Q:\n";
          imprimir(Q);
          std::cout << "\n\nValor de R:\n";
          imprimir(R);
        }
        break;
      case 4:                                       //Solve QR
        if (tipo == 0){   //Metodo Double
          std::cout << std::endl << " QR double" << std::endl;
          anpi::Matrix<double> Q;
          anpi::Matrix<double> R;
          std::cout << std::endl << " Falta el solve QR double" << std::endl;
        }else{            //Metodo float
          std::cout << std::endl << " QR double" << std::endl;
          anpi::Matrix<float> Q;
          anpi::Matrix<float> R;
          std::cout << std::endl << " Falta el solve QR double" << std::endl;
        }
        break;
      case 5:                                       //Solve LU
        if (tipo == 0){   //Metodo Double
          std::cout << std::endl << " Solve LU double" << std::endl;
          anpi::Matrix<double> LU;
          std::cout << std::endl << " Falta el solve LU double" << std::endl;
        }else{            //Metodo float
          std::cout << std::endl << " Solve LU float" << std::endl;
          anpi::Matrix<float> LU;
          std::cout << std::endl << " Falta el solve LU float" << std::endl;
        }
        break;
      default:
        break;
    }
  }
  return EXIT_FAILURE;
}
