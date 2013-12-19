#pragma once
#include <vector>
#include "Algebra.h"
#include <math.h>
#include <omp.h>

using namespace std;

typedef vector<double> SEQUENCE;

class EIGG
{
	const int FIRST = 0;
	int mod;
	int a;
	int b;
	int iter_seq(int n);
public:
	EIGG(int m);
	SEQUENCE generate(int length, int a, int b);
	static SEQUENCE dpf( SEQUENCE AVal );
	~EIGG();
};

