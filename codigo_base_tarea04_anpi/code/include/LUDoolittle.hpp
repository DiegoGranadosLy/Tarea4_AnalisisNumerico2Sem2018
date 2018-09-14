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
#include <algorithm>

#include "Exception.hpp"
#include "Matrix.hpp"

#ifndef ANPI_LU_DOOLITTLE_HPP
#define ANPI_LU_DOOLITTLE_HPP

namespace anpi {


  /**
   * Auxiliary method used to debug LU decomposition.
   *
   * It separates a packed LU matrix into the lower triangular matrix
   * L and the upper triangular matrix U, such that the diagonal of L
   * is composed by 1's.
   */
  template<typename T>
  void unpackDoolittle(const Matrix<T>& LU,
                       Matrix<T>& L,
                       Matrix<T>& U) {

    throw anpi::Exception("To be implemented yet");
  }

  /**
   * Auxiliary method used to permute the matrix.
   *
   * Takes the place (column) and check under the diagonal
   * the mayor element to make the pivot.
   * Interchange the rows and copy the change in p.
   */
  template<typename T>
  void permutation(unsigned int col,Matrix<T>& LU,std::vector<size_t>& permut) {
    T mayorValue     = LU[col][col]; //Initial value (on diagonal).
    unsigned int row = col;
    for(unsigned int tempRow=col;tempRow<LU.rows();++tempRow){
      if (LU[tempRow][col] > mayorValue){
        mayorValue = LU[tempRow][col];
        row = tempRow;
      }
    }
    if (row != col){
      T temp;
      permut[row] = permut[col];
      permut[col] = row;
      for(unsigned int j=0;j<LU.cols();++j){
        temp       = LU[row][j];
        LU[row][j] = LU[col][j];
        LU[col][j] = temp;
      }
    }
  }

  /**
   * Decompose the matrix A into a lower triangular matrix L and an
   * upper triangular matrix U.  The matrices L and U are packed into
   * a single matrix LU.
   *
   * The L matrix will have in the Doolittle's LU decomposition a
   * diagonal of 1's
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
  void luDoolittle(const Matrix<T>& A, Matrix<T>& LU,
                   std::vector<size_t>& permut) {
    if ((A.rows()==permut.size()) && (A.cols()==A.rows())){
      LU = A;        //Se realiza la copia de la matriz A en LU
      for(unsigned int k=0;k<LU.cols()-1;++k){
        permutation(k,LU,permut);
        for(unsigned int i=k+1;i<LU.cols();++i){
          const T factor = LU[i][k]/LU[k][k];
          for(unsigned int j=k;j<LU.cols();++j){
            LU[i][j]-= factor*LU[k][j];
          }
          LU[i][k] = -factor;
        }
      }
    }else{
      throw anpi::Exception("Dimensiones incompatibles\n");
    }
  }
}

#endif
