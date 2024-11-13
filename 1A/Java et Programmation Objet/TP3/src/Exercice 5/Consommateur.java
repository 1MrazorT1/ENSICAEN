import java.util.Scanner;
import java.lang.String;

public class Consommateur extends Thread {
    private int temporisation;
    private String nom;
    public TamponCirculaire tampon;

    public Consommateur(TamponCirculaire tampon, int temporisation, String nom) {
        this.temporisation = temporisation;
        this.nom = nom;
        this.tampon = tampon;
    }

    public void setTemporisation(int temporisation) {
        this.temporisation = temporisation;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    @Override
    public void run() {
        System.out.println("Entrer le nom du consommateur :");
        Scanner scanner=new Scanner(System.in);
        this.setNom(scanner.nextLine());
        System.out.println("Entrer la durée de la temporisation souhaitée :");
        this.setTemporisation(Integer.parseInt(scanner.nextLine()));
        int delay_check = 0;
        while(this.tampon.tableau.length != 0){
            while(this.tampon.getTaille() == 0){
                System.out.println("TAMPON VIDE !");
            }
            this.tampon.preleve();
            delay_check++;
            if(delay_check == 2){
                try {
                    Thread.sleep(this.temporisation);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                delay_check = 0;
            }
        }
    }
}
