
#include "../include/arc.h"

//fonctions.h
char* lirestr(FILE*);
int convertir(const char*,const char*);

Arc::Arc(const char* str){
	begin = convertir(str,"%d");
	str = strchr(str,' ')+1;
	end = convertir(str,"%d");
	str = strchr(str,' ')+1;
	value = convertir(str,"%d");}

ostream& operator<<(ostream &os, const Arc &arc){
	os << arc.begin << " " << arc.end << " " << arc.value << endl;
	return os;}
