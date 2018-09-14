/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author:
 * @Date  : 03.03.2018
 */

#include <cmath>
#include <limits>
#include <functional>

#include "Exception.hpp"
#include "Matrix.hpp"

#ifndef ANPI_LU_CROUT_HPP
#define ANPI_LU_CROUT_HPP

namespace anpi {

  /**
   * Auxiliary method used to debug LU decomposition.
   *
   * It separates a packed LU matrix into the lower triangular matrix
   * L and the upper triangular matrix U, such that the diagonal of U
   * is composed by 1's.
   */
  template<typename T>
  void unpackCrout(const Matrix<T>& LU,Matrix<T>& L,Matrix<T>& U) {
    if ((LU.cols()==LU.rows())&&(L.cols()==L.rows())&&
        (U.cols()==U.rows())  &&(LU.cols()==L.cols())&&
        (LU.cols()==U.cols())){ //square Matrix (LU, L and U).
      for(unsigned int i=0;i<LU.cols();++i){
        for(unsigned int j=0;j<LU.cols();++j){
          if(i<j){ //Save on Upper matrix and store a zero on Lower matrix
            U[i][j] = LU[i][j];
            L[i][j] = T(0);
          }else{
            if(i>j){ //Save on Lower matrix and store a zero on Upper matrix
              U[i][j] = T(0);
              L[i][j] = LU[i][j];
            }else{//Diagonal. Store a '1' on Upper and the value on Lower
              U[i][j] = T(1);
              L[i][j] = LU[i][j];
            }
          }
        }
      }
    }
  }


  /**
   * Decompose the matrix A into a lower triangular matrix L and an
   * upper triangular matrix U.  The matrices L and U are packed into
   * a single matrix LU.
   *
   * Crout's way of packing assumes a diagonal of
   * 1's in the U matrix.
   *
   * @param[in] A a square matrix
   * @param[out] LU matrix encoding the L and U matrices
   * @param[out] permut permutation vector, holding the indices of the
   *             original matrix falling into the corresponding element.
   *             For example if permut[5]==3 holds, then the fifth row
   *             of the LU decomposition in fact is dealing with the third
   *             row of the original matrix.
   *
   * @throws anpi::Exception if matrix cannot be decomposed, or input
   *         matrix is not square.
   */
  template<typename T>
  void luCrout(const Matrix<T>& A,Matrix<T>& LU,std::vector<size_t>& permut){
    // http://claudiovz.github.io/metodos_numericos_I/
    // sistema_de_ecuaciones_lineales/sistema_de_ecuaciones_lineales008.html#___sec96
    if ((A.rows()==permut.size()) && (A.cols()==A.rows())){
      LU = A;        //Se realiza la copia de la matriz A en LU
      for(unsigned int i=0;i<A.rows();++i){
        permutation(i,LU,permut);           //Se permutan todas las
      }                                     //filas antes de comenzar el algoritmo.
      for(unsigned int j=1;j<LU.cols();++j){//Para la primer fila de
        LU[0][j] = LU[0][j]/LU[0][0];       //la matriz uper: U
      }

      for(unsigned int i=1;i<LU.cols();++i){
        for(unsigned int j=i;j<LU.cols();++j){
          for(unsigned int k=0; k<i ;++k){    //Para encontrar la columna de lower.
            LU[j][i] -= LU[j][k]*LU[k][i];
          }
        }
        if(i!=(LU.cols()-1)){                 //Para que no toque la ultima diagonal
          for(unsigned int j=i+1;j<LU.cols();++j){
            for(unsigned int k=0; k<=i ;++k){ //Para encontrar la columna de upper.
              if(k!=i){
                LU[i][j] -= LU[i][k]*LU[k][j];
              }else{
                LU[i][j] = LU[i][j]/LU[k][i];
              }
            }
          }
        }
      }
    }else{
      throw anpi::Exception("Dimensiones incompatibles\n");
    }
  }

}

#endif
