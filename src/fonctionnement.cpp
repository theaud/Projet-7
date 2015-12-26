#include "../include/fonctionnement.h"

void partie1()
{
//------------- Lecture de la base de donnees-------------------------------------
	cout << "	Lecture de la base de donn\202es..." << endl << endl;
	Liste<Graphe> graphes = Graphe::getdatabase();

//------------- Traitement du graphes -------------------------------------------

	if(graphes.size()>0)
        {

		//------------- affichage selectif -------------------------------------------
        int choix;
        bool continuer=true;
            do{
            saut_ligne(2);
            cout<<"Table d'adjacence :      1"<<endl;
            cout<<"Table multivoques :      2"<<endl;
            cout<<"Fermetures transitives  :3"<<endl;
            cout<<"Table d'adjacence :  §§§§    4"<<endl;
            cout<<"truc des rang :      §§§§    5"<<endl;
            cout<<"saisiir blabla a refaire : "<<endl;

            cin>> choix;//a voir pour mettre saisie secure
            system("cls");
            saut_ligne(1);
            switch(choix)
                {
                case 1:graphes.back().printadjacenttab();
                    break;
                case 2:graphes.back().printmultivoquetab();
                    break;
                case 3:graphes.back().printfermeturetransitive();
                    break;

                case 5: graphes.back().calcul_rang();// a revoir
                     break;
                default:continuer=false;
                    break;
                }

            }while(continuer);

		}
	else
        { cout << "D\202mmarage du programme : \202chou\202" << endl << endl;}

 //------------- Fin du programme -------------------------------------------

	cout << "Fin du programme." << endl;
	graphes.clear();
	system("PAUSE");



}
