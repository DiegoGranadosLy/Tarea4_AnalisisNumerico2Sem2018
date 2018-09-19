/**
 * Copyright (C) 2017 
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 */

#include <functional>

#include <cmath>

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <exception>
#include <cstdlib>
#include <complex>

/**
 * Unit tests for the matrix class
 */

#include "Matrix.hpp"
#include "Allocator.hpp"
#include "QR.hpp"

// Explicit instantiation of all methods of Matrix


// normal allocator


typedef std::complex<double> dcomplex;

typedef std::allocator<float> alloc;

template class anpi::Matrix<dcomplex,alloc>;
template class anpi::Matrix<double  ,alloc>;
template class anpi::Matrix<float   ,alloc>;
template class anpi::Matrix<int     ,alloc>;

typedef anpi::Matrix<dcomplex,alloc> cmatrix;
typedef anpi::Matrix<double  ,alloc> dmatrix;
typedef anpi::Matrix<float   ,alloc> fmatrix;
typedef anpi::Matrix<int     ,alloc> imatrix;

// aligned allocator
typedef anpi::aligned_allocator<float> aalloc;

template class anpi::Matrix<dcomplex,aalloc>;
template class anpi::Matrix<double  ,aalloc>;
template class anpi::Matrix<float   ,aalloc>;
template class anpi::Matrix<int     ,aalloc>;

typedef anpi::Matrix<dcomplex,aalloc> acmatrix;
typedef anpi::Matrix<double  ,aalloc> admatrix;
typedef anpi::Matrix<float   ,aalloc> afmatrix;
typedef anpi::Matrix<int     ,aalloc> aimatrix;

// row aligned allocator
typedef anpi::aligned_row_allocator<float> aralloc;

template class anpi::Matrix<dcomplex,aralloc>;
template class anpi::Matrix<double  ,aralloc>;
template class anpi::Matrix<float   ,aralloc>;
template class anpi::Matrix<int     ,aralloc>;

typedef anpi::Matrix<dcomplex,aralloc> arcmatrix;
typedef anpi::Matrix<double  ,aralloc> ardmatrix;
typedef anpi::Matrix<float   ,aralloc> arfmatrix;
typedef anpi::Matrix<int     ,aralloc> arimatrix;

#if 1
# define dispatchTest(func) \
  func<cmatrix>();          \
  func<dmatrix>();          \
  func<fmatrix>();          \
  func<imatrix>();          \
                            \
  func<acmatrix>();         \
  func<admatrix>();         \
  func<afmatrix>();         \
  func<aimatrix>();         \
                            \
  func<arcmatrix>();        \
  func<ardmatrix>();        \
  func<arfmatrix>();        \
  func<arimatrix>();

#else
# define dispatchTest(func) func<arfmatrix>(); 
#endif




BOOST_AUTO_TEST_SUITE( Matrix )

template<class M>
void testConstructors() {
  // Constructors
  { // default
    M a;
    BOOST_CHECK( a.rows() == 0);
    BOOST_CHECK( a.cols() == 0);
    BOOST_CHECK( a.dcols() == 0);
  }
  { // unitilialized
    M a(2,3,anpi::DoNotInitialize);
    BOOST_CHECK( a.rows() == 2);
    BOOST_CHECK( a.cols() == 3);
    BOOST_CHECK( a.dcols() >= 3);
  }
  { // default initialized
    M a(3,2);
    BOOST_CHECK( a.rows() == 3);
    BOOST_CHECK( a.cols() == 2);
    BOOST_CHECK( a(0,0) == typename M::value_type(0));
  }
  { // default initialized
    M a(3,2,typename M::value_type(4));
    BOOST_CHECK( a.rows() == 3);
    BOOST_CHECK( a.cols() == 2);
    BOOST_CHECK( a(0,0) == typename M::value_type(4));
  }
  { // initializer_list
    M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
    BOOST_CHECK( a.rows() == 3);
    BOOST_CHECK( a.cols() == 5);
    
    BOOST_CHECK( a(0,0) == typename M::value_type(1));
    BOOST_CHECK( a(1,2) == typename M::value_type(8));
    BOOST_CHECK( a(2,3) == typename M::value_type(14));
  }
  { // Copy constructor
    M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
    M b(a);

    BOOST_CHECK( a==b );
    BOOST_CHECK( b.rows() == 3 );
    BOOST_CHECK( b.cols() == 5 );
    BOOST_CHECK( b.data() != a.data());
  }

  { // Move constructor
    M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
    M b(std::move(a));

    BOOST_CHECK( b.rows() == 3 );
    BOOST_CHECK( b.cols() == 5 );

    BOOST_CHECK( a.empty() );
  }
  { // Mem constructor
    M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
    M b(a.rows(),a.cols(),a.data());

    BOOST_CHECK( a==b );
    BOOST_CHECK( b.rows() == 3 );
    BOOST_CHECK( b.cols() == 5 );
    BOOST_CHECK( b.data() != a.data() );
  }
}


/**
 * Instantiate and test the methods of the Matrix class
 */
BOOST_AUTO_TEST_CASE( Constructors ) {
  dispatchTest(testConstructors);
}

template<class M>
void testComparison() {
  // == and !=
  M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
  M b = { {1,2,3,4,5},{6,7,9,9,10},{11,12,13,14,15} };

  BOOST_CHECK( (a!=b) );
  
  b(1,2)=typename M::value_type(8);
  
  BOOST_CHECK( (a==b) );
}  

BOOST_AUTO_TEST_CASE(Comparison) 
{
  dispatchTest(testComparison);
}

template<class M>
void testAssignment() {
  { // Move assignment
    M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
    M c(a);
    M b;
    b=std::move(a);
    BOOST_CHECK(a.empty() );
    BOOST_CHECK(!b.empty() );
    BOOST_CHECK(b.rows()==3 );
    BOOST_CHECK(b.cols()==5 );
    BOOST_CHECK(b==c );
  }
  { // assignment
    M a = { {1,2,3,4,5},{5,6,7,8,9},{9,10,11,12,13} };
    M b;
    b=a;
    BOOST_CHECK(a==b );
  }  
  { // swap
    M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
    M b = { {13,14},{15,16} };

    M c(a);
    M d(b);

    BOOST_CHECK( a==c );
    BOOST_CHECK( d==b );
    
    c.swap(d);
    BOOST_CHECK( a==d );
    BOOST_CHECK( b==c );
  }
  { // column
    M a = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15} };
    std::vector<typename M::value_type> col = a.column(1);
    std::vector<typename M::value_type> ref = {2,7,12};
    BOOST_CHECK( col == ref );
  }
}

BOOST_AUTO_TEST_CASE(Assignment)
{
  dispatchTest(testAssignment);
}

template<class M>
void testArithmetic() {
  
  {
    M a = { {1,2,3},{ 4, 5, 6} };
    M b = { {7,8,9},{10,11,12} };
    M r = { {8,10,12},{14,16,18} };
    
    M c(a);
    c+=b;
    BOOST_CHECK(c==r );
    c=a+b;
    BOOST_CHECK(c==r );


    c=M{ {1,2,3},{ 4, 5, 6} } + b;
    BOOST_CHECK(c==r );

    c=a+M{ {7,8,9},{10,11,12} };
    BOOST_CHECK(c==r );
  }

  {
    M a = { {1,2,3},{ 4, 5, 6} };
    M b = { {7,8,9},{10,11,12} };
    M r = { {-6,-6,-6},{-6,-6,-6} };
    
    M c(a);
    c-=b;
    BOOST_CHECK( c==r );
    c=a-b;
    BOOST_CHECK( c==r );


    c=M{ {1,2,3},{ 4, 5, 6} } - b;
    BOOST_CHECK( c==r );

    c=a-M{ {7,8,9},{10,11,12} };
    BOOST_CHECK( c==r );
  } 
}

BOOST_AUTO_TEST_CASE(Arithmetic) {
  dispatchTest(testArithmetic);  
}

  /////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(Multiplication) {
  {
    anpi::Matrix<float> a = { {1,2,3},{ 4, 5, 6} };
    anpi::Matrix<float> b = { {7,8,9},{10,11,12},{10,11,12} };
    anpi::Matrix<float> c = { {7,8,9},{10,11,12} };
    anpi::Matrix<float> d;
    anpi::Matrix<float> r = { {57,63,69},{138,153,168} };
    d = a*b;  //Multiplication made it. d = a*b

    for(unsigned int i=0;i< d.rows();++i){
      for(unsigned int j=0;j< d.cols();++j){
        BOOST_CHECK( d[i][j]==r[i][j] );
      }
    }

    d = a*c;  //Multiplication no made it. d=a
    for(unsigned int i=0;i< d.rows();++i){
      for(unsigned int j=0;j< d.cols();++j){
        BOOST_CHECK( d[i][j]==a[i][j] );
      }
    }

    std::vector<float> p    = {1,2,3};
    std::vector<float> pp   = {1,2};
    std::vector<float> pRes = {14,32};
    std::vector<float> pR;
    pR = a*p; //Multiplication made it. pR = a*p
    for(unsigned int i=0;i< pR.size();++i){
      BOOST_CHECK(pR[i]==pRes[i]);
    }

    pR = a*pp; //Multiplication no made it. pR = a*p
    for(unsigned int i=0;i< pR.size();++i){
      BOOST_CHECK( pR[i]==pp[i]);
    }

  }
}

BOOST_AUTO_TEST_CASE(QR){
  anpi::Matrix<float> A = { { 2, 0,1,2},
                          { 1, 1,1,1},
                          {-1,-2,1,2},
                          {-1,-1,0,1} };

  anpi::Matrix<float> Q;
  anpi::Matrix<float> QT;
  anpi::Matrix<float> R;
  anpi::Matrix<float> I;
  anpi::Matrix<float> Ar;
  anpi::qr(A,Q,R);

  QT.allocate(Q.cols(),Q.rows());
  QT.fill(float(0));

  Ar.allocate(A.rows(),A.cols());
  Ar.fill(float(0));  

  anpi::transpose(Q,QT);

  I = QT*Q;

  for (unsigned int i=0;i<I.rows();i++){    //Prueba para QT*Q = I
    for (unsigned int j=0;j<I.cols();j++){
      if(i!=j){
        BOOST_CHECK((I[i][j]<0.00001)||(I[i][j]>-0.00001));   
      }else{
        BOOST_CHECK((I[i][j]<1.00001)||(I[i][j]>0.9998));
      }
    }
  }

  for (unsigned int i=0;i<R.rows();i++){    //Prueba para R = triangular superior
    for (unsigned int j=0;j<R.cols();j++){
      if(i>j){
        BOOST_CHECK((I[i][j]<0.00001)||(I[i][j]>-0.00001));   
      }
    }
  }

  Ar = Q*R;
  for (unsigned int i=0;i<A.rows();i++){    //A = Q*R
    for (unsigned int j=0;j<A.cols();j++){
        BOOST_CHECK((A[i][j]<Ar[i][j]+0.00001)&&(A[i][j]>Ar[i][j]-0.00001));   
    }
  }  
}
  
BOOST_AUTO_TEST_SUITE_END()
