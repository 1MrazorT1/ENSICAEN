#ifndef COMPTEUR_H
#define COMPTEUR_H

#include "Obstacle.h"

class Compteur : public Obstacle{
    public:
        Compteur();
        void reçoitPalet() override;
        int getValeur() const;
        void reset();
    private:
        int compteur;
        Obstacle* suc;
};

#endif