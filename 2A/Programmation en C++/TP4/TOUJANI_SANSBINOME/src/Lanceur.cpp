#include "Lanceur.h"

Lanceur::Lanceur(Obstacle* premierObstacle) : premierObstacle(premierObstacle) {}

void Lanceur::lancer() const {
    if (premierObstacle != nullptr) {
        premierObstacle->reçoitPalet(); 
    }
}
