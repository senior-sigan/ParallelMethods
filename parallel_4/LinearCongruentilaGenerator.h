#pragma once
#include <vector>
#include <omp.h>

using namespace std;
typedef vector<unsigned char> SEQUENCE;

class LinearCongruentilaGenerator
{
	unsigned a;
	unsigned c;
	unsigned mod;
	unsigned seed;

public:
	LinearCongruentilaGenerator( unsigned seed );
	SEQUENCE generate( int nProcess, unsigned length );
	~LinearCongruentilaGenerator();
};

