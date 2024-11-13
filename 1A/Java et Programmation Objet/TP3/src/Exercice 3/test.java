public class test extends Vigenere{
    public static void main(String[] argv){
        String clef = new String();
        clef = argv[0];
        String texte = new String();
        texte = argv[1];
        System.out.println(dechiffrer(texte, clef));
    }
}
