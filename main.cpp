#include <iostream>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "Na.h"
#include "ProbAmpa.h"

int main(int argc, char* argv[]) {
    int num_instances = 5000000;

    if (argc < 2) {
        std::cout << "Pass number of mechanisms as an argument,";
        std::cout << "using default " << num_instances << " instances" << std::endl;
    } else {
        num_instances = atoi(argv[1]);
    }

    std::cout << "\n Channel Instances : " <<  num_instances << std::endl;

    #ifdef _OPENMP
        #pragma omp parallel
        {
            #pragma omp master
            {
                printf (" Number of Threads requested = %i\n", omp_get_num_threads());
            }
        }
    #endif

    #pragma omp parallel
    {
        Na channel_a(num_instances);
        channel_a.compute();

        ProbAmpa channel_b(num_instances);
        channel_b.compute();
    }

    std::cout << std::endl;
}
