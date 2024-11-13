import javafx.scene.control.TableColumn;
import java.lang.String;

public class Film {
    private int numero;
    private TableColumn<Film, Integer> anneeSortie;
    private String titre;
    private String resume;
    private int numero_genre;
    private int numero_realisateur;

    public Film(TableColumn<Film, String> titre, TableColumn<Film, Integer> anneeSortie){
        this.titre = String.valueOf(titre);
        this.anneeSortie = anneeSortie;
    }

    public Film(int numero, String titre, String resume, int numero_genre, TableColumn<Film, Integer> anneeSortie){
        this.numero = numero;
        this.titre = titre;
        this.resume = resume;
        this.numero_genre = numero_genre;
        this.anneeSortie = anneeSortie;
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public String getTitre() {
        return titre;
    }

    public void setTitre(String titre) {
        this.titre = titre;
    }

    public String getResume() {
        return resume;
    }

    public void setResume(String resume) {
        this.resume = resume;
    }

    public int getGenre() {
        return numero_genre;
    }

    public void setGenre(int genre) {
        this.numero_genre = genre;
    }
}
