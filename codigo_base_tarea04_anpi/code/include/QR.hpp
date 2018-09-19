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

#ifndef ANPI_QR_HPP
#define ANPI_QR_HPP

namespace anpi {

  /**
   * Transpose a matrix Q to QT
   * @param[in]  Q : Matrix to transpose
   * @param[out] QT: Matrix
   *
   */
  template<typename T>
  void transpose(anpi::Matrix<T>& Q,anpi::Matrix<T>& QT ){
    for(unsigned int i=0;i<Q.rows();++i){
      for(unsigned int j=0;j<Q.rows();++j){
        QT[i][j] = Q[j][i];
      }
    }
  }


  /**
   * Decompose the matrix A into a ortogonal matrix and an
   * upper triangular matrix R.
   *Uses the Householder tranformation
   * @param[in] A a square matrix
   * @param[out] Q matrix encoding the ortogonal matrix
   * @param[out] R upper triangular matrix
   *
   * @throws anpi::Exception if matrix cannot be decomposed, or input
   *         matrix is not square.
   */
  template<typename T>
  void qr( const anpi::Matrix<T>& A,anpi::Matrix<T>& Q,anpi::Matrix<T>& R ){
    
    if(A.cols()==A.rows()){ //A is a square matrix.
      R=A;
      anpi::Matrix<T> temp(A.rows(),A.cols(),T(0));
      for(unsigned int j=0;j<A.cols()-1;++j){
        T *vector= (T*)malloc(A.rows()*sizeof(T));
        T alfa = T(0);
        T norma=T(0);
        for(unsigned int i=j;i<A.rows();++i){
          vector[i] = R[i][j];  //Add the column to the vector
          alfa+=R[i][j]*R[i][j];//Calculate the alfa value
          if(i!=j){
            norma+=vector[i]*vector[i];//Calculate the u's norma.
          }
        }
        vector[j]-=sqrt(alfa);  // u =a:1 - ||a:1||eo
        norma+=vector[j]*vector[j];
        for(unsigned int u=0;u<R.rows();++u){   //uuT
          for(unsigned int v=0;v<R.rows();++v){
            if(u<j && v<j){//Before the column where we operate
              if(u==v){
                temp[u][v] = T(1);//Diagonal.
              }else{
                temp[u][v] = T(0);//No diagonal.
              }
            }else{
              if (u==v){          //Diagonal
                temp[u][v] = T(1)-T(2)*((vector[u]*vector[v])/norma);
              }else{              //No diagonal
                temp[u][v] =T(-1)*T(2)*((vector[u]*vector[v])/norma);
              }
            }
          }
        }
        ///////////////////////////////////////////////////////////
        //Here we have to make the multiplication..!!
        if(j==0){
          Q=temp;
          R=temp*A;
        }else{
          anpi::Matrix<T> Rtemp(R.rows(),R.cols(),T(0));
          anpi::Matrix<T> Qtemp(R.rows(),R.cols(),T(0));
          anpi::Matrix<T> QT   (A.rows(),A.cols(),T(0));
          Rtemp = R;
          Qtemp = Q;
          transpose(temp,QT);
          Q=Qtemp*QT;
          R=QT*Rtemp;
        }
        temp = Matrix<T>(A.rows(),A.cols(),T(0));
        free(vector);
      }
      anpi::Matrix<T> res(R.rows(),R.cols(),T(0));
      res = Q*R;
    }else{
      throw anpi::Exception("Dimensiones incompatibles\n");
    }
  }

}

#endif
