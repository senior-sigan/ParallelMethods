#include "stdafx.h"
#include "Cryptographer.h"


Cryptographer::Cryptographer( SEQUENCE seq ) :sequence( seq ) {
}

string Cryptographer::encrypt( string msg, int nProcess ) {
	omp_set_dynamic( true );
	omp_set_nested( true );
	omp_set_num_threads( nProcess );

	int length = msg.length() / nProcess;

	int block_size = msg.length() / nProcess;
	string cypher(msg.length(),0);

#pragma omp parallel
	{
		int n = omp_get_thread_num();
		int offset = n * block_size;
		for ( int i = 0; i < block_size; ++i ) {
			cypher[i + offset] = ( (unsigned char)msg[i + offset] ^ (unsigned char)sequence[( i + offset ) % sequence.size()] );
		}
	}

	return cypher;
}


Cryptographer::~Cryptographer() {
}
