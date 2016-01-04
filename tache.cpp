#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tache.h"

//fonctions.h
int convertir(const char*,const char*);

Tache::Tache(const char* str){
	num = convertir(str,"%d");
	str = strchr(str,' ')+1;
	duree = convertir(str,"%d");
	str = strchr(str,' ')+1;
	int n = convertir(str,"%d");
	while(n>0){
		contraintes.push(n);
		str = strchr(str,' ')+1;
		n = convertir(str,"%d");}}

bool Tache::operator==(const Tache &tache)const{
	return num==tache.num;}

ostream& operator<<(ostream &os, const Tache &tache){
	os << tache.num << " " << tache.duree << " " << tache.contraintes << endl;
	return os;}
