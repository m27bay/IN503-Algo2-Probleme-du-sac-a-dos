/**
 * Partie théorique
 * */

/**
 * 3) Que peut-on dire si un algorithme remplit deux colis à moins de la moitié de
 * leur capacité ?
 * 
 * Si l'algorithme remplit deux colis à moins de la moité de leur capacité, la solution
 * sortie par l'algorithme n'est pas optimale.
 * L'algorithme doit normalement finir de remplir un colis avant de commencer un autre.
 * Ici si l'on a p1 + p2 = (1/2)P et p3 + p4 = (1/2)P, la solution optimale et donc
 * un seul colis avec p1, p2, p3, p4.
 * 
 * 4) Proposer au moins deux algorithmes gloutons qui résolvent le problème du
 * remplissage des lutins (mais pas nécessairement en donnant la solution optimale).
 * 
 * Algorithme glouton n°1 :
 * 
 * Algorithme glouton n°2 :
 * */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>    // std::find

void afficher(std::vector<std::string> tableau) {
    std::cout << "affichage du tableau {";
    for(std::string str : tableau) {
        std::cout << "( " << str << " ), ";
    }
    std::cout << "}" << std::endl;
    std::cout << "nombre de colis : " << (int)tableau.size() << std::endl;
}

void afficher(std::vector<int> tableau) {
    std::cout << "affichage du tableau {";
    for(int entier : tableau) {
        std::cout << entier << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << "nombre d'objet : " << (int)tableau.size() << std::endl;
}

void trieDecroissant(std::vector<int>& tableau) {
    for(int i=0; i<int(tableau.size()); ++i) {
        for(int j=i+1; j<int(tableau.size()); ++j)
        if(tableau[i] >= tableau[j]) {
            int tmp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = tmp;
        }
    }
}

void trieCroissant(std::vector<int>& tableau) {
    for(int i=0; i<int(tableau.size()); ++i) {
        for(int j=i+1; j<int(tableau.size()); ++j)
        if(tableau[i] <= tableau[j]) {
            int tmp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = tmp;
        }
    }
}

void remplissageSimple(std::vector<int> poidObj,
                                    std::vector<std::string>* poidColis, int poidsMAx) {
    // Initalisation
    int nombreColis = 0, sommePoids = 0;
    std::string listePoids = "\0";

    // Remplissage
    for(int poids : poidObj) {
        if(sommePoids + poids <= poidsMAx) {
            sommePoids += poids;
            listePoids += std::to_string(poids);
            listePoids += ", ";
        }
        else {
            poidColis->push_back(listePoids);
            listePoids = "\0";
            listePoids += std::to_string(poids);
            listePoids += ", ";
            sommePoids = 0;
            sommePoids += poids;
        }
    }

    if(sommePoids != 0) {
        poidColis->push_back(listePoids);
        listePoids = "\0";
        sommePoids = 0;
    }
}

void maximumObjParColis(std::vector<int> poidObj, std::vector<std::string>* poidColis, int poidsMAx) {
    trieDecroissant(poidObj);
    remplissageSimple(poidObj, poidColis, poidsMAx);
}

void opti(std::vector<int> poidObj, std::vector<std::string>* poidColis, int poidsMAx) {
    trieCroissant(poidObj);

    int taillePoidObj = (int)poidObj.size();
    std::string tmp = "\0";
    for(int i = 0; i < taillePoidObj; ++i) {
        if(poidObj[i] == -1) {
            continue;
        }
        int sommePoids = 0;
        for(int j = i + 1; j < taillePoidObj; ++j) {
            if(poidObj[j] == -1) {
                continue;
            }
            if(sommePoids == 0) {
                tmp += std::to_string(poidObj[i]);
                tmp += ", ";
                sommePoids = poidObj[i];
                poidObj[i] = -1;
            }
            if(sommePoids + poidObj[j] <= poidsMAx) {
                tmp += std::to_string(poidObj[j]);
                tmp += ", ";
                sommePoids += poidObj[j];
                poidObj[j] = -1;
            }
        }
        if(!tmp.empty()) {
            poidColis->push_back(tmp);
        }
        tmp = "\0";
        sommePoids = 0;
    }

    for(int poids : poidObj) {
        if(poids != -1) {
            tmp += std::to_string(poids);
            tmp += " ,";
        }
    }
    if(!tmp.empty()) {
        poidColis->push_back(tmp);
    }
    
}

int main(void)
{
    std::vector<int> poidObj = {2, 6, 1, 5, 8, 4, 5, 7, 5, 3};
    int P = 9;

    std::cout << "##### algo1 #####" << std::endl;
    std::vector<std::string> poidColis;
    remplissageSimple(poidObj, &poidColis, P);
    afficher(poidColis);
    std::cout << "################\n" << std::endl;

    std::cout << "##### algo2 #####" << std::endl;
    poidColis.clear();
    maximumObjParColis(poidObj, &poidColis, P);
    afficher(poidColis);
    std::cout << "################\n" << std::endl;

    std::cout << "##### opti #####" << std::endl;
    poidColis.clear();
    opti(poidObj, &poidColis, P);
    afficher(poidColis);
    std::cout << "################\n" << std::endl;
    
    return 0;
}

