import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.sql.ResultSet;

public class Controller {
    @FXML
    private Button rechercher;
    @FXML
    private Button effacer;
    @FXML
    private Button quitter;
    @FXML
    private TextField nom_comedien_field;
    @FXML
    private TableView<Film> table_films;
    @FXML
    private TableColumn<Film, String> titre;
    @FXML
    private TableColumn<Film, Integer> anneeSortie;

    private void rechercher_clicked(ActionEvent event) {
        table_films.getItems().clear();
        String nom_comedien = nom_comedien_field.getText();
        DataBase db = new DataBase();
        ResultSet resultat = db.rechercher_films_par_comedien(nom_comedien);
        table_films.getItems().add(new Film(titre, anneeSortie));
    }

    private void effacer_clicked(ActionEvent event){
        nom_comedien_field.clear();
        table_films.getItems().clear();
    }

    private void quitter_clicked(ActionEvent event){
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        stage.close();
    }
}
