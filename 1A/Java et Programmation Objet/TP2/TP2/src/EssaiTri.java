import java.util.Scanner;

public class EssaiTri
{
    public static void main (String[] argv)
    {
        boolean fini=false;
        Scanner clavier = new Scanner(System.in) ;
        String ligne;

        TriSimple tableTrie=new TriSimple(5,2);

        while (!fini)
        {
            System.out.println("a suivi des donnees a ajouter\n"+
                    "ou bien s suivi des donnees a supprimer\n"+
                    "ou bien q pour quitter");
            ligne=clavier.nextLine() ;
            String chaine [] = ligne.split("\\s") ;

            switch (chaine [0])
            {
                case "a" :
                    for (int i = 1 ; i != chaine.length ; i++)
                    {
                        try
                        {
                            tableTrie.inserer(Integer.parseInt(chaine [i]));
                        }
                        catch (NumberFormatException e)
                        {
                            System.err.println ("Probleme de format pour " + chaine [i]) ;
                        }
                    }
                    break;
                case "s" :
                    for (int i = 1 ; i != chaine.length ; i++)
                    {
                        try
                        {
                            tableTrie.supprimer(Integer.parseInt(chaine [i]));
                        }
                        catch (NumberFormatException e)
                        {
                            System.err.println("Probleme de format pour " + chaine [i]);
                        }
                    }
                    break;
                case "q" :
                    fini=true;;
                    break;
                default :
                    System.out.println("a suivi des donnees a ajouter\n"+
                            "ou bien s suivi des donnees a supprimer\n"+
                            "ou bien q pour quitter");
                    break;
            }
            System.out.println(tableTrie);
        }
    }
}
