#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arc.h"

//fonctions.h
int convertir(const char*,const char*);

Arc::Arc(int b, int e, int v){
	begin = b;
	end = e;
	value = v;}

Arc::Arc(const char* str){
	begin = convertir(str,"%d");
	str = strchr(str,' ')+1;
	end = convertir(str,"%d");
	str = strchr(str,' ')+1;
	value = convertir(str,"%d");}

bool Arc::operator==(const Arc &arc)const{
	return begin==arc.begin && end==arc.end;}

ostream& operator<<(ostream &os, const Arc &arc){
	os << arc.begin << " " << arc.end << " " << arc.value << endl;
	return os;}
