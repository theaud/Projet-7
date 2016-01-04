
#ifndef ARC
#define ARC
#include "liste.h"

class Arc{
public :
	int begin, end, value;
public :
	Arc(){}
	Arc(int b, int e, int v);
	Arc(const char* str);
	~Arc(){}
	bool operator==(const Arc &arc)const;
	friend ostream& operator<<(ostream &os, const Arc &arc);
};

#endif
