#include <iostream>
#include <vector>
#include <string>
#include <algorithm>    // std::find

void afficher(std::vector<std::string> tableau) {
    std::cout << "Affichage du tableau (";
    for(std::string str : tableau) {
        std::cout << "( " << str << " ), ";
    }
    std::cout << ")." << std::endl;
    std::cout << "Nombre de colis : " << (int)tableau.size() << std::endl;
}

void afficher(std::vector<int> tableau) {
    std::cout << "Affichage du tableau (";
    for(int entier : tableau) {
        std::cout << entier << ", ";
    }
    std::cout << ")." << std::endl;
    std::cout << "Nombre d'objet : " << (int)tableau.size() << std::endl;
}

void trieCroissant(std::vector<int>& tableau) {
    for(int i=0; i<int(tableau.size()); ++i) {
        for(int j=i+1; j<int(tableau.size()); ++j)
        if(tableau[i] >= tableau[j]) {
            int tmp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = tmp;
        }
    }
}

void trieDecroissant(std::vector<int>& tableau) {
    for(int i=0; i<int(tableau.size()); ++i) {
        for(int j=i+1; j<int(tableau.size()); ++j)
        if(tableau[i] <= tableau[j]) {
            int tmp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = tmp;
        }
    }
}

void remplissageSimple(std::vector<int> poidsObj, std::vector<std::string>* poidsColis, int poidsMax) {
    // Initalisation
    int nombreColis = 0, sommePoids = 0;
    std::string listePoids = "\0";

    // Remplissage
    for(int poids : poidsObj) {
        if(poids > poidsMax) {
            std::cout << "ERREUR : le poids ne peut pas être mis dans un colis.";
            return;
        }
        if(sommePoids + poids <= poidsMax) {
            sommePoids += poids;
            listePoids += std::to_string(poids);
            listePoids += ", ";
        }
        else {
            poidsColis->push_back(listePoids);
            listePoids = "\0";
            listePoids += std::to_string(poids);
            listePoids += ", ";
            sommePoids = 0;
            sommePoids += poids;
        }
    }

    if(sommePoids != 0) {
        poidsColis->push_back(listePoids);
        listePoids = "\0";
        sommePoids = 0;
    }
}

void maximumObjParColis(std::vector<int> poidsObj, std::vector<std::string>* poidsColis, int poidsMax) {
    trieCroissant(poidsObj);
    remplissageSimple(poidsObj, poidsColis, poidsMax);
}

void opti(std::vector<int> poidsObj, std::vector<std::string>* poidsColis, int poidsMax) {
    trieDecroissant(poidsObj);

    int tailleTableauObj = (int)poidsObj.size();
    std::string listePoids = "\0";
    for(int i = 0; i < tailleTableauObj; ++i) {
        if(poidsObj[i] > poidsMax) {
            std::cout << "ERREUR : le poids ne peut pas être mis dans un colis.";
            return;
        }
        if(poidsObj[i] == -1) {
            continue;
        }
        int sommePoids = 0;
        for(int j = i + 1; j < tailleTableauObj; ++j) {
            if(poidsObj[j] == -1) {
                continue;
            }
            if(sommePoids == 0) {
                listePoids += std::to_string(poidsObj[i]);
                listePoids += ", ";
                sommePoids = poidsObj[i];
                poidsObj[i] = -1;
            }
            if(sommePoids + poidsObj[j] <= poidsMax) {
                listePoids += std::to_string(poidsObj[j]);
                listePoids += ", ";
                sommePoids += poidsObj[j];
                poidsObj[j] = -1;
            }
        }
        if(!listePoids.empty()) {
            poidsColis->push_back(listePoids);
        }
        listePoids = "\0";
        sommePoids = 0;
    }

    for(int poids : poidsObj) {
        if(poids != -1) {
            listePoids += std::to_string(poids);
            listePoids += " ,";
        }
    }
    if(!listePoids.empty()) {
        poidsColis->push_back(listePoids);
    }
    
}

int main(void)
{
    std::vector<int> poidsObj = {2,6,1,5,8,4,5,7,5,3};
    int P = 9;
    // std::vector<int> poidsObj = { 20,  19,  18,  18,  17,  17,  15,  15,  14,  12,  11,  11,  10,  10,  10,  9,  7,  7,  6,  4, };
    // int P = 30;

    std::cout << "##### algo1 #####" << std::endl;
    std::vector<std::string> poidsColis;
    remplissageSimple(poidsObj, &poidsColis, P);
    afficher(poidsColis);
    std::cout << "################\n" << std::endl;

    std::cout << "##### algo2 #####" << std::endl;
    poidsColis.clear();
    maximumObjParColis(poidsObj, &poidsColis, P);
    afficher(poidsColis);
    std::cout << "################\n" << std::endl;

    std::cout << "##### opti #####" << std::endl;
    poidsColis.clear();
    opti(poidsObj, &poidsColis, P);
    afficher(poidsColis);
    std::cout << "################\n" << std::endl;
    
    return 0;
}

