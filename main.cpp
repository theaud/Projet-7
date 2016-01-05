#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "graphe.h"
#include "arc.h"
#include "tache.h"

//fonctions.h
int saisirint(const char*,int);
int saisirint(const char*,int,int);
char* saisirstr(const char*,const char*);

void menu_graphe(Liste<Graphe> &graphes){
	int n=1;
	while(n!=0){
		system("CLS");
		cout << "Menu :" << endl;
		cout << "1. Afficher les graphes" << endl;
		cout << "2. Afficher la table d'adjacence" << endl;
		cout << "3. Afficher les multivoques" << endl;
		cout << "4. Afficher les fermetures transitives" << endl;
		cout << "5. Afficher le calcul des rangs" << endl;
		cout << "0. Quitter" << endl;
		n = saisirint("Executer : ",0,5);
		cout << endl;
		switch(n){
		case 1 :
			cout << graphes;
			system("PAUSE");
		break;
		case 2 :
			cout << "----------------------------------------" << endl << endl;
			while(graphes.foreach()){
				graphes.get().printadjacenttab();
				cout << endl << "----------------------------------------" << endl << endl;}
			system("PAUSE");
		break;
		case 3 :
			cout << "----------------------------------------" << endl << endl;
			while(graphes.foreach()){
				graphes.get().printmultivoque();
				cout << endl << "----------------------------------------" << endl << endl;}
			system("PAUSE");
		break;
		case 4 :
			cout << "----------------------------------------" << endl << endl;
			while(graphes.foreach()){
				Graphe fermeture = graphes.get().getfermeturetransitive();
				fermeture.printadjacenttab();
				cout << endl;
				if(fermeture.containscircuit()) cout << "Le graphe contient un circuit.";
				else cout << "Le graphe ne contient pas de circuit.";
				cout << endl << endl;
				cout << "----------------------------------------" << endl << endl;}
			system("PAUSE");
		break;
		case 5 :
			cout << "----------------------------------------" << endl << endl;
			while(graphes.foreach()){
				Graphe fermeture = graphes.get().getfermeturetransitive();
				if(fermeture.containscircuit()) cout << "Pas de calcul de rang car le graphe contient un circuit." << endl;
				else graphes.get().getrangs();
				cout << endl << "----------------------------------------" << endl << endl;}
			system("PAUSE");
		break;}}}

void editer(Liste<Graphe> &graphes){
	int n=1;
	if(graphes.size()>1) n = saisirint("S\202l\202ctionnez le graphe que vous souhaitez modifier : ",1,graphes.size());
	Graphe &graphe = graphes.at(n-1);
	while(n!=0){
		system("CLS");
		cout << graphe << endl;
		cout << "Menu :" << endl;
		cout << "1. Cr\202er une t\203che" << endl;
		cout << "2. Modifier la dur\202 d'une t\203che" << endl;
		cout << "3. Modifier les contraintes d'une t\203che" << endl;
		cout << "4. Supprimer une t\203che" << endl;
		cout << "0. Retour" << endl;
		n = saisirint("Executer : ",0,4);
		switch(n){
		case 1 :{
			int num = graphe.taches.size()+1;
			cout << "num\202ro de t\203che = " << num << endl;
			int duree = saisirint("dur\202e = ",0);
			char *str = saisirstr("contraintes = ","0123456789 ");
			graphe.taches.push(Tache(num,duree,str));
			free(str);
			cout << "T\203che cr\202\202e !" << endl;
			system("PAUSE");}
		break;
		case 2 :{
			int k = saisirint("num\202ro de t\203che = ",1,graphe.taches.size());
			Tache &tache = graphe.taches.at(k-1);
			cout << endl << tache << endl;
			tache.duree = saisirint("dur\202e = ",0);
			cout << "Modification enregistr\202e !" << endl;
			system("PAUSE");}
		break;
		case 3 :{
			int k = saisirint("num\202ro de t\203che = ",1,graphe.taches.size());
			Tache &tache = graphe.taches.at(k-1);
			cout << endl << tache << endl;
			char *str = saisirstr("contraintes = ","0123456789 ");
			tache = Tache(tache.num,tache.duree,str);
			free(str);
			cout << "Modification enregistr\202e !" << endl;
			system("PAUSE");}
		break;
		case 4 :{
			int k = saisirint("num\202ro de t\203che = ",1,graphe.taches.size());
			cout << endl << graphe.taches.pop(k-1) << endl;
			cout << "T\203che supprim\202e !" << endl;
			system("PAUSE");}
		break;}
		if(n!=0) graphe.arcs = Graphe::getarcs(graphe.taches);}}

void menu_contrainte(Liste<Graphe> &graphes){
	int n=1;
	while(n!=0){
		system("CLS");
		cout << "Menu :" << endl;
		cout << "1. Afficher les graphes" << endl;
		cout << "2. Afficher la table d'adjacence" << endl;
		cout << "3. Afficher le calendrier au plus t\223t" << endl;
		cout << "4. Afficher le calendrier au plus tard" << endl;
		cout << "5. Afficher la validation du graphe" << endl;
		cout << "6. Editer le graphe" << endl;
		cout << "0. Quitter" << endl;
		n = saisirint("Executer : ",0,6);
		cout << endl;
		switch(n){
		case 1 :
			cout << graphes;
			system("PAUSE");
		break;
		case 2 :
			cout << "----------------------------------------" << endl << endl;
			while(graphes.foreach()){
				graphes.get().printadjacenttab();
				cout << endl << "----------------------------------------" << endl << endl;}
			system("PAUSE");
		break;
		case 3 :
			cout << "----------------------------------------" << endl << endl;
			while(graphes.foreach()){
				graphes.get().tot();
				cout << endl << "----------------------------------------" << endl << endl;}
			system("PAUSE");
		break;
		case 4 :
			//A faire
		break;
		case 5 :
			//A faire
		break;
		case 6 :
			editer(graphes);
		break;}}}

int main(int argc, char *argv[]){
	cout << "Lecture de la base de donn\202es..." << endl << endl;
	Liste<Graphe> graphes1 = Graphe::getgraphes();
	Liste<Graphe> graphes2 = Graphe::getcontraintes();
	if(graphes1.size()>0 && graphes2.size()>0){
		cout << "D\202mmarage du programme : r\202ussi" << endl << endl;
		int n = saisirint("Voulez-vous lire un graphe (1) ou un tableau de contrainte (2) ? ",1,2);
		switch(n){
		case 1 : menu_graphe(graphes1);
		break;
		case 2 : menu_contrainte(graphes2);
		break;}}
	else cout << "D\202mmarage du programme : \202chou\202" << endl << endl;
	cout << "Fin du programme." << endl;
	graphes1.clear();
	graphes2.clear();
	system("PAUSE");}
