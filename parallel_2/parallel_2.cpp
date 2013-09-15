/*
 * Created by Siganov Ilya 
 * Lab 2.14 - Calculating prefix sums form 0 to 999 in Array of 1000 elements
 */

#include "stdafx.h"


void sequential(VECTOR inp, VECTOR& sum){
	unsigned len = inp.size();
	sum[0] = inp[0];
	for (unsigned i = 1; i < len; ++i){
		sum[i] = sum[i-1] + inp[i];
	}
}

double parallel(VECTOR arr, VECTOR& summs, unsigned nProcess = 2){

	int nElements = arr.size();
	std::clock_t start = std::clock();
	int m = (int)log(nElements)/log(2); 
	omp_set_dynamic(true);
	omp_set_nested(true);
	omp_set_num_threads(nProcess);
	for (int d = 0; d < m; ++d){
#pragma omp parallel for
		for (int k = 0; k < nElements; ++k){
			if (k >= pow(2,d))
				summs[k] = arr[k] + arr[k - pow(2,d)];
			else
				summs[k] = arr[k];
		}
		summs.swap(arr);
	}
	double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	return duration;
}

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _OPENMP
	int nElements = 1000000;
	VECTOR arr(nElements);
	VECTOR summs(nElements,0);
	for(int i = 0; i < nElements; ++i){
		arr[i] = rand();
	}
	printf_s("Start calc sums parallel. Array.size = %d\n",nElements);
	double duration = parallel(arr, summs,3);
	std::cout << "\nTime elapsed "<<duration << std::endl;

	printf_s("Start calc sums parallel. Array.size = %d\n",nElements);
	double duration_seq = parallel(arr, summs,1);
	std::cout << "\nTime elapsed "<<duration_seq << std::endl;

	return EXIT_SUCCESS;
#endif
	return EXIT_FAILURE;
}

