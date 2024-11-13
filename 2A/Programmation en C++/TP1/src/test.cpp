#include "Book.cpp"
#include <iostream>
#include <limits>
#include <vector>

int main(){
    /*int nbr = lireNombre();
    std::cout << "Nombre de pages = " << nbr << std::endl;
    lireNombre(&nbr);
    std::cout << "Nombre de pages apres modification par adresse = " << nbr << std::endl;
    //lireNombre(nbr);
    //std::cout << "Nombre de pages apres modification par valeur= " << nbr << std::endl;
    lireNombre(nbr);
    std::cout << "Nombre de pages apres modification par reference = " << nbr << std::endl;
    Book livre;
    livre = lireLivre();
    afficherLivre(livre);
    */
    /*int taille = 5;
    std::vector<Book> tab(taille);
    lireMultiLivres(tab, taille);
    afficherMultiLivres(tab, taille);
    */
    Book l1, l2;
    l1.nbpages = 1;
    l2.nbpages = 2;
    afficherLivre(l1);
    afficherLivre(l2);
    std::cout << "apres echange :" << std::endl;
    echangeNbrPages(&l1, &l2);
    afficherLivre(l1);
    afficherLivre(l2);
    



    
    
    
    
    return 0;
}