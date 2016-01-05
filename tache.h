
#ifndef TACHE
#define TACHE
#include "liste.h"

class Tache{
public :
	int num, duree;
	Liste<int> contraintes;
public :
	Tache(){}
	Tache(const char* str);
	Tache(int n, int d, const char* str);
	~Tache(){}
	bool operator==(const Tache &tache)const;
	friend ostream& operator<<(ostream &os, const Tache &tache);
};

#endif
