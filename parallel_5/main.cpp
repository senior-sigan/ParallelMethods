#include <iostream>
#include "FourEIGG.h"
#include <fstream>
#include <ctime>

bool doStuff = true;
bool compare = true;

int main() {
#ifdef _OPENMP
	char fname_seq[] = "seq.txt";
	char fname_spectr[] = "spectr.txt";
	int nProcess = 4;
	int length = 40000;
	SEQUENCE res;


	if ( !compare ) {
		cout << "Dont compare" << endl;
		FourEIGG gen;
		cout << "Start generating" << endl;
		clock_t start = clock( );
		res = gen.generate( length, nProcess );
		cout << "Time elapsed " << ( clock( ) - start ) / (double)CLOCKS_PER_SEC << endl;
		if ( doStuff ) {
			cout << "Calculate spectr" << endl;
			SEQUENCE spectr = EIGG::dpf( res );

			cout << "SAving in file" << endl;
			ofstream out_sp;
			out_sp.open( fname_spectr, std::ios::trunc );
			if ( out_sp.is_open( ) ) {
				for ( unsigned int i = 1; i < spectr.size( ); ++i ) {
					out_sp << i << " " << spectr[i] << endl;
				}
				out_sp.close( );
			}

			ofstream out_seq;
			out_seq.open( fname_seq, std::ios::trunc );
			if ( out_seq.is_open( ) ) {
				for ( unsigned int i = 1; i < res.size( ); ++i ) {
					out_seq << res[i] << " ";
				}
				out_seq.close( );
			}
		}
	}
	else {
		cout << "Will be compared 1 process vs " << nProcess << endl;
		FourEIGG gen;
		cout << "Start generating" << endl;
		clock_t start = clock( );
		res = gen.generate( length, nProcess );
		double delay_parallel = ( clock() - start ) / (double)CLOCKS_PER_SEC;
		cout << "Time elapsed for " << nProcess <<" process " << delay_parallel << endl;

		start = clock();
		gen.generate( length, 1 );
		double delay_one = ( clock( ) - start ) / (double)CLOCKS_PER_SEC;
		cout << "Time elapsed for 1 process " << delay_one << endl;
		cout << "Acceleration " << delay_one / delay_parallel << endl;
	}
	return EXIT_SUCCESS;
#endif
	std::cout << "No OMP" << endl;
}