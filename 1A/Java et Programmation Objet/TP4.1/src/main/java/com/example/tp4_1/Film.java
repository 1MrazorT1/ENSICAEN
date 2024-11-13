package com.example.tp4_1;

public class Film {
    private int numero;
    private int anneeSortie;
    private String titre;
    private String resume;
    private int numero_genre;
    private int numero_realisateur;

    public Film(String titre, int anneeSortie, String resume){
        this.titre = titre;
        this.anneeSortie = anneeSortie;
        this.resume = resume;
    }

    public Film(String titre, int anneeSortie){
        this.titre = titre;
        this.anneeSortie = anneeSortie;
    }

    public Film(int numero, String titre, String resume, int numero_genre, int anneeSortie){
        this.numero = numero;
        this.titre = titre;
        this.resume = resume;
        this.numero_genre = numero_genre;
        this.anneeSortie = anneeSortie;
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public String getTitre() {
        return titre;
    }

    public void setTitre(String titre) {
        this.titre = titre;
    }

    public String getResume() {
        return resume;
    }

    public void setResume(String resume) {
        this.resume = resume;
    }

    public int getGenre() {
        return numero_genre;
    }

    public void setGenre(int genre) {
        this.numero_genre = genre;
    }

    public int getAnneeSortie() {
        return anneeSortie;
    }

    public void setAnneeSortie(int anneeSortie) {
        this.anneeSortie = anneeSortie;
    }
}