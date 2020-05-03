/************************************************************************/
/* Auteur : S. Gueye							*/
/* TP : Arbres couvrants de poids minimum				*/
/* Algorithmes de Prim et Kruskal					*/
/* Date dernière maj : 24/04/2020					*/
/***********************************************************************/

const int N = 500; // Constante permettant de surdimensionner les données
const int infini = 1e+5;

class graphe{
	int type; // Type du graphe lues données. 
		  // '1' il s'agit d'un graphe simple
		  // '2' il s'agit d'un graphe euclidien
	int n; 		// Nombre de noeuds du graphe
	double E[N][N]; 	// Matrice des poids des arêtes du graphe
	bool A[N][N]; 		// Matrice booléenne qui indique les arêtes choisies pour l'arbre couvrant
				// A[i][j] = true si (i,j) est choisi et false sinon
	pair<int,int> coord[N]; // Coordonnées des noeuds du graphe euclidien 
public : 
	graphe(char* filename);
	void affichage();
	void resultats();
	void arbrecouvrant();
};
