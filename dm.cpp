#include <iostream>
#include <cstdlib>
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
        for(int j=i+1; j<int(tableau.size()); ++j) {
            if(tableau[i] >= tableau[j]) {
                int tmp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = tmp;
            }
        }
    }
}

void trieCroissant(std::vector<int>& tableau, int poidsMax) {
    for(int i=0; i<int(tableau.size()); ++i) {
        for(int j=i+1; j<int(tableau.size()); ++j) {
            double rapport = tableau[i]/poidsMax;
            double rapport2 = tableau[j]/poidsMax;
            if(rapport >= rapport2) {
                int tmp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = tmp;
            }
        }
    }
}

void trieDecroissant(std::vector<int>& tableau) {
    for(int i=0; i<int(tableau.size()); ++i) {
        for(int j=i+1; j<int(tableau.size()); ++j) {
            if(tableau[i] <= tableau[j]) {
                int tmp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = tmp;
            }
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

void maximumObjParColis(std::vector<int> poidsObj, std::vector<std::string>* poidsColis,
                                                                        int poidsMax) {
    trieCroissant(poidsObj);
    remplissageSimple(poidsObj, poidsColis, poidsMax);
}

void maximumRapportParColis(std::vector<int> poidsObj, std::vector<std::string>* poidsColis,
                                                                        int poidsMax) {
    trieCroissant(poidsObj, poidsMax);
    remplissageSimple(poidsObj, poidsColis, poidsMax);
}

void remplissageOptimise(std::vector<int> poidsObj, std::vector<std::string>* poidsColis, int poidsMax) {
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

void genereTableauAleatoire(std::vector<int>* poidsObj, int nombreObj,
                                                        int poidsMinObj, int poidsMaxObj) {
    for(int i=0; i<nombreObj; ++i) {
        poidsObj->push_back(rand()%poidsMaxObj + poidsMinObj);
    }
}

double moyenneRemplissageSimple(int nombreEntree, int nombreObj, int poidsMinObj,
                                                int poidsMaxObj, int poidsMaxColis) {
    double sommeNombreColis = 0;
    for(int repetition=0; repetition<nombreEntree; ++repetition) {
        std::vector<int> poidsObj;
        std::vector<std::string> poidsColis;

        genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        remplissageSimple(poidsObj, &poidsColis, poidsMaxColis);
        sommeNombreColis += (int)poidsColis.size();

        poidsObj.clear();
        poidsColis.clear();
    }

    return sommeNombreColis/nombreEntree;
}

double moyenneMaximumObjParColis(int nombreEntree, int nombreObj, int poidsMinObj,
                                                int poidsMaxObj, int poidsMaxColis) {
    double sommeNombreColis = 0;
    for(int repetition=0; repetition<nombreEntree; ++repetition) {
        std::vector<int> poidsObj;
        std::vector<std::string> poidsColis;

        genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        maximumObjParColis(poidsObj, &poidsColis, poidsMaxColis);
        sommeNombreColis += (int)poidsColis.size();

        poidsObj.clear();
        poidsColis.clear();
    }

    return sommeNombreColis/nombreEntree;
}

double moyenneMaximumRapportParColis(int nombreEntree, int nombreObj, int poidsMinObj,
                                                int poidsMaxObj, int poidsMaxColis) {
    double sommeNombreColis = 0;
    for(int repetition=0; repetition<nombreEntree; ++repetition) {
        std::vector<int> poidsObj;
        std::vector<std::string> poidsColis;

        genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        maximumRapportParColis(poidsObj, &poidsColis, poidsMaxColis);
        sommeNombreColis += (int)poidsColis.size();

        poidsObj.clear();
        poidsColis.clear();
    }

    return sommeNombreColis/nombreEntree;
}

double moyenneRemplissageOptimise(int nombreEntree, int nombreObj, int poidsMinObj,
                                                int poidsMaxObj, int poidsMaxColis) {
    double sommeNombreColis = 0;
    for(int repetition=0; repetition<nombreEntree; ++repetition) {
        std::vector<int> poidsObj;
        std::vector<std::string> poidsColis;

        genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        remplissageOptimise(poidsObj, &poidsColis, poidsMaxColis);
        sommeNombreColis += (int)poidsColis.size();

        poidsObj.clear();
        poidsColis.clear();
    }

    return sommeNombreColis/nombreEntree;
}

void moyenne(int nombreEntree, int nombreObj, int poidsMinObj,
                                                int poidsMaxObj, int poidsMaxColis) {
    double moyenne1 = moyenneRemplissageSimple(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);
    double moyenne2 = moyenneMaximumObjParColis(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);
    double moyenne3 = moyenneMaximumRapportParColis(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);
    double moyenne4 = moyenneRemplissageOptimise(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);

    std::cout << "Moyenne via remplissage simple " << moyenne1 << " / " << nombreObj << std::endl;
    std::cout << "Moyenne via maximum objet par colis " << moyenne2 << " / " << nombreObj << std::endl;
    std::cout << "Moyenne via maximum rapport par colis " << moyenne3 << " / " << nombreObj << std::endl;
    std::cout << "Moyenne via remplissage optimise " << moyenne4 << " / " << nombreObj << std::endl;
}

int main(void)
{
    std::cout << "\033[1;31m##### Test generation nombre aleatoire #####\033[0m" << std::endl;
    std::vector<int> poidsObj;
    int nombreObj = 10, poidsMaxObj = 9, poidsMinObj = 1;
    genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
    afficher(poidsObj);

    poidsObj.clear();
    poidsObj = {2,6,1,5,8,4,5,7,5,3};
    int P = 9;

    std::cout << "\n\033[1;31m##### remplissage simple #####\033[0m" << std::endl;
    std::vector<std::string> poidsColis;
    remplissageSimple(poidsObj, &poidsColis, P);
    afficher(poidsColis);

    std::cout << "\n\033[1;31m##### maximum objet par colis #####\033[0m" << std::endl;
    poidsColis.clear();
    maximumObjParColis(poidsObj, &poidsColis, P);
    afficher(poidsColis);

    std::cout << "\n\033[1;31m##### maximum rapport poidsObj/poidsMax par colis #####\033[0m" << std::endl;
    poidsColis.clear();
    maximumRapportParColis(poidsObj, &poidsColis, P);
    afficher(poidsColis);
   
    std::cout << "\n\033[1;31m##### remplissage optimise #####\033[0m" << std::endl;
    poidsColis.clear();
    remplissageOptimise(poidsObj, &poidsColis, P);
    afficher(poidsColis);
    
    std::cout << "\n\033[1;31m####### Moyenne ######" << std::endl;
    srand(time(NULL));
    std::cout << "\033[1;34m##### Test n°1 : #####\n\033[0m> 1000 entrees <\n> 100 objets <" << std::endl;
    std::cout << "> poids obj entre 1 et 10 <\n> poids colis 10 <\n" << std::endl;
    moyenne(1000, 100, 1, 10, 10);
    std::cout << "\033[1;34m\n##### Test n°2 : #####\n\033[0m> 1000 entrees <\n> 100 objets <" << std::endl;
    std::cout << "> poids obj entre 1 et 1000 <\n> poids colis 1000 <\n" << std::endl;
    moyenne(1000, 100, 1, 1000, 1000);
    std::cout << "\033[1;34m\n##### Test n°3 : #####\n\033[0m> 1000 entrees <\n> 100 objets <" << std::endl;
    std::cout << "> poids obj entre 1 et 10000 <\n> poids colis 10000 <\n" << std::endl;
    moyenne(1000, 100, 1, 10000, 10000);
    
    return 0;
}

