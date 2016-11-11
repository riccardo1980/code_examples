# code_examples
Collection of code examples. Custom CMAKE modules are supplied for
compilation support.

## Getting Started
### Prerequisites
In order to compile all the examples, the following libraries are required:

- [OpenMP][1]
- [Threading Building Blocks][2]
- [Thrust][3]

Some examples require only a subset of above libraries, so check the prerequisites of the code you are interested in.

### Installation
Clone the project, then use `cmake` on an empty build folder: for example, if you are interested in **parallel\_sort** code:

```
git clone https://github.com/riccardo1980/code_examples
cd code_examples
mkdir build
cd build
cmake ../parallel_sort
make
```
## List of examples
Source code of each example is collected in a separate folder.

### parallel_sort
Tests a number of serial and parallel **sorting algorithms**, requires [OpenMP][1] and [Threading Building Blocks][2].

Implemented algorithms:
- bubblesort, shakersort (serial C++ implementation)
- oddevensort, mergesort (OpenMP based implementation)
- mergesort (based on C++11 std::thread)

Code can call exterrnal sorting functions, such as: qsort, tbb::parallel_sort.
 
### thrust_zip_iterator
Use example for **thrust::zip_iterator**, requires [OpenMP][1] and [Thrust][3].

### openmp_nested 
Use example for OpenMP **nested parallelism**, requires [OpenMP][1].

### MATLAB/Octave matlab_keyvalue
Facilities for parsing key-value optional function parameters.

## Author

* **Riccardo Zanella** [riccardo1980](https://github.com/riccardo1980)

## License
This project is licensed under GPL v.2 - see the [LICENSE.txt](LICENSE.txt) file for details. 


[1]: http://www.openmp.org
[2]: https://www.threadingbuildingblocks.org
[3]: https://github.com/thrust


