
#include "../include/graphe.h"

//fonctions.h
char* lirestr(FILE*);
int convertir(const char*,const char*);

ostream& operator<<(ostream &os, const Graphe &graphe){
	os << "nombre de sommets = " << graphe.nbsommets << endl;
	os << "nombre d'arcs = " << graphe.nbarcs << endl;
	while(graphe.arcs.foreach()) os << graphe.arcs.get();
	return os;}

char** Graphe::getadjacenttab(){
	char **tab = (char**)malloc(sizeof(char*)*nbsommets);
	for(int i=0; i<nbsommets; i++){
		tab[i] = (char*)malloc(sizeof(char)*nbsommets);
		for(int j=0; j<nbsommets; j++) tab[i][j] = '-';}
	while(arcs.foreach()) tab[arcs.get().begin][arcs.get().end] = arcs.get().value+48;
	return tab;}

void Graphe::printadjacenttab(){
	char **tab = getadjacenttab();
	cout << "   ";
	for(int i=0; i<nbsommets; i++) cout << i << " ";
	cout << endl;
	cout << "  ";
	for(int i=0; i<nbsommets; i++) cout << "--";
	cout << endl;
	for(int i=0; i<nbsommets; i++){
		cout << i << "| ";
		for(int j=0; j<nbsommets; j++) cout << tab[i][j] << " ";
		cout << endl;
		free(tab[i]);}
	free(tab);}

Liste< Liste<int> >* Graphe::getmultivoquetab(){
	Liste< Liste<int> > *liste = new Liste< Liste<int> >[nbsommets];
	char **tab = getadjacenttab();
	for(int n=0; n<nbsommets; n++){
		for(int i=0; i<nbsommets; i++){
			if(tab[n][i]!='-') liste[n]["rang 1"].push(i);}
		bool test = liste[n].size();
		while(test){
			Liste<int> rang;
			while(liste[n].back().foreach()){
				for(int i=0; i<nbsommets; i++){
					if(tab[liste[n].back().get()][i]!='-' && !rang.contains(i)) rang.push(i);}}
			rang.sort();
			test = rang.size() && !liste[n].contains(rang);
			if(test) liste[n].push(rang);}}
	for(int i=0; i<nbsommets; i++) free(tab[i]);
	free(tab);
	return liste;}

void Graphe::printmultivoquetab(){
	Liste< Liste<int> > *liste = getmultivoquetab();
	for(int n=0; n<nbsommets; n++){
		cout << "- sommet " << n << endl;
		if(liste[n].size()){
			for(int i=1; liste[n].foreach(); i++)
				cout << "[" << i << "] " << liste[n].get();}
		else cout << "N/A" << endl;}
	delete[] liste;}

Liste<int>* Graphe::getfermeturetransitive(){
	Liste< Liste<int> > *multivoque = getmultivoquetab();
	Liste<int> *liste = new Liste<int>[nbsommets];
	for(int n=0; n<nbsommets; n++){
		while(multivoque[n].foreach()){
			while(multivoque[n].get().foreach()){
				int &sommet = multivoque[n].get().get();
				if(!liste[n].contains(sommet)) liste[n].push(sommet);}}
		liste[n].rsort();}
	delete[] multivoque;
	return liste;}

void Graphe::printfermeturetransitive(){
	Liste<int> *liste = getfermeturetransitive();
	for(int n=0; n<nbsommets; n++){
		cout << "- sommet " << n << endl;
		if(liste[n].size()) cout << liste[n];
		else cout << "N/A" << endl;}
	delete[] liste;}

bool Graphe::containscircuit(){
	Liste<int> *liste = getfermeturetransitive();
	for(int n=0; n<nbsommets; n++){
		if(liste[n].contains(n)){
			delete[] liste;
			return true;}}
	delete[] liste;
	return false;}

Graphe Graphe::lire(FILE *file){
	Graphe graphe;
	char *str = lirestr(file);
	graphe.nbsommets = convertir(str,"%d");
	free(str);
	str = lirestr(file);
	graphe.nbarcs = convertir(str,"%d");
	free(str);
	str = lirestr(file);
	while(strcmp(str,"-1")){
		graphe.arcs.push(str);
		free(str);
		str = lirestr(file);}
	if(graphe.nbarcs!=graphe.arcs.size()){
		graphe.nbarcs = graphe.arcs.size();
		cout << "* WARNING : le nombre d'arcs de correspond pas ! *" << endl;}
	return graphe;}

Liste<Graphe> Graphe::getdatabase(){
	Liste<Graphe> graphes;
	FILE *file = fopen("graphe.txt","r");
	if(file!=NULL){
		while(fgetc(file)!=EOF){
			fseek(file,-1,SEEK_CUR);
			graphes.push(lire(file));}
		fclose(file);}
	else cout << "* Erreur : le fichier graphe.txt est absent ! *" << endl;
	return graphes;}



/*
int nbsommets, nbarcs;
Liste<Arc> arcs;

*/
//pop pour suprimer
int * Graphe::calcul_rang()
{
//----------------- declaration  ---------------------
    int cmp=0;
    int * rang=new int[nbsommets];
    char ** table=getadjacenttab();
//----------------- initialisation -------------------
    for(int i=0;i<nbsommets;i++)
        {rang[i]=-1;}

//----------------- traitement -----------------------

while(liste_vide(table)==0 && cmp<nbsommets+1)//temp que toutes les collone ne sont pas vide
    {rang=actualisation_rang( table,rang,cmp);
    table=suppression(table,rang,cmp);
    cmp++;
    }

    rang=actualisation_rang( table,rang,cmp);
//-----------------------------------------------

cout << "Tableau des rangs :\n";
 for(int i=0;i<nbsommets;i++)
        {cout<<"Sommet :"<<i<<"= rang :"<< rang[i]<<endl;}

return rang;
}

bool Graphe::liste_vide(char** table,int j)
{
for(int i=0;i<nbsommets;i++)
    {if(table[i][j]!='-')
        {return false;}
    }
    return true;
}

bool Graphe::liste_vide(char** table)
{
 for(int i=0;i<nbsommets;i++)
    {for(int j=0;j<nbsommets;j++)
        {if(table[i][j]!='-')
            {return false;}
        }
    }
    return true;
}

void Graphe::afficher(char** table)
{printf("\n");
for(int j=0;j<nbsommets;j++)
   {
    for(int k=0;k<nbsommets;k++)
        {
          printf("%c ",table[j][k]);
        }
        printf("\n");
   }
}

char** Graphe::suppression(char** table,int* rang,int cmp)
{
  for(int valeur=0;valeur<nbsommets;valeur++)
    {if(rang[valeur]==cmp)//la colonne est vide => on va suprimer se sommet
        {for(int j=0;j<nbsommets;j++)
            {for(int k=0;k<nbsommets;k++)
                {if(table[j][k]=='0'+valeur)
                    {table[j][k]='-';}
                }
            }
        }
    }
return table;

}

int * Graphe::actualisation_rang(char** table,int* rang,int cmp)
{
     for(int i=0;i<nbsommets;i++)
            {
            if(liste_vide(table,i) &&rang[i]==-1)//la colonne est vide
                {rang[i]=cmp;}
            }
  return rang;
}

