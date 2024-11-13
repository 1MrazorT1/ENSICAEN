#include "../include/Planche.h"
#include <iostream>

Planche::Planche(int nbCompteurs) : nbCompteurs(nbCompteurs) {
    compteurs = new Compteur*[nbCompteurs];

    Obstacle* compteurTerminal = new Compteur();

    for (int i = 0; i < nbCompteurs; ++i) {
        compteurs[i] = new Compteur();
        compteurs[i]->setSuccesseur(compteurTerminal);
    }

    Obstacle** rangPrecedent = (Obstacle**)compteurs;
    int nbObstacles = nbCompteurs;

    for (int k = nbCompteurs - 1; k > 0; --k) {
        Obstacle** nouveauRang = new Obstacle*[nbObstacles - 1];

        for (int i = 0; i < nbObstacles - 1; ++i) {
            nouveauRang[i] = new Clou(rangPrecedent[i], rangPrecedent[i + 1]);
        }

        rangPrecedent = nouveauRang;
        nbObstacles--;
    }

    lanceur = rangPrecedent[0];
}

Planche::~Planche() {
    for (int i = 0; i < nbCompteurs; ++i) {
        delete compteurs[i];
    }
    delete[] compteurs;
}

void Planche::simuler(int nbPalets) {
    for (int i = 0; i < nbPalets; ++i) {
        /*lanceur->lancer();*/ 
    }

    int c0 = compteurs[0]->getValeur(); 

    if (c0 == 0) {
        std::cerr << "Erreur : le compteur c0 est nul, impossible de calculer les ratios." << std::endl;
        return;
    }

    for (int i = 0; i < nbCompteurs; ++i) {
        int ci = compteurs[i]->getValeur();
        double ratio = static_cast<double>(ci) / c0; 
        std::cout << "Ratio c" << i << " / c0 : " << std::round(ratio) << std::endl;
    }
}
