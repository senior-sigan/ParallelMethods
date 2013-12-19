#include "FourEIGG.h"


FourEIGG::FourEIGG() {}

SEQUENCE FourEIGG::generate( int length, int nProcess ) {
	omp_set_dynamic( true );
	omp_set_nested( true );
	omp_set_num_threads( nProcess );
	int primes_size = 143;
	int pice = length / nProcess;
	vector<SEQUENCE> seq(nProcess);
#pragma omp parallel 
	{
		int prime = primes[(time(NULL) * omp_get_thread_num()) % primes_size];
		printf( "%d\n", prime );
		EIGG gen( prime );
		seq[omp_get_thread_num( )] = gen.generate(pice, prime / 2, prime / 4);
	}

	SEQUENCE res;
	for ( unsigned int i = 0; i < seq.size( ); ++i ) {
		res.insert( res.begin( ), seq[i].begin( ), seq[i].end( ) );
	}

	return res;
}

FourEIGG::~FourEIGG() {
}
