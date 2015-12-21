#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "graphe.h"
#include "arc.h"

int main(int argc, char *argv[]){
	cout << "	Lecture de la base de donn\202es..." << endl << endl;
	Liste<Graphe> graphes = Graphe::getdatabase();
	if(graphes.size()>0){
		cout << "D\202mmarage du programme : r\202ussi" << endl << endl;
		cout << graphes;
		cout << "Table d'adjacence :" << endl;
		graphes.back().printadjacenttab();
		cout << endl;
		cout << "Table multivoques :" << endl;
		graphes.back().printmultivoquetab();
		cout << endl;
		cout << "Fermetures transitives :" << endl;
		graphes.back().printfermeturetransitive();
		cout << endl;
		if(graphes.back().containscircuit()) cout << "Le graphe contient un circuit.";
		else cout << "Le graphe ne contient pas de circuit.";
		cout << endl << endl;}
	else cout << "D\202mmarage du programme : \202chou\202" << endl << endl;
	cout << "Fin du programme." << endl;
	graphes.clear();
	system("PAUSE");}
