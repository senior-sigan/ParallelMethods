// parallel_4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "LinearCongruentilaGenerator.h"
#include "Cryptographer.h"

int _tmain( int argc, _TCHAR* argv[] ) {
	unsigned seed = time( 0 );
	LinearCongruentilaGenerator gen(seed);
#ifdef _OPENMP
	int nProcess = 4;
	unsigned block_size = 5000000;
	gen.generate( nProcess, block_size );
	gen.generate( 1, block_size*nProcess );

	
	//for ( SEQUENCE::const_iterator i = seq.begin( ); i != seq.end( ); ++i ) {
	//	cout << (int)*i << " ";
	//}
	//cout << endl;

	/*Cryptographer cryptor( seq );
	string open_text = "Hello world.How are you?";
	string cypher = cryptor.encrypt( open_text, nProcess );
	string text = cryptor.encrypt( cypher, nProcess );
	cout <<open_text<<"\n"<< cypher << "\n" << text << endl;
	*/
	//SEQUENCE seq = 
	//	gen.generate( 1, block_size * nProcess );
	return 0;
#endif
	cout << "You haven't got OpenMpi" << endl;
	return EXIT_FAILURE;
}

