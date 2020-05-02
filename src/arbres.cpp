#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

#include "arbres.h"
/****************************************************************/
/* Objectifs : Constructeur de la classe			*/
/* La construction dépend du type du graphe lu 			*/
/* en argument							*/
/* Ce type est lu dans la première ligne du fichier (filename)	*/
/* Si le type est :						*/
/*  	1 : il s'agit d'un graphe simple			*/	
/* 	2  : il s'agit d'un graphe euclidien			*/
/* En fonction du type vous devez voir quelle structure(s)	*/ 
/* remplir							*/
/****************************************************************/ 
graphe::graphe(char* filename)
{
    // !!! A FAIRE !!! //

	ifstream file(filename);

	file >> this->type;
	file >> this->n;

	for(int i = 0 ; i < this->n ; ++i)
	{
		if(this->type == 1)
			for(int j = 0 ; j < this->n ; ++j)
				file >> this->E[i][j];
		else if(this->type == 2)
		{
			file >> this->coord[i].first;
			file >> this->coord[i].second;
		}
	}
		
	file.close();
}

/****************************************************************/
/* Objectifs : Affichage du contenu de E ou de coord		*/
/* en fonction du type						*/
/****************************************************************/ 
void graphe::affichage()
{
	cout << "n = " << n << endl;

	if(type == 1){
		cout << "Matrice des poids du graphe simple :  " << endl; 	
		cout << "E = " << endl;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < (n-1); j++)
				cout << E[i][j] << "\t";
			cout << E[i][n-1] << endl;		
		}
	}
	else{
		cout << "Coordonnées des noeuds du graphe euclidien :  " << endl; 	
		for(int i = 0 ; i < n; i++)
			cout << "(" << coord[i].first << "," << coord[i].second << ")" << endl;
	}
}


/****************************************************************************/
/* Objectifs : Affichage des aretes et du cout de l'arbre couvrant T de     */
/* poids minimum selon le type du graphe			                        */
/* Vous devez afficher ici le message : cout << "Coût(T) = " << S << endl;  */
/* où S est le coût (à trouver) de l'arbre de poids minimum trouvé par la   */
/* méthode "arbrecouvrant"                                                  */
/****************************************************************************/
void graphe::resultats()
{
    int S = 0;
    // !!! A FAIRE !!! //
	cout << "Coût(T) = " << S << endl; // Ce message doit être affiché
}


/****************************************************************/
/* Objectif : Calcul de l'arbre couvrant de poids minimum.  	*/
/* Vous pouvez coder l'un (Prim) ou l'autre (Kruskal) des 	    */
/* algorithmes donnés dans le cours				                */
/* Cette méthode ne fait que remplir A				            */
/* L'affichage de l'arbre et de son coût doit se faire dans 	*/
/* "resultats()"						                        */
/****************************************************************/ 
void graphe::arbrecouvrant()
{
	   // !!! A FAIRE !!! //
}
