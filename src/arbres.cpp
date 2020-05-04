#include <iostream>
#include <fstream>
#include <utility>

#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

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
    // int S = 0;
	double S = 0;
    // !!! A FAIRE !!! //
if(this->type == 1)
{
	for(int i = 0 ; i < this->n ; ++i)
		for(int j = 0 ; j < this->n ; ++j)
			if(this->A[i][j] == true)
					S += this->E[i][j];
}
else if(this->type == 2)
{
	for(int i = 0 ; i < this->n ; ++i)
		for(int j = 0 ; j < this->n ; ++j)
			if(this->A[i][j] == true)
				S += this->distanceDeuxPoints(this->coord[i], this->coord[j]);
}

	cout << "Coût(T) = " << round(S) << endl; // Ce message doit être affiché
}

void graphe::arbrecouvrant_grapheSimple()
{
	//on ajoute a la liste de sommets couverts le premier sommet
	vector<int> C { 0 };	
	vector<pair<int,int>> omega_C;
	pair<int,int> e_etoile;
	/* les valeurs de A sont déjà init à false, donc A vide */

	for(int k = 1 ; k < this->n ; ++k)
	{
		// remplir omega_C et attribuer val a e etoile	
		int j = 0;
		int poidsPlusFaible = infini;
		for(int i = 0 ; i < this->n ; ++i)
		{
			for(j = i ; j < this->n ; ++j)
			{
				//arete = i,j
				pair<int,int> arete = make_pair(i, j);

				//si l'arete n'existe pas, on skip
				if(this->E[i][j] == 0)
					continue;

				//verifier si une des extremités est dans C et l'autre précisément pas
				bool C_contains_i = find(C.begin(), C.end(), i) != C.end();
				bool C_contains_j = find(C.begin(), C.end(), j) != C.end();
				if(!C_contains_i != !C_contains_j)
				{
					//si ce n'est pas déjà dans l'ensemble
					if(find(omega_C.begin(), omega_C.end(), arete) == omega_C.end())
						omega_C.push_back(arete);

					int poidsArete = this->E[i][j];
					if(poidsArete < poidsPlusFaible)
					{
						e_etoile = arete; //on met dans e etoile l'arete au poids le plus petit
						poidsPlusFaible = poidsArete;
					}
				}	
			}
		}
		
		this->A[e_etoile.first][e_etoile.second] = true;

		//si l'extremite i n'est pas comprise dans C..
		if(find(C.begin(), C.end(), e_etoile.first) == C.end())
			C.push_back(e_etoile.first);
		else
			C.push_back(e_etoile.second);

		// Retirer e etoile de omega c
		omega_C.erase(find(omega_C.begin(), omega_C.end(), e_etoile));
		
		// Ajouter toutes les aretes partant du nouveau sommet dans C
		for(int i = 0 ; i < this->n ; ++i)
			if(this->E[C.back()][i] != 0)
				omega_C.push_back(make_pair(C.back(), i));

		// retirer l'arete e etoile qui part du nouveau sommet dans C
		omega_C.erase(find(omega_C.begin(), omega_C.end(), make_pair(e_etoile.second, e_etoile.first)));


		// cout<<"\ndebug iteration "<<k<<endl;

		// cout<<"C = "<<endl;
		// for(int i : C)
		// 	cout<<i<<endl;

		// cout<<endl;
		// cout<<"omega C ="<<endl;
		// for(pair<int,int> p : omega_C)
		// 	cout<<p.first<<";"<<p.second<<endl;

		// cout<<"e etoile = "<<endl;
		// cout<<endl<<e_etoile.first<<";"<<e_etoile.second<<endl;

		// cout<<"A="<<endl;
		// int v, w;
		// for( v = 0 ; v < this->n ; ++v)
		// {
		// 	for(w = 0 ; w < this->n - 1 ; ++w)
		// 		cout<<this->A[v][w]<<"\t";
		// 	cout<<this->A[v][w]<<endl;
		// }
	}
}

double graphe::distanceDeuxPoints(pair<int,int> a, pair<int,int> b)
{
	int xa = a.first;
	int xb = b.first;
	int ya = a.second;
	int yb = b.second;
	return sqrt((xb - xa) * (xb - xa) + (yb - ya) * (yb - ya));
}

void graphe::arbrecouvrant_grapheEuclidien()
{
	//on ajoute a la liste de sommets couverts le premier sommet
	vector<pair<int,int>> C { this->coord[0] };	
	vector<pair<pair<int,int>,pair<int,int>>> omega_C;
	pair<pair<int,int>,pair<int,int>> e_etoile;
	/* les valeurs de A sont déjà init à false, donc A vide */

	for(int k = 1 ; k < this->n ; ++k)
	// for(int k = 1 ; k <= 2 ; ++k)
	{
		int poidsPlusFaible = infini;
		//je parcours toutes les aretes
		for(int i = 0 ; i < this->n ; ++i)
		{
			for(int j = 0 ; j < this->n ; ++j)
			{
				// remplir omega_C et attribuer val a e etoile	
				pair<pair<int,int>,pair<int,int>> arete = make_pair(this->coord[i], this->coord[j]);

				//si l'arete n'existe pas, on skip
				if(this->coord[i] == this->coord[j])
					continue;

				//verifier si une des extremités est dans C et l'autre précisément pas
				bool C_contains_i = find(C.begin(), C.end(), this->coord[i]) != C.end();
				bool C_contains_j = find(C.begin(), C.end(), this->coord[j]) != C.end();
				if(!C_contains_i != !C_contains_j)
				{
					//si ce n'est pas déjà dans l'ensemble
					if(find(omega_C.begin(), omega_C.end(), arete) == omega_C.end())
						omega_C.push_back(arete);

					int poidsArete = round(this->distanceDeuxPoints(this->coord[i], this->coord[j]));
					if(poidsArete < poidsPlusFaible)
					{
						e_etoile = arete; //on met dans e etoile l'arete au poids le plus petit
						poidsPlusFaible = poidsArete;
					}
				}	
			}
		}
		int indexSommetA = distance(begin(this->coord), 
				find(begin(this->coord), end(this->coord), e_etoile.first));
		int indexSommetB = distance(begin(this->coord), 
				find(begin(this->coord), end(this->coord), e_etoile.second));
		this->A[indexSommetA][indexSommetB] = true;

		//debug
		// cout<<"e etoile ="<<e_etoile.first.first<<";"<<e_etoile.first.second
		// 		<<"->"<<e_etoile.second.first<<";"<<e_etoile.second.second<<endl;

		//si l'extremite i n'est pas comprise dans C..
		if(find(C.begin(), C.end(), e_etoile.first) == C.end())
			C.push_back(e_etoile.first);
		else
			C.push_back(e_etoile.second);

		// Retirer e etoile de omega c
		omega_C.erase(find(omega_C.begin(), omega_C.end(), e_etoile));
		
		// Ajouter toutes les aretes partant du nouveau sommet dans C
		for(int i = 0 ; i < this->n ; ++i)
			for(int j = 0 ; j < this->n ; ++j)
				if(this->coord[i] != this->coord[j] && this->coord[i] == C.back())
					omega_C.push_back(make_pair(this->coord[i], this->coord[j]));
			

		// retirer l'arete e etoile qui part du nouveau sommet dans C
		omega_C.erase(find(omega_C.begin(), omega_C.end(), make_pair(e_etoile.second, e_etoile.first)));





		// cout<<"\ndebug iteration "<<k<<endl;

		// cout<<"C = "<<endl;
		// for(pair<int,int> sommet : C)
		// 	cout<<sommet.first<<";"<<sommet.second<<endl;

		// cout<<endl;
		// cout<<"omega C ="<<endl;
		// for(pair<pair<int,int>,pair<int,int>> arete : omega_C)
		// 	cout<<arete.first.first<<";"<<arete.first.second<<"->"
		// 			<<arete.second.first<<";"<<arete.second.second<<endl;

		// cout<<"e etoile = "<<endl;
		// cout<<e_etoile.first.first<<";"<<e_etoile.first.second<<"->"
		// 			<<e_etoile.second.first<<";"<<e_etoile.second.second<<endl;

		// cout<<"A="<<endl;
		// int v, w;
		// for( v = 0 ; v < this->n ; ++v)
		// {
		// 	for(w = 0 ; w < this->n - 1 ; ++w)
		// 		cout<<this->A[v][w]<<"\t";
		// 	cout<<this->A[v][w]<<endl;
		// }
	}
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
	
	if(this->type == 1)
		this->arbrecouvrant_grapheSimple();
	else if(this->type == 2)
		this->arbrecouvrant_grapheEuclidien();
}
