#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <omp.h>

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {
  try{
    omp_set_nested(1);   /* make sure nested parallism is on */
    int nthreads;
    if ( const char *env_th = std::getenv("OMP_NUM_THREADS") )
      std::istringstream( env_th ) >> nthreads;
    else
      nthreads = omp_get_num_procs();

    nthreads = std::max( nthreads, 1);
    int nthreads1 = nthreads/3;
    int nthreads2 = nthreads - nthreads1;

    cout << "Starting a total number of " << nthreads << " threads"<< endl
      << "Task 1: " << nthreads1 << endl
      << "Task 2: " << nthreads2 << endl << endl;

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
  }
  catch ( std::exception& e){
    cerr << "Error: " << e.what() << endl;
    exit(EXIT_FAILURE);

  }
  return (EXIT_SUCCESS);
}
