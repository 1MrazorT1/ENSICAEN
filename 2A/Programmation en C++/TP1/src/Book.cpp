#include "../include/Book.h"
#include <iostream>
#include <vector>

int lireNombre(){
    int n;
    do{
        std::cout << "Entrez un nombre entre 2 et 2000: ";
        std::cin >> n;
    } while (n < 2 || n > 2000);
    return n;
}

void lireNombre(int* n){
    do{
        std::cout << "Entrez un nombre entre 2 et 2000: ";
        std::cin >> *n;
    } while (*n < 2 || *n > 2000);
}

/*L'intrus :
void lireNombre(int n){
    do{
        std::cout << "Entrez un nombre entre 2 et 2000: ";
        std::cin >> n;
    } while (n < 2 || n > 2000);
}*/

void lireNombre(int& n){
    do{
        std::cout << "Entrez un nombre entre 2 et 2000: ";
        std::cin >> n;
    } while (n < 2 || n > 2000);
}

Book lireLivre(){
    Book livre;
    livre.nbpages = lireNombre();
    std::cout << "Entrez le titre du livre: ";
    std::cin >> livre.titre;
    return livre;
}

void lireMultiLivres(std::vector<Book>& tab, int taille) {
    for (int i = 0; i < taille; i++) {
        std::cout << "Livre " << (i + 1) << "/" << taille << " :" << std::endl;
        tab[i] = lireLivre(); 
    }
}

void afficherLivre(Book livre){
    std::cout << "Le titre de ce livre est " << livre.titre << " et son nombre de pages est " << livre.nbpages << "." << std::endl;
}

void afficherMultiLivres(std::vector<Book> tab, int taille){
    for(int i=0; i < taille; i++){
        afficherLivre(tab[i]);
    }
}

void echangeNbrPages(Book *l1, Book *l2){
    int temp = l1->nbpages;
    l1->nbpages = l2->nbpages;
    l2->nbpages = temp;
}

Book& LivrePlusLong(std::vector<Book>& tab, int taille){
    int max = tab[0].nbpages;
    int k = -1;
    for(int i=0; i<taille; i++){
        if(max < tab[i].nbpages){
            max = tab[i].nbpages;
            k = i;
        }
    }
    return(tab[k]);
}

Book& LivrePlusCourt(std::vector<Book>& tab, int taille){
    int min = tab[0].nbpages;
    int k = 0;
    for(int i=0; i<taille; i++){
        if(min > tab[i].nbpages){
            min = tab[i].nbpages;
            k = i;
        }
    }
    return(tab[k]);
}