#include <iostream>

using namespace std;

#include "arbres.h"

int main(int argc,char** argv)
{
	if(argc < 2)
		cout << "Nombre d'arguments insuffisants" << endl;
	else{
		graphe obj(argv[1]);
		obj.affichage();
		obj.arbrecouvrant();
		// obj.resultats();
	}

	return(1);
}
