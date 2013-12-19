#include "Algebra.h"

unsigned Algebra::qe2( unsigned num, unsigned deg, unsigned mod ) {
	unsigned s = 1;

	while ( deg != 0 ) {
		if ( ( deg & 1 ) != 0 ) {
			s = s * num % mod;
		}
		deg >>= 1;
		num = num*num % mod;
	}
	return s;
}

unsigned Algebra::gcg( unsigned a, unsigned b ) {
	unsigned r;
	while ( b != 0 ) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

unsigned Algebra::ext_gcg( unsigned a, unsigned b, int* x, int* y ) {
	if ( b == 0 ) {
		*x = 1;
		*y = 0;
		return a;
	}
	else {
		int x1 = 0, x2 = 1, y1 = 1, y2 = 0, q = 0, r = 0;
		int _x, _y;
		while ( b > 0 ) {
			q = a / b;
			r = a - q * b;
			_x = x2 - q * x1;
			_y = y2 - q * y1;

			a = b;
			b = r;
			x2 = x1;
			x1 = _x;
			y2 = y1;
			y2 = _y;
		}
		*x = x2;
		*y = y2;
		return a;
	}
}

unsigned Algebra::reverse( unsigned num, unsigned mod ) {
	int x = 0, y = 0;
	ext_gcg( num, mod, &x, &y );
	if ( x < 0 ) {
		return x + mod;
	}
	else {
		return x;
	}
}

unsigned Algebra::digits( unsigned num ) {
	unsigned dgts=1;
	while ( ( num >>= 1 ) != 0 ) {
		dgts++;
	}
	return dgts;
}

unsigned Algebra::module( const int num, const int mod ) {
	int _num = num % mod;
	if ( _num < 0 ) {
		_num += mod;
	}
	return _num;
}