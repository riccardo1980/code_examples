#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>

#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

#include "omp.h"

#include "tbb/parallel_sort.h"

#include "sortingAlgorithms.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& data){
  
  typename std::vector<T>::const_iterator begin = data.begin();
  typename std::vector<T>::const_iterator end = data.end();
  for( ; begin < end-1; ++begin)
    os << *begin << " ";
    
  os << *begin;

  return os;
}

double myrand(){
    return ( 2.0 * rand() ) /RAND_MAX - 1.0;
}

template < typename RAIter >
typename RAIter::value_type L2relativeError ( RAIter ref_begin, RAIter ref_end, RAIter approx_begin ){

  typedef typename RAIter::value_type value_type;
  value_type num = value_type(0.0);
  value_type den = value_type(0.0);
  for( ; ref_begin < ref_end; ++ref_begin, ++approx_begin ){
    value_type tn =  ( *ref_begin - *approx_begin );
    num += tn * tn; 
    den += *ref_begin * *ref_begin;
  }
 return std::sqrt( num / den ); 
}

extern "C"{

int c_compar( const void *a, const void *b){
    return (int) (  (*(double*)a) - (*(double*)b) > 0 );
} 

}

using std::cout;
using std::cerr;
using std::endl;
using std::exception;
using std::vector;
void print_cmd (const char *me){
  cout << "Usage" << endl
         << me << " N k" << endl
         << " N       number of elements to sort" << endl
         << " k       one of the following:" << endl
         << "    0    c qsort" << endl
         << "    1    bubblesort" << endl
         << "    2    shakersort" << endl
         << "    3    omp oddevensort" << endl
         << "    4    omp oddevensort" << endl
         << "    5    tbb parallel sort" << endl
         << "    6    c++11 parallel mergesort" << endl;
}

int main (int argc, char *argv[]){
  try {

    int N = 200;
    int k = 1;
    switch (argc){
      case 3:
        std::istringstream( argv[2] ) >> k;
      case 2:
        std::istringstream( argv[1] ) >> N;
        case 1:
          break;
        default:
          print_cmd(argv[0]);
          throw std::runtime_error( "Wrong number of command line parameters! ");
    } 

    double start, stop;
    vector<double> dd(N);
    std::generate( dd.begin(), dd.end(), myrand );

    vector<double> dd1 = dd;
    cout << std::scientific << std::setprecision(2); 
   
    start = omp_get_wtime();
    std::sort( dd1.begin(), dd1.end() );
    stop = omp_get_wtime();
    cout << "std::sort" << endl
      <<"Time:   " << stop - start << " [s]" << endl;
     
    int threads = omp_get_max_threads();
    
    vector<double> dd2 = dd;
    std::stringstream ss;
    switch (k){
        case 0:
          ss << "c qsort";  
          start = omp_get_wtime();
          qsort ( &dd2[0], dd2.size(), sizeof(double), c_compar );
          stop = omp_get_wtime();
          break;
        case 1: 
          ss << "bubblesort";
          start = omp_get_wtime();
          bubbleSort( dd2.begin(), dd2.end() );
          stop = omp_get_wtime();
          break; 
        case 2: 
          ss << "shakersort";
          start = omp_get_wtime();
          shakerSort( dd2.begin(), dd2.end() );
          stop = omp_get_wtime();
          break;
        case 3: 
          ss << "omp oddevensort (cores " << threads << ")";
          start = omp_get_wtime();
          oddevenSort( dd2.begin(), dd2.end() );
          stop = omp_get_wtime();
          break;
        case 4: 
          ss << "omp mergesort (cores " << threads << ")";
          start = omp_get_wtime();
          omp_mergeSort( dd2.begin(), dd2.end() );
          stop = omp_get_wtime();
          break;
        case 5: 
          ss << "tbb::parallel_sort (cores " << threads << ")";
          start = omp_get_wtime();
          tbb::parallel_sort( dd2.begin(), dd2.end() );
          stop = omp_get_wtime();
          break;
        case 6: 
          ss << "cpp11 parallel mergesort (cores " << threads << ")";
          start = omp_get_wtime();
          cpp11_mergeSort( threads, dd2.begin(), dd2.end() );
          stop = omp_get_wtime();
          break;
        default:
          print_cmd( argv[0] );
          throw std::runtime_error( "Kernel not recognized! ");
    }

    cout << ss.str() << endl;
    cout << "Time:   " 
      << stop - start << " [s]" << endl;
    cout << "Error:  " << L2relativeError( dd1.begin(), dd1.end(), dd2.begin() ) << endl; 

    //cout << dd1 << endl;    
    //cout << endl << dd2 << endl;    

  }
  catch( exception &e){
    cerr << "Error: " << e.what() << endl;
    exit(EXIT_FAILURE);
  }
  
  return (EXIT_SUCCESS);

}
