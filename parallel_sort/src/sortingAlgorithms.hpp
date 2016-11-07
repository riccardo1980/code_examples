#ifndef SORTINGALGORITHMS_HPP
#define SORTINGALGORITHMS_HPP

#include <functional> // std::less and std::greater
#include <algorithm>  // std::swap

/*
 for type T the following implementations must be provided:
 
 template< class T >
 void swap( T& a, T& b );

 template< class T >
 struct greater{
    inline bool operator()( T& a, T& b );
 };

 */

/****************************************************************************
 *    BUBBLE SORT
 ****************************************************************************/
/**
  * bubble sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  * @param cmp compare function
  *
  * cmp(a,b) returns true if a > b
  * use std::less<T>() for non decreasing order  
  * use std::greater<T>() for non increasing order  
  * ( T must be equal to the type pointed by the iterators )
  */
template <typename RandomAccessIterator, typename C>
inline void bubbleSort( RandomAccessIterator begin, 
                 RandomAccessIterator end, 
                 C cmp){
  
  bool swapFlag = true; // true if a swap operation has been performed

  while (swapFlag){
    --end;
    swapFlag = false;
    for( RandomAccessIterator it = begin; 
         it < end; ++it ){
      if ( !cmp( *it,  *(it+1) ) ){
        std::swap( *it, *(it+1));
        swapFlag = true;   
      } 
    } 
  }

}
/**
  * bubble sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  *
  * sorts in non decreasing order
  */
template <typename RandomAccessIterator>
inline void bubbleSort( RandomAccessIterator  begin,
    RandomAccessIterator end){

  bubbleSort( begin, end, 
      std::less< typename RandomAccessIterator::value_type >() );


}

/****************************************************************************
 *    SHAKER SORT
 ****************************************************************************/
/**
  * shaker sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  * @param cmp compare function
  *
  * cmp(a,b) returns true if a > b
  * use std::less<T>() for non decreasing order  
  * use std::greater<T>() for non increasing order  
  * ( T must be equal to the type pointed by the iterators )
  */
template <typename RandomAccessIterator, typename C>
inline void shakerSort( RandomAccessIterator begin, 
                 RandomAccessIterator end, 
                 C cmp){
  
  bool swapFlag = true; // true if a swap operation has been performed

  while (swapFlag){
    --end;
    swapFlag = false;
    for( RandomAccessIterator it = begin; 
         it < end; ++it ){
      if ( !cmp( *it,  *(it+1) ) ){
        std::swap( *it, *(it+1));
        swapFlag = true;   
      } 
    }
    
    if ( ! swapFlag )
      break;
   
    ++begin;
    swapFlag = false;
    for( RandomAccessIterator it = end-2;
        it > begin -2; --it){
      if ( !cmp(*it,  *(it+1) ) ){
        std::swap( *it, *(it+1));
        swapFlag = true;   
      } 
    }
  }
}
/**
  * shaker sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  *
  * sorts in non decreasing order
  */
template <typename RandomAccessIterator>
inline void shakerSort( RandomAccessIterator  begin,
    RandomAccessIterator end){

  shakerSort( begin, end, 
  std::less< typename RandomAccessIterator::value_type >() );

}

/****************************************************************************
 *    ODDEVEN SORT
 ****************************************************************************/
/**
  * oddeven sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  * @param cmp compare function
  *
  * cmp(a,b) returns true if a > b
  * use std::less<T>() for non decreasing order  
  * use std::greater<T>() for non increasing order  
  * ( T must be equal to the type pointed by the iterators )
  */
template <typename RandomAccessIterator, typename C>
inline void oddevenSort( RandomAccessIterator begin, 
                 RandomAccessIterator end, 
                 C cmp){
  
  RandomAccessIterator it;
#pragma omp parallel shared(begin, end) private(it)
  for ( int phase = 0; phase < end-begin; ++phase){
    // odd-even 
    if (phase % 2 == 0)    
#pragma omp for
      for( it = begin; it < end-1; it+=2 ){
        if ( !cmp( *it,  *(it+1) ) ){
          std::swap( *it, *(it+1));
        } 
      } // here we have an implicit barrier
    else
      // even-odd
#pragma omp for
      for( it = begin+1; it < end-1; it+=2 ){
        if ( !cmp( *it,  *(it+1) ) ){
          std::swap( *it, *(it+1));
        } 
      } // here we have an implicit barrier
    } // end of parallel region
}

/**
  * oddeven sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  *
  * sorts in non decreasing order
  */
template <typename RandomAccessIterator>
inline void oddevenSort( RandomAccessIterator  begin,
    RandomAccessIterator end){

  oddevenSort( begin, end, 
  std::less< typename RandomAccessIterator::value_type >() );

}

/****************************************************************************
 *    MERGE SORT
 ****************************************************************************/
#define CS 256 
template <typename RandomAccessIterator, typename C>
inline void omp_recursiveMergeSort( RandomAccessIterator begin, 
                 RandomAccessIterator end, 
                 C cmp){
 
    int N = end - begin; 
    if ( N > CS){
        int N_a = (N+1)/2; 
#pragma omp task firstprivate (begin)
        omp_recursiveMergeSort( begin, begin + N_a, cmp); 
#pragma omp task firstprivate (begin, end)
        omp_recursiveMergeSort( begin + N_a, end, cmp); 
#pragma omp taskwait
        std::inplace_merge( begin, begin + N_a, end, cmp );
    }
    else{
      std::sort( begin, end, cmp );
    }

}

/**
  * merge sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  * @param cmp compare function
  *
  * cmp(a,b) returns true if a > b
  * use std::less<T>() for non decreasing order  
  * use std::greater<T>() for non increasing order  
  * ( T must be equal to the type pointed by the iterators )
  */
template <typename RandomAccessIterator, typename C>
inline void omp_mergeSort( RandomAccessIterator begin, 
                 RandomAccessIterator end, 
                 C cmp){

#pragma omp parallel
  {
#pragma omp single
    omp_recursiveMergeSort( begin, end, cmp);
  }
}

/**
  * merge sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  *
  * sorts in non decreasing order
  */
template <typename RandomAccessIterator>
inline void omp_mergeSort( RandomAccessIterator  begin,
    RandomAccessIterator end){

  omp_mergeSort( begin, end, 
  std::less< typename RandomAccessIterator::value_type >() );

}


#include <thread>
/****************************************************************************
 *    MERGE SORT
 ****************************************************************************/
template <typename RandomAccessIterator, typename C>
inline void cpp11_recursiveMergeSort( RandomAccessIterator begin, 
    RandomAccessIterator end, 
    C cmp, int th = 0){

  int N = end - begin; 
  if ( N > CS){
    int N_a = (N+1)/2; 

    if ( th ){
      int th_a = (th+1)/2;
      std::thread other( cpp11_recursiveMergeSort<RandomAccessIterator,C>, begin, begin + N_a, cmp, th_a );

      cpp11_recursiveMergeSort( begin + N_a, end, cmp, th-th_a); 
      other.join();
    } 
    else
    {
      cpp11_recursiveMergeSort( begin, begin + N_a, cmp); 
      cpp11_recursiveMergeSort( begin + N_a, end, cmp); 

    }
    // wait
    std::inplace_merge( begin, begin + N_a, end, cmp );
  }
  else{
    std::sort( begin, end, cmp );
  }


}

/**
 * merge sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  * @param cmp compare function
  *
  * cmp(a,b) returns true if a > b
  * use std::less<T>() for non decreasing order  
  * use std::greater<T>() for non increasing order  
  * ( T must be equal to the type pointed by the iterators )
  */
template <typename RandomAccessIterator, typename C>
inline void cpp11_mergeSort( int threads, RandomAccessIterator begin, 
                 RandomAccessIterator end, 
                 C cmp){

  cpp11_recursiveMergeSort( begin, end, cmp, threads); 

  }

/**
  * merge sort implementation
  * @parameter begin iterator to first element 
  * @parameter end iterator one past last element
  *
  * sorts in non decreasing order
  */
template <typename RandomAccessIterator>
inline void cpp11_mergeSort( int threads, RandomAccessIterator  begin,
    RandomAccessIterator end){

  cpp11_mergeSort( threads, begin, end, 
  std::less< typename RandomAccessIterator::value_type >() );

}


#endif

