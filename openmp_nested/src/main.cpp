#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>

using std::cout;
using std::endl;

int main(int argc, char **argv) {

  omp_set_nested(1);   /* make sure nested parallism is on */
  int nprocs;
  std::istringstream( std::getenv("OMP_NUM_THREADS") ) >> nprocs;
  nprocs = std::max( nprocs, 1);
  //int nprocs = omp_get_num_procs();
  int nthreads1 = nprocs/3;
  int nthreads2 = nprocs - nthreads1;

#pragma omp parallel default(none) shared(nthreads1, nthreads2, cout) num_threads(2)
#pragma omp single
  {
#pragma omp task
#pragma omp parallel for num_threads(nthreads1) 
    for (int i=0; i<16; i++){
      	#pragma omp critical
	    {
	cout << "Task 1: thread " << omp_get_thread_num() 
           << " of the " << omp_get_team_size(2) 
           << " children of " << omp_get_ancestor_thread_num(1) 
           << " handling iter " << i << endl;
	    }
    }
#pragma omp task
#pragma omp parallel for num_threads(nthreads2) 
    for (int j=0; j<16; j++){
      	#pragma omp critical
	    {
      cout << "Task 2: thread " << omp_get_thread_num() 
           << " of the " << omp_get_team_size(2) 
           << " children of " << omp_get_ancestor_thread_num(1) 
           << " handling iter " << j << endl;
	    }
    }
  }
  return 0;
}
