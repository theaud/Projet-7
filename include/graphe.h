
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
	void printadjacenttab();
	char** getadjacenttab();
	void printmultivoquetab();
	Liste< Liste<int> >* getmultivoquetab();
	void printfermeturetransitive();
	Liste<int>* getfermeturetransitive();
	bool containscircuit();
	static Graphe lire(FILE *file);
	static Liste<Graphe> getdatabase();

	int * calcul_rang();
    bool liste_vide(char** liste,int i);
    bool liste_vide(char** table);
    void afficher(char** table);
    char** suppression(char** table,int* rang,int cmp);
    int * actualisation_rang(char** table,int* rang,int cmp);
};

#endif
