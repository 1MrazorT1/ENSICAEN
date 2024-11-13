#include "../include/Clou.h"
#include <cstdlib>

Clou::Clou(Obstacle* gauche, Obstacle* droite) : sucGauche(gauche), sucDroite(droite) {}

void Clou::reçoitPalet(){
    if(rand() % 2 == 0){
        sucGauche->reçoitPalet();
    }else{
        sucDroite->reçoitPalet();
    }
}
