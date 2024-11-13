#ifndef CLOU_H
#define CLOU_H

#include "Obstacle.h"

class Clou : public Obstacle{
    public:
        Clou(Obstacle* gauche, Obstacle* droite);
        void reçoitPalet() override;
    private:
        Obstacle* sucGauche;
        Obstacle* sucDroite;
};

#endif