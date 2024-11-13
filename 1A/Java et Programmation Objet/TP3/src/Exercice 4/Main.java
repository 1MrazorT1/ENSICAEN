import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("Entrer le chemin du fichier original :");
        Scanner scanner=new Scanner(System.in);
        String original_chemin=scanner.nextLine();
        System.out.println("Entrer le chemin où vous souhaitez sauvegarder la copie :");
        String copy_chemin = scanner.nextLine();
        scanner.close();
        FileCopy fc=new FileCopy(original_chemin,copy_chemin);
        fc.setTemporisation(5000);
        affichage_2_sec thread = new affichage_2_sec(fc);
        thread.start();
        fc.duplicateFile();
        System.out.println(fc.getNumberBytesCopied());
    }
}
