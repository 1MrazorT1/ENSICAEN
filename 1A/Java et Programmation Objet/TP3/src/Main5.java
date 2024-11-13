public class Main5 {
    public static void main(String[] args) {
        TamponCirculaire tampon = new TamponCirculaire(0);
        int taille = 5;
        tampon.updateTaille(taille);
        for (int i = 0; i < taille; i++) {
            tampon.depose("mohamed");
        }
        for(int i = 0; i < taille; i++){
            System.out.println(tampon.tableau[i]);
        }
        for(int i = 0; i < 2*taille; i++){
            tampon.preleve();
        }
    }
}
