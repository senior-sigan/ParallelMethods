#include "stdafx.h"

#define MODUL 10

void print( MATRIX& a ) {
	MATRIX::iterator row;
	ROW::iterator el;
	for ( row = a.begin(); row != a.end(); ++row ) {
		for ( el = row->begin(); el != row->end(); ++el ) {
			std::cout << *el << " ";
		}
		std::cout << std::endl;
	}
}

double transpose( MATRIX& a ) {
	int n = a.size();
	return 0.0;
}

long double det( MATRIX& a ) {
	int n = a.size();
	long double det = a[0][0];
	for ( int i = 1; i < n; ++i ) {
		det *= a[i][i];
	}
	return det;
}

MATRIX gauss( const MATRIX a, const int nProcess, double* duration ) {
	omp_set_dynamic( true );
	omp_set_nested( true );
	omp_set_num_threads( nProcess );

	MATRIX res = a;
	int n = a.size();
	double m;
	*duration = 0.0;
	std::clock_t start = std::clock();

	for (int i = 0; i < n - 1; ++i ) {
#pragma omp parallel for private(m)
		for (int j = i + 1; j < n; ++j ) {
			m = res[j][i] / res[i][i];
			for (int k = i + 1; k < n; ++k ) {
				res[j][k] -= m * res[i][k];
			}
			res[j][i] = 0;
		}
	}
	*duration = ( std::clock() - start ) / (double)( CLOCKS_PER_SEC );
	return res;
}

void init( MATRIX& a ) {
	MATRIX::iterator row;
	unsigned size = a.size();
	for ( row = a.begin(); row != a.end(); ++row ) {
		*row = ROW( size );
	}
}

void fill( MATRIX& a ) {
	srand( std::clock() );
	MATRIX::iterator row;
	ROW::iterator el;
	for ( row = a.begin(); row != a.end(); ++row ) {
		for ( el = row->begin(); el != row->end(); ++el ) {
			*el = rand() % 1000 - 500;
		}
	}
}

int _tmain( int argc, _TCHAR* argv[] ) {
#ifdef _OPENMP
	int size = 400;
	MATRIX a( size );
	double duration;
	int nProcess = 4;
	init( a );
	fill( a );
	//print( a );
	std::cout << "Start gaus" << std::endl;
	MATRIX res = gauss( a, nProcess, &duration );
	std::cout << "Duration = " << duration << std::endl;
	std::cout << "DET" << det( a ) << std::endl;
	//print( res );
	return EXIT_SUCCESS;
#endif
	std::cout << "You have't openMP" << std::endl;
	return EXIT_FAILURE;
}

