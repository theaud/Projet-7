
#ifndef GRAPHE
#define GRAPHE
#include "arc.h"
#include "include.h"

class Graphe{
private :
	int nbsommets, nbarcs;
	Liste<Arc> arcs;
public :
	Graphe(){}
	~Graphe(){}
	friend ostream& operator<<(ostream &os, const Graphe &graphe);
//-------------------fonction pour -------------------

	void printadjacenttab();
	char** getadjacenttab();
//-------------------fonction pour -------------------
	void printmultivoquetab();
	Liste< Liste<int> >* getmultivoquetab();
//-------------------fonction pour -------------------
	void printfermeturetransitive();
	Liste<int>* getfermeturetransitive();
//-------------------fonction pour -------------------
	bool containscircuit();
//-------------------fonction pour -------------------
	static Graphe lire(FILE *file);
	static Liste<Graphe> getdatabase();

//-------------------fonction pour le calcul du rang-------------------
	int * calcul_rang();
    bool liste_vide(char** liste,int i);
    bool liste_vide(char** table);
    void afficher(char** table);
    char** suppression(char** table,int* rang,int cmp);
    int * actualisation_rang(char** table,int* rang,int cmp);
//---------------------------------------------------------------------


};

#endif
