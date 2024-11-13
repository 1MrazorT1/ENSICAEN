public class TamponCirculaire {

    public Object[] tableau;
    private int taille_tableau;

    public TamponCirculaire(int taille_tableau) {
        this.taille_tableau = taille_tableau;
        this.tableau = new Object[taille_tableau];
    }

    public int getTaille() {
        return this.taille_tableau;
    }

    public void updateTaille(int taille) {
        this.taille_tableau = this.taille_tableau + taille;
    }

    public void depose(Object obj) {
        if(this.tableau.length == 0){
            Object[] nouveauTableau = new Object[this.taille_tableau + 1];
            nouveauTableau[this.taille_tableau] = obj;
            this.taille_tableau++;
            this.tableau = nouveauTableau;
            System.out.println("Object " + obj.toString() + " a été ajouté correctement.");
            return;
        }
        Object[] nouveauTableau = new Object[this.taille_tableau + 1];
        for (int i = 0; i < this.taille_tableau; i++) {
            nouveauTableau[i] = this.tableau[i];
        }
        nouveauTableau[this.taille_tableau] = obj;
        this.taille_tableau++;
        this.tableau = nouveauTableau;
        System.out.println("Object " + obj.toString() + " a été ajouté correctement.");
    }


    public Object preleve() {
        if (this.taille_tableau == 0) {
            System.out.println("Aucun objet n'a été prélevé !");
            return null;
        }
        Object obj = this.tableau[0];
        Object[] nouveauTableau = new Object[this.taille_tableau - 1];
        for (int i = 0; i < this.taille_tableau - 1; i++) {
            nouveauTableau[i] = this.tableau[i + 1];
        }
        this.tableau = nouveauTableau;
        this.taille_tableau--;
        if (obj != null) {
            System.out.println("Object " + obj.toString() + " a été prélevé correctement.");
        }
        return obj;
    }
}