#include "EIGG.h"

EIGG::EIGG(int m) {
	this->mod = m;
}

SEQUENCE EIGG::generate(int length, int a = 11, int b = 13) {
	this->a = a;
	this->b = b;
	SEQUENCE seq;
	
	int n = FIRST;
	int seed = iter_seq( n );
	int current = seed;
	do {
		seq.push_back( current );
		current = iter_seq( ++n );
	} while ( --length > 0 );

	return seq;
}

int EIGG::iter_seq( int n ) {
	return Algebra::reverse( a*n + b, mod );
}

EIGG::~EIGG() {
}

SEQUENCE EIGG::dpf( SEQUENCE seq ) {
	const double PI_2 = asin( 1 ) * 4;
	int i, j;
	int n = seq.size();
	SEQUENCE res(n);
	double im;
	double re;
	double arg;

	omp_set_dynamic( true );
	omp_set_nested( true );
	omp_set_num_threads( 4 );
	
	for ( i = 0; i < n; ++i ) {
		im = 0; re = 0; arg = 0;
#pragma omp parallel for
		for ( j = 0; j < n; ++j ) {
			arg = PI_2 * i * j / n;
			im += sin( arg )*seq[j];
			re += cos( arg )*seq[j];
		}
		res[i] = sqrt( im*im + re*re ) / n;
	}

	return res;
}