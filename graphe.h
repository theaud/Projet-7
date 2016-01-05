
#ifndef GRAPHE
#define GRAPHE
#include "liste.h"
#include "arc.h"
#include "tache.h"

class Graphe{
public :
	int nbsommets, nbarcs;
	Liste<Arc> arcs;
	Liste<Tache> taches;
public :
	Graphe(){}
	~Graphe(){}
	friend ostream& operator<<(ostream &os, const Graphe &graphe);
	int** getadjacenttab();
	void printadjacenttab();
	Liste< Liste<int> >* getmultivoque();
	void printmultivoque();
	Graphe getfermeturetransitive();
	bool containscircuit();
	static Graphe liregraphe(FILE *file);
	static Liste<Graphe> getgraphes();
	static Liste<Arc> getarcs(Liste<Tache> taches);
	static Graphe lirecontrainte(FILE *file);
	static Liste<Graphe> getcontraintes();
	
	//Fonctions Mathieu
    bool colonne_vide(int** liste,int i);

    int* actualisation_rang(bool afficher);

    void permuter(int**rt ,int i,int j);
    int** getrangs(bool afficher);
    void printrangs(bool afficher);

	//Fonctions Thomas
	void tot();

	//question 9
	bool* getvaliadation();
	void  printvalidation();

	bool point_entrer();
    bool point_sortie();
    bool no_circuit();
    bool tous_sommets_accessible(bool circuit);
    bool tous_sommets_sortie(bool circuit);
};

#endif
