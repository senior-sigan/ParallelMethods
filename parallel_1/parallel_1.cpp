/*
 * Created by Siganov Ilya 
 * Lab 1.14 - finding max odd number in array with openMP
 */

#include "stdafx.h"
const char* fname = "data.input";

int generator(unsigned process, unsigned size){
	srand((unsigned)time(0));
	std::ofstream out;
	out.open(fname,std::ios::trunc);
	if(out.is_open()){
		//so stupid, but i have'n got time
		out << size << " " << process << std::endl;
		for (unsigned i = 0; i < size; ++i){
			out << rand() << " ";
		} 
		out.close();
	}
	return EXIT_FAILURE;
}

int _tmain(int argc, _TCHAR* argv[]){
	//return generator(4,100000); // WHUT???
#ifdef _OPENMP
	std::cout << "SUCCESS. You have openmp" << std::endl;
	std::ifstream input;
	input.open(fname);
	if (!input.is_open()){
		std::cout << "Can't open file " << fname << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string head;
	std::getline(input, head);
	std::istringstream iss_h(head);
	int size;
	int nProcess;
	iss_h >> size;
	iss_h >> nProcess;

	std::vector<int> ar(size,0);
	std::cout << "Start reading" <<std::endl;
	for (int i = 0; i < size; i++){
		//if (i % 10000 == 0)
		//	std::cout << i << std::endl;
		if (!input.eof()){
			input >> ar[i];
		} else {
			std::cout << "YOU LIE!!! There are not enough numbers in file!!" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	input.close();

	std::vector<int> maxes(nProcess,ar[0]);

	omp_set_dynamic(true);
	omp_set_nested(true);
	omp_set_num_threads(nProcess);
	std::cout << "Size: " << ar.size() << "\nNumber of threads: " << nProcess << std::endl;
	std::cout << "Start finding odd max" << std::endl;
	std::clock_t start;
	start = std::clock();
	//======MAGICK IS HERE================
#pragma omp parallel 
	{
		int procId = omp_get_thread_num();
		std::cout << procId <<std::endl;
#pragma omp for
		for (int i = 0; i < (int)ar.size(); ++i)
			if ((ar[i] % 2 != 0) && (ar[i] > maxes[procId]))
				maxes[procId] = ar[i];
	}
	//======MAGICK END=====================
	int max = maxes[0];
	for (int i = 0; i < (int)maxes.size(); ++i)
		if (maxes[i] > max)
			max = maxes[i];
	//======SO BORING END=================
	double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

	std::cout << "Time elapsed " << duration << std::endl;
	std::cout << "Odd maximum is " << max << std::endl;
	return 0;
#endif
	std::cout << "Fail you have't got openMP" <<std::endl;
	exit(EXIT_FAILURE);
}

