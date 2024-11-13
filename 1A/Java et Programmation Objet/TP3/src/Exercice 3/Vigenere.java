import java.io.*;
import java.lang.String;
import java.util.Scanner;

import static java.lang.Character.toLowerCase;
import static java.lang.Character.toUpperCase;

public class Vigenere {

    public static String chiffrer(String avant, String clef){
        clef = clef.replaceAll("\\s", "");
        StringBuilder apres = new StringBuilder(avant);
        int j = 0;
        for(int i=0; i<avant.length(); i++){
            if(((avant.charAt(i) >= 65) && (avant.charAt(i) <= 90))){
                apres.setCharAt(i,(char) (((int) avant.charAt(i) + (int) toUpperCase(clef.charAt(j)) - 130) % 26 + (int) 'A'));
                j++;
                if (j == clef.length()) {
                    j = 0;
                }
            }else if(((avant.charAt(i) >= 97) && (avant.charAt(i) <= 122))){
                apres.setCharAt(i,toLowerCase((char) (((int) toUpperCase(avant.charAt(i)) + (int) toUpperCase(clef.charAt(j)) - 130) % 26 + (int) 'A')));
                j++;
                if (j == clef.length()) {
                    j = 0;
                }
            }
        }
        return apres.toString();
    }

    public static String dechiffrer(String avant, String clef){
        clef = clef.replaceAll("\\s", "");
        StringBuilder apres = new StringBuilder(avant);
        int j = 0;
        for(int i=0; i<avant.length(); i++){
            if(((avant.charAt(i) >= 65) && (avant.charAt(i) <= 90))){
                apres.setCharAt(i, (char) ((((int) avant.charAt(i) - (int) toUpperCase(clef.charAt(j)) + 26) % 26 + (int) 'A')));
                j++;
                if (j == clef.length()) {
                    j = 0;
                }
            }else if(((avant.charAt(i) >= 97) && (avant.charAt(i) <= 122))){
                apres.setCharAt(i, toLowerCase((char) ((((int) toUpperCase(avant.charAt(i)) - (int) toUpperCase(clef.charAt(j)) + 26) % 26 + (int) 'A'))));
                j++;
                if (j == clef.length()) {
                    j = 0;
                }
            }
        }
        return apres.toString();
    }

    public static void main(String[] args){
        System.out.println("Entrer le 1er argument (c pour chiffrer, d pour dechiffrer) :");
        Scanner scanner=new Scanner(System.in);
        String mode=scanner.nextLine();
        if(!mode.equals("c") && !mode.equals("d")){
            System.out.println("ERROR ! FIRST ARGUMENT MUST BE C OR D !");
            return ;
        }
        System.out.println("Entrer le chemin du fichier contenant la clé :");
        String chemin_clef = scanner.nextLine();
        System.out.println("Entrer le chemin du fichier contenant le texte à modifier :");
        String chemin_avant = scanner.nextLine();
        System.out.println("Entrer le chemin du fichier d'enregistrement :");
        String chemin_apres = scanner.nextLine();
        scanner.close();
        try (InputStream texte_clef = new FileInputStream(chemin_clef);
             InputStream texte_avant = new FileInputStream(chemin_avant);
             OutputStream texte_apres = new FileOutputStream(chemin_apres)){
            String clef = "";
            String avant = "";
            byte[] buffer = new byte[1024];
            int bytesRead;
            while((bytesRead = texte_clef.read(buffer)) != -1){
                clef = clef + new String(buffer, 0, bytesRead);
            }
            byte[] buffer_2 = new byte[1024];
            int bytesRead_2;
            while((bytesRead_2 = texte_avant.read(buffer_2)) != -1){
                avant = avant + new String(buffer_2, 0, bytesRead_2);
            }
            if(mode.equals("c")){
                byte[] bytes = chiffrer(avant, clef).getBytes();
                texte_apres.write(bytes);
            }else{
                byte[] bytes = dechiffrer(avant, clef).getBytes();
                texte_apres.write(bytes);
            }
            System.out.println(clef);
            System.out.println(avant);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}