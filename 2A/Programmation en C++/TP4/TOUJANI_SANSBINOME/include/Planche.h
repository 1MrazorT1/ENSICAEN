#ifndef PLANCHE_H
#define PLANCHE_H

#include "Compteur.h"
#include "Clou.h"
#include "Lanceur.h"

class Planche {
public:
    Planche(int nbCompteurs);
    void Planche::simuler(int nbPalets);
    ~Planche();

private:
    int nbCompteurs;
    Compteur** compteurs; 
    Obstacle* lanceur;
};

#endif
