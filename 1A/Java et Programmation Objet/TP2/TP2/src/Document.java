public class Document {
    int numero;
    String titre;

    public Document(int numero, String titre){
        this.numero = numero;
        this.titre = titre;
    }
    public Document(Document doc) {
        this.numero = doc.numero;
        this.titre = doc.titre;
    }
    public String toString(){
        return numero+ " + " +titre;
    }
    public boolean equals(Document doc1, Document doc2) {
        if (doc1.getClass() == doc2.getClass()) {
            if (doc1.numero == doc2.numero) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}