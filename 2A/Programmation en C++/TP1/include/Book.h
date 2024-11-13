#include <vector>
#ifndef BOOK_H
#define BOOK_H

struct Book{
    char titre[50];
    int nbpages;
};

int lireNombre();
void lireNombre(int* n);
//void lireNombre(int n);
void lireNombre(int& n);
Book lireLivre();
void lireMultiLivres(std::vector<Book>& Tab, int taille);
void afficherLivre(Book livre);
void afficherMultiLivres(std::vector<Book> Tab, int taille);
void echangeNbrPages(Book *l1, Book *l2);
Book& LivrePlusLong(std::vector<Book>& Tab, int taille);
Book& LivrePlusCourt(std::vector<Book>& Tab, int taille);

#endif