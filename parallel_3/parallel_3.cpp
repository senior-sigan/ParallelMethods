

#include "stdafx.h"

double transpose(MATRIX& a){
	int n = a.size();
	return 0.0;
}
double gauss(MATRIX& a){
	int n = a.size();
	int i,j,k;
	double m;
	double duration = 0.0;
	std::clock_t start = std::clock();

	for (i = 0; i < n; ++i){
		for (j = i+1; j < n; ++j)
			a[j][i] /= a[i][i];
		for (j = i+1; j < n; ++j)
			for (k = i+1; k < n; ++k)
				a[j][k] -= a[j][i] * a[i][k];		
	}

	duration = (std::clock() - start) / (double)(CLOCKS_PER_SEC);
	return duration;
}
void init(MATRIX& a){
	MATRIX::iterator row;
	unsigned size = a.size();
	for (row = a.begin(); row != a.end(); ++row)
		*row = ROW(size);
}
void fill(MATRIX& a){
	MATRIX::iterator row;
	ROW::iterator el;
	for (row = a.begin(); row != a.end(); ++row)
		for (el = row->begin(); el != row->end(); ++el)
			*el = rand();
}
void print(MATRIX& a){
	MATRIX::iterator row;
	ROW::iterator el;
	for (row = a.begin(); row != a.end(); ++row){
		for (el = row->begin(); el != row->end(); ++el){
			std::cout << *el << "\t";
		}
		std::cout << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _OPENMP
	MATRIX a(10);
	init(a);
	fill(a);
	std::cout << gauss(a) << std::endl;
	print(a);
	return EXIT_SUCCESS;
#endif
	std::cout << "You have't openMP" <<std::endl;
	return EXIT_FAILURE;
}

