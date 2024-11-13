public class Test_exercice_5 {
    public static void main(String[] args){
        Producteur prod = new Producteur(new TamponCirculaire(0),0);
        prod.start();
        while(!prod.isCreated()){
            try {
                Thread.sleep(0);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        Consommateur consom_1 = new Consommateur(prod.getTampon(), 0, "");
        consom_1.start();
    }
}
