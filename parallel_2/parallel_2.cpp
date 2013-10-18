/*
 * Created by Siganov Ilya 
 * Lab 2.14 - Calculating prefix sums form 0 to 999 in Array of 1000 elements
 */

#include "stdafx.h"

const char* fname = "vector.txt";
const char* summs_fname = "summs.txt";

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
			if (k % 2 != 0)
				continue;
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
	int nElements = 10000;
	VECTOR arr(nElements);
	VECTOR summs(nElements,0);
	VECTOR summs2(nElements,0);
	for(int i = 0; i < nElements; ++i){
		arr[i] = rand();
	}
	int nProcess = 3;
	printf_s("Start calc sums parallel on %d process\n",nProcess);
	double duration = parallel(arr, summs,nProcess);
	std::cout << "Time elapsed "<<duration << std::endl;

	printf_s("Start calc sums sequential\n");
	double duration_seq = parallel(arr, summs2,1);
	std::cout << "Time elapsed "<<duration_seq << std::endl;
	std::cout << "Acceleration " << duration_seq / duration << std::endl;

	std::cout << "Saving" <<std::endl;
	std::ofstream out;
	out.open(fname,std::ios::trunc);
	if(out.is_open()){
		for (VECTOR::const_iterator i = arr.begin(); i != arr.end(); ++i){
			out << *i << " ";
		}
		out << std::endl;
		out.close();
	}

	std::ofstream sum_out;
	sum_out.open(summs_fname,std::ios::trunc);
	if(sum_out.is_open()){
		for (VECTOR::const_iterator i = summs.begin(); i != summs.end(); ++i){
			sum_out << *i << " ";
		}
		sum_out << std::endl;
		sum_out.close();
	}
	return EXIT_SUCCESS;
#endif
	return EXIT_FAILURE;
}

