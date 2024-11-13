import java.io.File;
import java.util.Scanner;
public class Exercice1{
    public static void afficherNomsFichiers(String chemin){
        File directory=new File(chemin);
        if(directory.exists() && directory.isDirectory()){
            File[] FslashD= directory.listFiles();
            int i=0;
            for(File f : FslashD){
                if(f.isFile()){
                    System.out.println(f.getName());
                    i=i+1;
                }
            }
            if(i==0){
                System.out.println("Aucun fichier est présent dans ce dossier !");
            }
        }else{
            System.out.println("Argument provided is not a directory !");
        }
    }
    public static void afficherNomsFichiersJava(String chemin){
        File directory=new File(chemin);
        if(directory.exists() && directory.isDirectory()){
            File[] FslashD= directory.listFiles();
            int i=0;
            for(File f : FslashD){
                if(f.isFile() && f.getName().endsWith(".java")){
                    System.out.println(f.getName());
                    i=i+1;
                }
            }
            if(i==0){
                System.out.println("Aucun fichier java est présent dans ce dossier !");
            }
        }else{
            System.out.println("Argument provided is not a directory !");
        }
    }
    public static void main(String[] args){
        System.out.println("Entrer le chemin du dossier :");
        Scanner scanner=new Scanner(System.in);
        String chemin=scanner.nextLine();
        System.out.println("Vous voulez afficher tout les fichiers ou que les fichiers Java ?");
        System.out.println("Tapez 0 pour tout les fichiers ou 1 pour que les fichiers Java :");
        int reponse=scanner.nextInt();
        scanner.close();
        switch (reponse){
            case 0:
                afficherNomsFichiers(chemin);
                break;
            case 1:
                afficherNomsFichiersJava(chemin);
                break;
            default:
                System.out.println("Reponse invalide !");
        }
    }
}
