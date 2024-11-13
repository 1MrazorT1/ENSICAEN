import java.util.Scanner;

public class Producteur extends Thread {
    private int temporisation;
    private TamponCirculaire tampon;
    private boolean creation_check;

    public Producteur(TamponCirculaire tampon, int temporisation) {
        this.tampon = tampon;
        this.temporisation = temporisation;
        this.creation_check = false;
    }

    public void setTemporisation(int temporisation){
        this.temporisation = temporisation;
    }

    public TamponCirculaire getTampon(){
        return this.tampon;
    }

    public boolean isCreated() {
        return this.creation_check;
    }

    @Override
    public void run() {
        System.out.println("Entrer le nombre d'objet à déposer :");
        Scanner scanner=new Scanner(System.in);
        int nombre= Integer.parseInt(scanner.nextLine());
        this.tampon.updateTaille(nombre);
        System.out.println("Entrer la durée de la temporisation souhaitée :");
        this.setTemporisation(Integer.parseInt(scanner.nextLine()));
        int delay_check = 0;
        for(int i = 0; i < nombre; i++){
            System.out.println("Entrer l'object suivant :");
            this.tampon.depose(scanner.nextLine());
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
        this.creation_check = true;
    }
}
