#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>

#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/transform_reduce.h>
#include <thrust/functional.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/tuple.h>

using std::cout;
using std::cerr;
using std::endl;
using std::exception;
using std::runtime_error;

typedef thrust::host_vector< double >::iterator dblIter;
typedef thrust::tuple< double, double > doubleTuple;

struct squared_difference : thrust::unary_function< doubleTuple, double > {
  double operator() ( const doubleTuple& it ){
    double t = thrust::get<0>( it ) - thrust::get<1>( it );
    return t*t;
  }
};

double L2_2_diff( thrust::host_vector<double>::iterator first1, 
    thrust::host_vector<double>::iterator last1, thrust::host_vector<double>::iterator first2 ){
    
  typedef thrust::tuple< dblIter, dblIter > dblIterTuple;
  
  // only the first iterator in the tuple is relevant for the purposes of last
  typedef thrust::zip_iterator< dblIterTuple > ZipIterator;
  ZipIterator first( thrust::make_tuple( first1, first2 ) );
  ZipIterator last( thrust::make_tuple( last1, first2 ) );
    
  return transform_reduce( first, last, squared_difference(), 0.0, thrust::plus<double>() ); 

}

int main ( int argc, char *argv[] ) {
  try{

    thrust::host_vector< double >  a(4), b(4);

    for( int ii = 0; ii < a.size(); ++ii ){
        a[ii] = ii;
        b[ii] = 2.0*ii + 1.0;
    }

    typedef thrust::tuple< dblIter, dblIter > dblIterTuple;
    typedef thrust::zip_iterator< dblIterTuple > ZipIterator;

    ZipIterator first( thrust::make_tuple( a.begin(), b.begin() ) );

    // only the first iterator in the tuple is relevant for the purposes of last
    ZipIterator last( thrust::make_tuple( a.end(), b.begin() ) );

    squared_difference fun;
    cout << "naive for: " << endl;
    for ( ZipIterator it = first; it < last; ++it ){
      cout << thrust::get<0> ( *it ) << " "
           << thrust::get<1> ( *it ) << " "
           << fun( thrust::make_tuple(thrust::get<0> ( *it ),thrust::get<1> ( *it ) ))
           << endl;
    }
    
    thrust::host_vector< double >  c(4);
    transform( first, last, c.begin(), fun ); 

    cout << "transform: " << endl;
    for( int ii = 0; ii < 4; ++ii ){
        cout << c[ii] << endl; 
    }
    
    cout << "transform_reduce: " << endl;
    cout << transform_reduce( first, last, fun, 0.0, thrust::plus<double>() ) << endl; 

    cout << "L2_2_diff: " << L2_2_diff( a.begin(), a.end(), b.begin() ) << endl;

  } 
  catch (exception& e){
    cerr << "ERROR: " << e.what() << endl;
    exit (EXIT_FAILURE);
  }
  exit (EXIT_SUCCESS);
}
