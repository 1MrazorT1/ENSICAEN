import java.util.ArrayList;

public class Bibliotheque {
    private final int max;
    private final Document[] documents;

    public Bibliotheque(int n) {
        this.max = n;
        this.documents = new Document[n];
    }

    public int getCapacite() {
        return this.max;
    }
    public static class BibliothequeException extends Exception {
        public BibliothequeException(String message){
            super(message);
        }
    }
    public boolean ajoutDocument(Document doc) throws BibliothequeException {
        int i = 0;
        while (this.documents[i] != null) {
            i++;
            if(i>=this.max){
                System.out.println("Le document N°"+doc.numero+" et de titre "+doc.titre+" n'a pas été ajouté !");
                throw new BibliothequeException("Bibliotheque FULL !");
            }
        }
        this.documents[i] = doc;
        return true;
    }
    public int getNbDocuments() {
        int i = 0;
        while (i < this.documents.length && this.documents[i] != null) {
            i++;
        }
        return i;
    }

    public String toString() {
        String Str = "Cette bibliotheque contient: ";
        for (int i = 0; i < this.getNbDocuments(); i++) {
            Str = Str + ", ";
            Str = Str + this.documents[i].titre;
        }
        Str = Str + ".";
        return Str;
    }

    public ArrayList<Livre> recherche_par_auteur(String auteur){
        ArrayList<Livre> livres= new ArrayList<>();
        int n=this.getNbDocuments();
        Livre livre= new Livre(0,null, null, 0);
        for(int i=0;i<=n;i++){
            if(this.documents[i].getClass() == livre.getClass()){
                Livre lv= (Livre) this.documents[i];
                if(lv.auteur == auteur){
                    livres.add((Livre) this.documents[i]);
                }
            }
        }
        return livres;
    }
}