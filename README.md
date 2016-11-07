# code_examples
Collection of code examples

### parallel_sort
Tests a number of serial and parallel **sorting algorithms**.

- library-provided: qsort, tbb::parallel_sort
- serial: bubblesort, shakersort
- OpenMP parallel: oddevensort, mergesort
- c++11 thread-based: mergesort

Requires [OpenMP][1] and [Threading Building Blocks][2].
 
### thrust_zip_iterator
Use example for **thrust::zip_iterator**.

Requires [OpenMP][1] and [Thrust][3].

## Author

* **Riccardo Zanella** [riccardo1980](https://github.com/riccardo1980)

## License
This project is licensed under GPL v.2 - see the [LICENSE.txt](LICENSE.txt) file for details. 


[1]: http://www.openmp.org
[2]: https://www.threadingbuildingblocks.org
[3]: https://github.com/thrust


