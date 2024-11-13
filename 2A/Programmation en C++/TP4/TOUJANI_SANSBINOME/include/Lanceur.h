#ifndef LANCEUR_H
#define LANCEUR_H

#include "Obstacle.h"

class Lanceur{
public:
    Lanceur(Obstacle* premierObstable);
    void lancer() const;
private:
    Obstacle* premierObstacle;
};

#endif