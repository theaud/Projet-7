
#ifndef ARC
#define ARC
#include "liste.h"
#include "include.h"

class Arc{
public :
	int begin, end, value;
public :
	Arc(){}
	Arc(const char* str);
	~Arc(){}
	friend ostream& operator<<(ostream &os, const Arc &arc);
};

#endif
