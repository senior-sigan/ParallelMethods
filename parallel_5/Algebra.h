#pragma once
class Algebra
{
public:
	static unsigned qe2( unsigned num, unsigned deg, unsigned mod );
	static unsigned gcg( unsigned a, unsigned b );
	static unsigned ext_gcg( unsigned a, unsigned b, int* x, int* y );
	static unsigned reverse( unsigned a, unsigned mod );
	static unsigned digits( unsigned num );
	static unsigned module( const int num, const int mod );
};

