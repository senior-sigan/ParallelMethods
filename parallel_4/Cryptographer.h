#pragma once
#include <string>
#include "LinearCongruentilaGenerator.h"
using namespace std;

class Cryptographer
{
	SEQUENCE sequence;
public:
	Cryptographer(SEQUENCE seq);
	string encrypt( string msg, int nProcess );
	string decrypt( string cypher, int nProcess );
	~Cryptographer();
};

