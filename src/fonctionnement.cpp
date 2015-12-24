#include "../include/fonctionnement.h"

void partie1()
{
//------------- Lecture de la base de donnees-------------------------------------
	cout << "	Lecture de la base de donn\202es..." << endl << endl;
	Liste<Graphe> graphes = Graphe::getdatabase();

//------------- Traitement du graphes -------------------------------------------

	if(graphes.size()>0)
        {
		cout << "D\202mmarage du programme : r\202ussi" << endl << endl;
		cout << graphes;
		cout << "Table d'adjacence :" << endl;
		graphes.back().printadjacenttab();
		saut_ligne(1);
		cout << "Table multivoques :" << endl;
		graphes.back().printmultivoquetab();
		saut_ligne(1);
		cout << "Fermetures transitives :" << endl;
		graphes.back().printfermeturetransitive();
		saut_ligne(1);
		if(graphes.back().containscircuit()) cout << "Le graphe contient un circuit.";
		else cout << "Le graphe ne contient pas de circuit.";
		saut_ligne(2);


		//------------- affichage selectif -------------------------------------------









		}
	else
        { cout << "D\202mmarage du programme : \202chou\202" << endl << endl;}

 //------------- Fin du programme -------------------------------------------

	cout << "Fin du programme." << endl;
	graphes.clear();
	system("PAUSE");



}
