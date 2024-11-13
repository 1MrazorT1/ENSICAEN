public class Livre extends Document {
    String auteur;
    int nbpages;
    public Livre(int numero, String titre, String auteur, int nbpages){
        super(numero,titre);
        this.auteur=auteur;
        this.nbpages=nbpages;
    }
}
class Roman extends Livre{
    int prix;
    public Roman(int numero, String titre, String auteur, int nbpages, int prix){
        super(numero,titre,auteur,nbpages);
        this.prix=prix;
    }
}
class Manuel_Scolaire extends Livre{
    int niveau;
    public Manuel_Scolaire(int numero, String titre, String auteur, int nbpages, int niveau){
        super(numero,titre,auteur,nbpages);
        this.niveau=niveau;
    }
}