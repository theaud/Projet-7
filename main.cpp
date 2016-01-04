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
				else graphes.get().getrangs(false);
				cout << endl << "----------------------------------------" << endl << endl;}
			system("PAUSE");
		break;}}}

void editer(Liste<Graphe> &graphes){
	int n=0;
	if(graphes.size()>1) n = saisirint("S\202l\202ctionnez le graphe que vous souhaitez modifier : ",1,graphes.size())-1;
	Graphe &graphe = graphes.at(n);
	cout << graphe;
	n = saisirint("Saisissez le num\202ro d'une t\203che \205 cr\202er/modifier ou quittez (0) : ",0,graphes.size());
	while(n!=0){
		Tache &tache = graphe.taches.at(n-1);
		cout << tache << endl;
		n = saisirint("Modifier la dur\202 (1), Modifier les contraintes (2), Supprimer la t\205che (3) ? ",1,3);
		switch(n){
		case 1 : tache.duree = saisirint("dur\203 = ",0,100000);
		break;
		case 2 :
		break;
		case 3 :
		break;}}}

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
			//A faire
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
