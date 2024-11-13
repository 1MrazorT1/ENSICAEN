#include "Book.cpp"
#include <iostream>
#include <limits>
#include <vector>

int main(){
    int taille = 5;
    std::vector<Book> tab(taille);
    lireMultiLivres(tab, taille);
    std::cout << "Avant :" << std::endl;
    afficherMultiLivres(tab, taille);
    echangeNbrPages(&LivrePlusCourt(tab, taille), &LivrePlusLong(tab, taille));
    std::cout << "apres :" << std::endl;
    afficherMultiLivres(tab, taille);
    /*Blague BIS :
    Book& livrePlusCourt = LivrePlusCourt(tab, taille);
    Book& livrePlusLong = LivrePlusLong(tab, taille);
    echangeNbrPages(&livrePlusCourt, &livrePlusLong);
    afficherMultiLivres(tab, taille);
    */

    /*Test de partie 3 :
    echangeNbrPages(lireLivre(), lireLivre());
    */
}