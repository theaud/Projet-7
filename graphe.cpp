#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe.h"

//fonctions.h
char* lirestr(FILE*);
int convertir(const char*,const char*);

ostream& operator<<(ostream &os, const Graphe &graphe){
	os << "nombre de sommets = " << graphe.nbsommets << endl;
	os << "nombre d'arcs = " << graphe.nbarcs << endl;
	if(graphe.taches.size()){
		os << "liste des t\203ches :" << endl;
		while(graphe.taches.foreach()) os << graphe.taches.get();}
	if(graphe.arcs.size()){
		os << "liste des arcs :" << endl;
		while(graphe.arcs.foreach()) os << graphe.arcs.get();}
	return os;}

int** Graphe::getadjacenttab(){
	int **tab = (int**)malloc(sizeof(int*)*nbsommets);
	for(int i=0; i<nbsommets; i++){
		tab[i] = (int*)malloc(sizeof(int)*nbsommets);
		for(int j=0; j<nbsommets; j++) tab[i][j] = -1;}
	while(arcs.foreach()) tab[arcs.get().begin][arcs.get().end] = arcs.get().value;
	return tab;}

void Graphe::printadjacenttab(){
	int **tab = getadjacenttab();
	cout << "   ";
	for(int i=0; i<nbsommets; i++) printf("%2d ",i);
	cout << endl;
	cout << "  ";
	for(int i=0; i<nbsommets; i++) cout << "---";
	cout << endl;
	for(int i=0; i<nbsommets; i++){
		cout << i << "| ";
		for(int j=0; j<nbsommets; j++){
			if(tab[i][j]==-1) cout << " - ";
			else printf("%2d ",tab[i][j]);}
		cout << endl;
		free(tab[i]);}
	free(tab);}

Liste< Liste<int> >* Graphe::getmultivoque(){
	Liste< Liste<int> > *liste = new Liste< Liste<int> >[nbsommets];
	int **tab = getadjacenttab();
	for(int n=0; n<nbsommets; n++){
		for(int i=0; i<nbsommets; i++){
			if(tab[n][i]!=-1) liste[n]["rang 1"].push(i);}
		bool test = liste[n].size();
		while(test){
			Liste<int> rang;
			while(liste[n].back().foreach()){
				for(int i=0; i<nbsommets; i++){
					if(tab[liste[n].back().get()][i]!=-1 && !rang.contains(i)) rang.push(i);}}
			rang.sort();
			test = rang.size() && !liste[n].contains(rang);
			if(test) liste[n].push(rang);}}
	for(int i=0; i<nbsommets; i++) free(tab[i]);
	free(tab);
	return liste;}

void Graphe::printmultivoque(){
	Liste< Liste<int> > *liste = getmultivoque();
	for(int n=0; n<nbsommets; n++){
		cout << "- sommet " << n << endl;
		if(liste[n].size()){
			for(int i=1; liste[n].foreach(); i++)
				cout << "[" << i << "] " << liste[n].get() << endl;}
		else cout << "N/A" << endl;}
	delete[] liste;}

Graphe Graphe::getfermeturetransitive(){
	Liste< Liste<int> > *multivoque = getmultivoque();
	Liste<Arc> arcs;
	Graphe graphe = *this;
	for(int n=0; n<nbsommets; n++){
		while(multivoque[n].foreach()){
			while(multivoque[n].get().foreach()){
				Arc arc(n,multivoque[n].get().get(),n);
				if(!graphe.arcs.contains(arc)){
					graphe.nbarcs++;
					graphe.arcs.push(arc);}}}}
	delete[] multivoque;
	return graphe;}

bool Graphe::containscircuit(){
	int **tab = getadjacenttab();
	bool test=false;
	for(int i=0; i<nbsommets; i++){
		if(tab[i][i]!=-1) test = true;
		free(tab[i]);}
	free(tab);
	return test;}

Graphe Graphe::liregraphe(FILE *file){
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
	free(str);
	if(graphe.nbarcs!=graphe.arcs.size()){
		graphe.nbarcs = graphe.arcs.size();
		cout << "* Warning : le nombre d'arcs ne correspond pas ! *" << endl;}
	return graphe;}

Liste<Graphe> Graphe::getgraphes(){
	Liste<Graphe> graphes;
	FILE *file = fopen("graphe.txt","r");
	if(fgetc(file)!=EOF){
		fseek(file,-1,SEEK_CUR);
		while(fgetc(file)!=EOF){
			fseek(file,-1,SEEK_CUR);
			graphes.push(liregraphe(file));}
		fclose(file);}
	else cout << "* Erreur : le fichier graphe.txt est absent ou vide ! *" << endl;
	return graphes;}

Liste<Arc> Graphe::getarcs(Liste<Tache> taches){
	Liste<Arc> arcs;
	while(taches.foreach()){
		if(taches.get().contraintes.size()==0){
			arcs.push(Arc(0,taches.get().num,0));}}
	bool test;
	for(int i=1; i<=taches.size(); i++){
		test = true;
		while(taches.foreach()){
			if(taches.get().contraintes.contains(i)){
				arcs.push(Arc(i,taches.get().num,taches.at(i-1).duree));
				test = false;}}
		if(test) arcs.push(Arc(i,taches.size()+1,taches.at(i).duree));}
	return arcs;}

Graphe Graphe::lirecontrainte(FILE *file){
	Graphe graphe;
	char *str = lirestr(file);
	graphe.nbsommets = convertir(str,"%d");
	free(str);
	str = lirestr(file);
	while(strcmp(str,"-1")){
		graphe.taches.push(str);
		free(str);
		str = lirestr(file);}
	free(str);
	if(graphe.nbsommets!=graphe.taches.size()){
		graphe.nbsommets = graphe.taches.size();
		cout << "* Warning : le nombre de t\203ches ne correspond pas ! *" << endl;}
	graphe.arcs = getarcs(graphe.taches);
	graphe.nbarcs = graphe.arcs.size();
	graphe.nbsommets += 2;
	return graphe;}

Liste<Graphe> Graphe::getcontraintes(){
	Liste<Graphe> graphes;
	FILE *file = fopen("contrainte.txt","r");
	if(fgetc(file)!=EOF){
		fseek(file,-1,SEEK_CUR);
		while(fgetc(file)!=EOF){
			fseek(file,-1,SEEK_CUR);
			graphes.push(lirecontrainte(file));}
		fclose(file);}
	else cout << "* Erreur : le fichier contrainte.txt est absent ou vide ! *" << endl;
	return graphes;}

//Code Mathieu sur le calcul des rangs
void Graphe::printrangs(bool afficher)
{
  int** rang = getrangs(afficher);

  for(int i=0;i<nbsommets;i++)
      {
        cout<<" Rang = "<<rang[1][i]<<" Sommet= "<<rang[0][i]<<endl;
      }

}


bool Graphe::colonne_vide(int** table,int j)
{
for(int i=0;i<nbsommets;i++)
    {if(table[i][j]!=-1)
        {return false;}
    }
    return true;
}




int* Graphe::actualisation_rang(bool afficher)
{
  int ** table;
  int cmp=0,diminution=0;
  int *rang=new int[nbsommets];

    for(int i=0;i<nbsommets;i++)
        {rang[i]=-1;}



  do{

        table=getadjacenttab();
      if(afficher){printadjacenttab();}

    diminution=0;
     for(int i=0;i<nbsommets;i++)
            {
            if(colonne_vide(table,i) &&rang[i]==-1)//la colonne est vide
                { if(afficher){cout <<"On retire le sommet  : "<<i<<endl;}
                rang[i]=cmp;
                 diminution++;

                for(int j=0; j<arcs.size(); j++)
                    {
                       if(arcs.at(j).begin==i)
                            {arcs.pop(j);
                            nbarcs--;
                            j--;
                            }
                    }
                }

            }

       if(afficher){cout <<"on a diminue de  "<<diminution<<" sommets "<<endl;}


            cmp++;
    }while(arcs.size()>0 );

 for(int i=0;i<nbsommets;i++)
        {if(rang[i]==-1)
            {rang[i]=cmp;}
        }




  return rang;
}

int** Graphe::getrangs(bool afficher)
{
    int* rang=actualisation_rang( afficher);

    Graphe graphe=*this;

    int ** rt=new int*[2];
    int tampon[2];
    rt[0]=new int[nbsommets];
    rt[1]=new int[nbsommets];

// recopie du tableau
    for(int i=0;i<nbsommets;i++)
        {
         rt[0][i]=i;
         rt[1][i]=rang[i];
        }

//trie en fonction du rang
    for(int i=0;i<nbsommets;i++)
        {for(int j=i;j<nbsommets;j++)
             {
                if(rt[1][i]>rt[1][j])
                    {
                     permuter(rt,i,j);
                    }
             }
        }

return rt;
}

void Graphe::permuter(int**rt ,int i,int j)
{
int tampon[2];

tampon[0]=rt[0][i];
tampon[1]=rt[1][i];

rt[0][i]=rt[0][j];
rt[1][i]=rt[1][j];

rt[0][j]=tampon[0];
rt[1][j]=tampon[1];

}

void Graphe::tot(){

int new_begin;
int new_ending;
int tps[nbsommets];
int rang[6][6];
rang [0][0] = 0;
rang [0][1] = 0;
rang [1][0] = 3;
rang [1][1] = 1;
rang [2][0] = 2;
rang [2][1] = 2;
rang [3][0] = 1;
rang [3][1] = 3;
rang [4][0] = 4;
rang [4][1] = 4;
rang [5][0] = 5;
rang [5][1] = 4;
rang [6][0] = 5;
rang [6][1] = 5;
tps[0] = 0;
for(int i = 1; i < nbsommets; i++){
    new_begin = rang[i][0];
    new_ending = rang[(i+1)][0];
    cout << "i = " << i;
    while(arcs.foreach()){
        if (arcs.get().begin == new_begin && arcs.get().end == new_ending){
            tps[i] = tps[i-1] + arcs.get().value;
            cout << "value = " << arcs.get().value << endl;
        }
    }
}
for (int i = 0; i < nbsommets-1; i++){ cout << " " <<tps[i] << " ";}
}

//-------------------------------------------------------------------------------------
//--------------- 9) exo de validation ------------------------------------------------
//-------------------------------------------------------------------------------------
bool* getvaliadation();
{
    bool* test=new bool[5];
    test[0]=point_entrer();
    test[1]=point_sortie();
    test[2]=no_circuit();
    test[3]=tous_sommets_accessible()
    test[4]=tous_sommets_sortie(bool circuit);

return test;
}

void Graphe::printvalidation()
{
    bool* test=getvaliadation();




}


bool Graphe::point_entrer()
{
    int ** rang=getrangs(false);
    int cmp=0;
//----------------------------------------------------
for(int i=0;i<nbsommets;i++)
        {if(0==rand[1][i])
            {cmp++;}
        }
//----------------------------------------------------
    if(cmp==0)
        {cout<< " WARNING ERROR point d'entrer ";
        return false;
        }
    else if(cmp ==1)    {return true;}
    else                {return false;}

}


bool Graphe::point_sortie()
{
    int ** rang=getrangs(false);
    int min=0;
    int cmp=0;
//----------------------------------------------------
    for(int i=0;i<nbsommets;i++)
        {if(min>rand[1][i])
            {min=rand[1][i];}
        }
//----------------------------------------------------
     for(int i=0;i<nbsommets;i++)
        {if(min==rand[1][i])
            {cmp++;}
        }
//----------------------------------------------------
    if(cmp==0)
        {cout<< " WARNING ERROR point de sortie ";
        return false;
        }
    else if(cmp ==1)    {return true;}
    else                {return false;}
}

bool Graphe::no_circuit();

bool Graphe::tous_sommets_accessible(bool circuit)
{if(circuit==true){return false;}
 //-----------------------------------------------------------
    int * visiter=new int[nbsommets];
    for(int i=0;i<nbsommets;i++){visiter[i]=-1;}
//------------------------------------------------------

//a faire





}

bool Graphe::tous_sommets_sortie(bool circuit);
{
if(circuit==true){return false;}
 //-----------------------------------------------------------

    int * tester=new int[nbsommets];
    for(int i=0;i<nbsommets;i++){tester[i]=-1;}
 //-----------------------------------------------------------

// a faire



}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
