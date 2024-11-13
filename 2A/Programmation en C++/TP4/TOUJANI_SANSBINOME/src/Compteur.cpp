#include "../include/Compteur.h"

Compteur::Compteur() : compteur(0), suc(nullptr) {}

void Compteur::reçoitPalet(){
    compteur++;
    if(suc){
        suc->reçoitPalet();
    }
}

int Compteur::getValeur() const{
    return compteur;
}

void Compteur::reset(){
    compteur = 0;
}