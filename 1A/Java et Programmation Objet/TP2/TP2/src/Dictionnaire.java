public class Dictionnaire extends Document{
    int langue;
    public Dictionnaire(int numero, String titre, int langue){
        super(numero, titre);
        this.langue=langue;
    }
}