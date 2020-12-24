/**
 * Ce fichier comporte toutes les fonctions programmees, et utilisees pour le devoir d'algorithme.
 * @author Mickael LE DENMAT 21804355
 * */

#include <iostream>
#include <cstdlib>
#include <fstream> // Pour ecrire dans un fichier

#include <vector>
#include <string>

#include <random>
#include <chrono> // Pour chrono::system_clock
#include <functional> // Pour bind

#define SORTIE "sortie.txt"

/**
 * *Description : Affiche les elements du tableau 2D en parametre.
 * @param tableau, un tableau 2D d'entier.
 * */
void afficher(std::vector<std::vector<int>> tableau) {
    std::cout << "Affichage du tableau (";
    for(std::vector<int> sousTableau : tableau) {
        std::cout << "(";
        for(int element : sousTableau) {
            std::cout << element << ", ";
        }
        std::cout << "), ";
    }
    std::cout << ")." << std::endl;
    std::cout << "Nombre de colis : " << (int)tableau.size() << std::endl;
}

/**
 * *Description : Affiche les elements du tableau 1D en parametre.
 * @param tableau, un tableau 1D d'entier.
 * */
void afficher(std::vector<int> tableau) {
    std::cout << "Affichage du tableau (";
    for(int entier : tableau) {
        std::cout << entier << ", ";
    }
    std::cout << ")." << std::endl;
    std::cout << "Nombre d'objet : " << (int)tableau.size() << std::endl;
}

/**
 * *Description : Ecrit dans un fichier le tableau 2D en parametre.
 * @param nomFichier, le nom fichier ou l on ecrit.
 * @param tableau, un tableau 2D d'entier.
 * */
void ecrireTableauDansFichier(std::string nomFichier, std::vector<std::vector<int>> tableau) {
    std::ofstream flux;
    flux.open(nomFichier, std::ios::out | std::ios::app);
    if(flux) {
        flux << "Affichage du tableau (";
        for(std::vector<int> sousTableau : tableau) {
            flux << "(";
            for(int element : sousTableau) {
                flux << element << ", ";
            }
            flux << "), ";
        }
        flux << ").";
        flux << "Nombre de colis : " << (int)tableau.size() << "\n";
    }
    else {
        std::cout << "ERREUR : impossible d'ouvrir le fichier." << std::endl;
    }
}

/**
 * *Desciption : Vide le fichier en parametre.
 * @param nomFichier, le nom du fichier a vider.
 * */
void nettoyerFichier(std::string nomFichier) {
    std::ofstream flux;
    flux.open(nomFichier, std::ios::out | std::ios::trunc);
    if(flux) {
        flux << "";
    }
    else {
        std::cout << "ERREUR : impossible d'ouvrir le fichier." << std::endl;
    }
}

/**
 * *Description : Echange la valeur des deux entiers.
 * @param a, la première valeur.
 * @param b, la deuxième valeur.
 * */
void echange(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

/**
 * *Description : Echange les valeurs du tableau entre le debut et la fin
 * *                afin de la trié par ordre croissant.
 * @param tableau, le tableau a trie.
 * @param deb, le debut du sous tableau.
 * @param fin, la fin du sous tableau.
 * */
int partition(std::vector<int>& tableau, int deb, int fin) {
    int pivot = tableau[fin];
    int i = (deb - 1);
    for(int j=deb; j<fin; ++j) {
        if(tableau[j] < pivot) {
            i++;
            echange(tableau[i], tableau[j]);
        }
    }
    echange(tableau[i+1], tableau[fin]);

    return i+1;
}


/**
 * *Description : Algorithme quick sort qui permet de trier les elements du tableau entre le debut
 * *                et la fin.
 * @param tableau, le tableau a trie.
 * @param deb, le debut du sous tableau.
 * @param fin, la fin du sous tableau.
 * */
void quickSort(std::vector<int>& tableau, int deb, int fin) {
    if(deb < fin) {
        int positionPartition = partition(tableau, deb, fin);
        quickSort(tableau, deb, positionPartition - 1);
        quickSort(tableau, positionPartition + 1, fin);
    }
}

/**
 * *Description : Permet de retourner le tableau en parametre.
 * @param tableau, le tableau a retourner.
 * */
void retourner(std::vector<int>& tableau) {
    int tailleTableau = (int)tableau.size();
    for(int i=0; i<tailleTableau/2; ++i) {
        echange(tableau[i], tableau[tailleTableau - 1 -i]);
    }
}

/**
 * *Description : Applique l'algorithme de quick sort pour trier le tableau dans l ordre croissant.
 * @param tableau, le tableau a trier.
 * */
void trieCroissant(std::vector<int>& tableau) {
    quickSort(tableau, 0, (int)tableau.size() - 1);
}

/**
 * *Description : Applique l'algorithme de quick sort pour trier le tableau dans l ordre decroissant.
 * @param tableau, le tableau a trier.
 * */
void trieDecroissant(std::vector<int>& tableau) {
    quickSort(tableau, 0, (int)tableau.size() - 1);
    retourner(tableau);
}

/**
 * *Description : Applique l'algorithme de trie par insertion pour trier le tableau en fonction du
 * *                rapport entre l element i du tableau et le poidsMax dans l ordre croissant.
 * @param tableau, le tableau a trier.
 * @retur
 * */
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

/**
 * *Description : Permet de remplir le tableau 2D d entier poidsColis, avec les poids stocke dans le
 * *                tableau poidsObj en ne depassant pas le poidsMax par colis.
 * @param poidsObj, le tableau d entier ou son stocke les poids.
 * @param poidsColis, le tableau 2D d entier ou l on stocke chaque colis ainsi
 *                      que les poids qui les composes.
 * @param poidsMax, le poids maximal d un colis.
 * */
void remplissageSimple(std::vector<int> poidsObj, std::vector<std::vector<int>>* poidsColis, int poidsMax) {
    // Initalisation
    int nombreColis = 0, sommePoids = 0;
    std::vector<int> listePoids;

    // Remplissage
    for(int poids : poidsObj) {
        if(poids > poidsMax) {
            std::cout << "ERREUR : le poids ne peut pas être mis dans un colis.";
            return;
        }
        // Ajout du poids le le colis courant.
        if(sommePoids + poids <= poidsMax) {
            sommePoids += poids;
            listePoids.push_back(poids);
        }
        else { // Ajout du poids dans un autre colis.
            poidsColis->push_back(listePoids);
            listePoids.clear();
            listePoids.push_back(poids);
            sommePoids = 0;
            sommePoids += poids;
        }
    }

    // Si certains poids ne sont dans aucun colis.
    if(sommePoids != 0) {
        poidsColis->push_back(listePoids);
        listePoids.clear();
        sommePoids = 0;
    }
}

/**
 * *Description : Remplis les colis en mettant le maximum d'objet par colis.
 * @param poidsObj, le tableau des poids.
 * @param poidsCOlis, le tableau des colis.
 * @param poidsMax, le poids maximal d un colis.
 * */
void maximumObjParColis(std::vector<int> poidsObj,
                                std::vector<std::vector<int>>* poidsColis, int poidsMax) {
    trieCroissant(poidsObj);
    remplissageSimple(poidsObj, poidsColis, poidsMax);
}

/**
 * *Description : Remplis les colis en mettant optimisant le rapport entre le poids des objets et
 * *                le poidsMax par colis.
 * @param poidsObj, le tableau des poids.
 * @param poidsCOlis, le tableau des colis.
 * @param poidsMax, le poids maximal d un colis.
 * */
void maximumRapportParColis(std::vector<int> poidsObj,
                                std::vector<std::vector<int>>* poidsColis, int poidsMax) {
    trieCroissant(poidsObj, poidsMax);
    remplissageSimple(poidsObj, poidsColis, poidsMax);
}

/**
 * *Description : Remplis les colis de mettant un poids et en trouvant son plus grand complementaire
 * *                tel que poidsMax = p1 + p2.
 * @param poidsObj, le tableau des poids.
 * @param poidsCOlis, le tableau des colis.
 * @param poidsMax, le poids maximal d un colis.
 * */
void remplissageOptimise(std::vector<int> poidsObj,
                                std::vector<std::vector<int>>* poidsColis, int poidsMax) {
    trieDecroissant(poidsObj);
    if(poidsObj[0] > poidsMax) {
        std::cout << "ERREUR : le poids ne peut pas être mis dans un colis.";
        return;
    }

    int tailleTableauObj = (int)poidsObj.size();
    std::vector<int> listePoids;
    for(int i = 0; i < tailleTableauObj; ++i) {
        if(poidsObj[i] == -1) { // Si on a déjà mis le poids dans un colis.
            continue;
        }
        int sommePoids = 0;
        for(int j = i + 1; j < tailleTableauObj; ++j) {
            if(poidsObj[j] == -1) { // Si on a déjà mis le poids dans un colis.
                continue;
            }
            if(sommePoids == 0) { // Si le colis est vide.
                listePoids.push_back(poidsObj[i]);
                sommePoids = poidsObj[i];
                poidsObj[i] = -1;
            }
            if(sommePoids + poidsObj[j] <= poidsMax) {
                listePoids.push_back(poidsObj[j]);
                sommePoids += poidsObj[j];
                poidsObj[j] = -1;
            }
        }
        if(!listePoids.empty()) { // Si il reste des poids en dehors des colis.
            poidsColis->push_back(listePoids);
        }
        listePoids.clear();
        sommePoids = 0;
    }

    for(int poids : poidsObj) { // Si on n a pas vu des poids.
        if(poids != -1) {
            listePoids.push_back(poids);
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

void genereTableauAleatoire2(std::vector<int>* poidsObj, int nombreObj,
                                                        int poidsMinObj, int poidsMaxObj) {
    
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(poidsMinObj, poidsMaxObj);
    auto rd = bind(distrib, re);
    for(int i=0; i<nombreObj; ++i) {
        poidsObj->push_back(rd());
    }
}

double moyenneRemplissageSimple(int nombreEntree, int nombreObj, int poidsMinObj,
                                                int poidsMaxObj, int poidsMaxColis) {
    double sommeNombreColis = 0;

    for(int repetition=0; repetition<nombreEntree; ++repetition) {
        std::vector<int> poidsObj;
        std::vector<std::vector<int>> poidsColis;

        // genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        genereTableauAleatoire2(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
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
        std::vector<std::vector<int>> poidsColis;

        // genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        genereTableauAleatoire2(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
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
        std::vector<std::vector<int>> poidsColis;

        // genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        genereTableauAleatoire2(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
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
    nettoyerFichier(SORTIE);

    for(int repetition=0; repetition<nombreEntree; ++repetition) {
        std::vector<int> poidsObj;
        std::vector<std::vector<int>> poidsColis;

        // genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        genereTableauAleatoire2(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
        remplissageOptimise(poidsObj, &poidsColis, poidsMaxColis);
        ecrireTableauDansFichier(SORTIE, poidsColis);
        sommeNombreColis += (int)poidsColis.size();

        poidsObj.clear();
        poidsColis.clear();
    }

    return sommeNombreColis/nombreEntree;
}

void calculMoyenneToutAlgo(int nombreEntree, int nombreObj, int poidsMinObj,
                                                int poidsMaxObj, int poidsMaxColis) {
    double moyenneSimple = moyenneRemplissageSimple(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);
    double moyenneMaxObj = moyenneMaximumObjParColis(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);
    double moyenneMaxRapport = moyenneMaximumRapportParColis(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);
    double moyenneOpti = moyenneRemplissageOptimise(nombreEntree, nombreObj, poidsMinObj,
                                                                        poidsMaxObj, poidsMaxColis);

    std::cout << "Remplissage simple : " << moyenneSimple << " colis." << std::endl;
    std::cout << "Maximum objet par colis : " << moyenneMaxObj << " colis." << std::endl;
    std::cout << "Maximum rapport par colis : " << moyenneMaxRapport << " colis." << std::endl;
    std::cout << "Remplissage optimise : " << moyenneOpti << " colis.\n" << std::endl;

    std::cout << "\033[1;32mDifference avec l'optimale : \033[0m" << std::endl;
    std::cout << "Remplissage simple : ";
    std::cout << (moyenneSimple - moyenneOpti) << " colis" << std::endl;
    std::cout << "Maximum objet par colis : ";
    std::cout << (moyenneMaxObj - moyenneOpti) << " colis" << std::endl;
    std::cout << "Maximum rapport par colis : ";
    std::cout << (moyenneMaxRapport - moyenneOpti) << " colis\n" << std::endl;
}

void testGenerationNombreAleatoire() {
    std::cout << "\033[1;31m##### Test generation nombre aleatoire #####\033[0m" << std::endl;
    std::vector<int> poidsObj;
    int nombreObj = 10, poidsMaxObj = 9, poidsMinObj = 1;
    genereTableauAleatoire(&poidsObj, nombreObj, poidsMinObj, poidsMaxObj);
    afficher(poidsObj);
}

void testRemplissageSimple() {
    std::vector<int> poidsObj;
    std::vector<std::vector<int>> poidsColis;
    poidsObj = {2,6,1,5,8,4,5,7,5,3};
    int P = 9;

    std::cout << "\n\033[1;31m##### remplissage simple #####\033[0m" << std::endl;
    remplissageSimple(poidsObj, &poidsColis, P);
    afficher(poidsColis);
}

void testMaximumObjParColis() {
    std::vector<int> poidsObj;
    std::vector<std::vector<int>> poidsColis;
    poidsObj = {2,6,1,5,8,4,5,7,5,3};
    int P = 9;

    std::cout << "\n\033[1;31m##### maximum objet par colis #####\033[0m" << std::endl;
    maximumObjParColis(poidsObj, &poidsColis, P);
    afficher(poidsColis);
}

void testMaximumRapportParColis() {
    std::vector<int> poidsObj;
    std::vector<std::vector<int>> poidsColis;
    poidsObj = {2,6,1,5,8,4,5,7,5,3};
    int P = 9;

    std::cout << "\n\033[1;31m##### maximum rapport poidsObj/poidsMax par colis #####\033[0m" << std::endl;
    maximumRapportParColis(poidsObj, &poidsColis, P);
    afficher(poidsColis);
}

void testReplissageOptimise() {
    std::vector<int> poidsObj;
    std::vector<std::vector<int>> poidsColis;
    poidsObj = {2,6,1,5,8,4,5,7,5,3};
    int P = 9;

    std::cout << "\n\033[1;31m##### remplissage optimise #####\033[0m" << std::endl;
    remplissageOptimise(poidsObj, &poidsColis, P);
    afficher(poidsColis);
}

void testMoyenne(int numeroTest, int nombreEntree, int nombreObj, int poidsObjMin, 
                                int poidsObjMax, int poidsColis) {
    
    std::cout << "\033[1;34m##### Test n° " << numeroTest << "  : #####\033[0m\n";
    std::cout << "> " << nombreEntree << " entrees <\n> " << nombreObj << " objets <" << std::endl;
    std::cout << "> poids obj entre " << poidsObjMin << " et " << poidsObjMax << " <\n";
    std::cout << "> poids colis " << poidsColis << " <\n" << std::endl;
    calculMoyenneToutAlgo(nombreEntree, nombreObj, poidsObjMin, poidsObjMax, poidsColis);
}

void calculMoyenne() {
    srand(time(NULL));
    std::cout << "\n\033[1;31m####### Moyenne ######" << std::endl;
    testMoyenne(1, 1000, 100, 1, 10, 10);
    testMoyenne(2, 1000, 100, 1, 100, 100);
    testMoyenne(3, 1000, 100, 1, 1000, 1000);
    testMoyenne(4, 1000, 100, 1, 10000, 10000);
}

int main(void)
{
    testGenerationNombreAleatoire();
    testRemplissageSimple();
    testMaximumObjParColis();
    testMaximumRapportParColis();
    testReplissageOptimise();
   
    calculMoyenne();
    
    return 0;
}

