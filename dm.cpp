/**
 * Partie théorique
 * */

/**
 * 1) Que peut-on toujours faire si on a deux objets de poids p1 et p2 tel que P = p1 + p2.
 * 
 * Si l'on a deux poids, p1 et p2 tel que p1 + p2 = P, peut donc toujours remplir un seul
 * colis de poids P.
 * 
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

void afficher(std::vector<std::string> tableau) {
    std::cout << "affichage du tableau {";
    for(std::string str : tableau) {
        std::cout << "( " << str << " ), ";
    }
    std::cout << "}" << std::endl;
    std::cout << "nombre de colis : " << (int)tableau.size() << std::endl;
}

void glouton1(std::vector<int> poidObj, std::vector<std::string>* poidColis, int poidsMAx) {
    // Initalisation
    int nombreColis = 0, sommePoids = 0;
    std::string allPoids = "\0";

    // Remplissage
    for(int poids : poidObj) {
        if(sommePoids + poids <= poidsMAx) {
            sommePoids += poids;
            allPoids += std::to_string(poids);
            allPoids += ", ";
        }
        else {
            poidColis->push_back(allPoids);
            allPoids = "\0";
            allPoids += std::to_string(poids);
            allPoids += ", ";
            sommePoids = 0;
            sommePoids += poids;
        }
    }

    if(sommePoids != 0) {
        poidColis->push_back(allPoids);
        allPoids = "\0";
        sommePoids = 0;
    }
}

void glouton2(std::vector<int> poidObj, std::vector<std::string>* poidColis, int poidsMAx) {
    // Sort
    for(int i=0; i<int(poidObj.size()); ++i) {
        for(int j=i+1; j<int(poidObj.size()); ++j)
        if(poidObj[i] >= poidObj[j]) {
            int tmp = poidObj[i];
            poidObj[i] = poidObj[j];
            poidObj[j] = tmp;
        }
    }

    // Initalisation
    int nombreColis = 0, sommePoids = 0;
    std::string allPoids = "\0";

    // Remplissage
    for(int poids : poidObj) {
        if(sommePoids + poids <= poidsMAx) {
            sommePoids += poids;
            allPoids += std::to_string(poids);
            allPoids += ", ";
        }
        else {
            poidColis->push_back(allPoids);
            allPoids = "\0";
            allPoids += std::to_string(poids);
            allPoids += ", ";
            sommePoids = 0;
            sommePoids += poids;
        }
    }

    if(sommePoids != 0) {
        poidColis->push_back(allPoids);
        allPoids = "\0";
        sommePoids = 0;
    }
}

void opti(std::vector<int> poidObj, std::vector<std::string>* poidColis, int poidsMAx) {
    
}

int main(void)
{
    std::vector<int> poidObj = {1, 4, 1, 6, 7, 9, 3, 2, 8};

    std::cout << "##### algo1 #####" << std::endl;
    std::vector<std::string> poidColis;
    glouton1(poidObj, &poidColis, 10);
    afficher(poidColis);
    std::cout << "##########\n" << std::endl;

    std::cout << "##### algo2 #####" << std::endl;
    poidColis.clear();
    glouton2(poidObj, &poidColis, 10);
    afficher(poidColis);
    std::cout << "##########\n" << std::endl;
    
    return 0;
}

