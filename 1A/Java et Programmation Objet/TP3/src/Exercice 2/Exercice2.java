import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.io.BufferedReader;

public class Exercice2 {
    public static void main(String[] args){
        Scanner scanner=new Scanner(System.in);
        System.out.println("Donner le chemin du fichier à lire (le nom du fichier doit etre inclu à la fin du chemin !):");
        String name=scanner.nextLine();
        File fichier;
        if(name.endsWith(".txt")){
            fichier= new File(name);
        }else{
            System.out.println("Fichier Invalide ! Il faut donner un fichier texte !");
            return;
        }
        if(fichier.exists()){
            HashMap<String, Integer> mots = new HashMap<>();
            try (BufferedReader br = new BufferedReader(new FileReader(fichier))) {
                List<String> lines = new ArrayList<>();
                String line;
                String regex = "[ |,|.|;|:|_|-|+|*/\\|.|;|\\n|\"|'|{|}()=><|\\t|!|?]";
                while ((line = br.readLine()) != null) {
                    String[] words = line.split(regex);
                for(String wrd : words) {
                    if (mots.containsKey(wrd)) {
                        mots.put(wrd, mots.get(wrd) + 1);
                    } else {
                        mots.put(wrd, 1);
                    }
                }
                }
                for(String wrd : mots.keySet()){
                    System.out.println("Le mot "+ wrd +" figure " + mots.get(wrd) + " fois.");
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }else{
            System.out.println("Fichier Invalide ! Il faut donner un fichier existant !");
            return;
        }
    }
}