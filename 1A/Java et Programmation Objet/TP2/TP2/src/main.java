public class main {
    public static void main(String[] args){
        try {
            Bibliotheque bib=new Bibliotheque(Integer.parseInt(args[0]));
            for(int i=1;i<args.length;i=i+2){
                System.out.println("Biblio capacity :");
                System.out.println(bib.getCapacite());
                System.out.println("Current number of documents :");
                System.out.println(bib.getNbDocuments());
                Document doc = new Document(Integer.parseInt(args[i]), args[i+1]);
                try {
                    System.out.println("Ajout du document :");
                    System.out.println(bib.ajoutDocument(doc));
                }catch(Bibliotheque.BibliothequeException e){
                    System.out.println(e.getMessage());
                }
            }
            Document doc1 = new Document(Integer.parseInt(args[1]), args[2]);
            Document doc2 = new Document(Integer.parseInt(args[3]), args[4]);
            System.out.println(doc1.equals(doc1, doc2));
            System.out.println("Current number of documents :");
            System.out.println(bib.getNbDocuments());
            System.out.println(bib.toString());
        }catch(NumberFormatException e){
            System.out.println("Invalid input ! Please put in this order: number name number name !");
        }
        Bibliotheque bib=new Bibliotheque(5);
    }
}