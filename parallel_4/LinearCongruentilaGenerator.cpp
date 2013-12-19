#include "stdafx.h"
#include "LinearCongruentilaGenerator.h"


LinearCongruentilaGenerator::LinearCongruentilaGenerator( unsigned _seed ) : seed( _seed ) {
	a = 4;
	mod = 65;
	c = 9;
}

SEQUENCE LinearCongruentilaGenerator::generate( int nProcess, unsigned blockSize ) {
	omp_set_dynamic( true );
	omp_set_nested( true );
	omp_set_num_threads( nProcess );

	unsigned length = blockSize * nProcess;
	SEQUENCE sequence( length );
	clock_t start = clock();
#pragma omp parallel
	{
		int n = omp_get_thread_num();
		unsigned an = (unsigned)pow( a, n );
		sequence[n*blockSize] = ( seed * an + c*( an - 1 ) / ( a - 1 ) ) % mod;
		for ( int i = 1; i < blockSize; ++i ) {
			sequence[n*blockSize + i] = ( a * sequence[n*blockSize + i - 1] + c ) % mod;
		}
	}
	cout << "Timer " << ( clock( ) - start ) / (double)( CLOCKS_PER_SEC ) << endl;
	return sequence;
}

LinearCongruentilaGenerator::~LinearCongruentilaGenerator() {
}
