package com.example.tp4_1;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.text.Text;
import javafx.event.ActionEvent;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.net.URL;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ResourceBundle;

public class Controller implements Initializable {

    @FXML
    private TextField nom_comedien_field;

    @FXML
    private TableView<Film> table_films;


    @FXML
    private Text statut_requete_text;

    @FXML
    private TableColumn<Film, String> titre;

    @FXML
    private TableColumn<Film, Integer> anneesortie;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        titre.setCellValueFactory(new PropertyValueFactory<>("titre"));
        anneesortie.setCellValueFactory(new PropertyValueFactory<>("anneeSortie"));
        statut_requete_text.setText("OK");
        titre.setCellFactory(new Callback<TableColumn<Film, String>, TableCell<Film, String>>() {
            @Override
            public TableCell<Film, String> call(TableColumn<Film, String> param) {
                return new TableCell<Film, String>() {
                    @Override
                    protected void updateItem(String item, boolean empty) {
                        super.updateItem(item, empty);
                        if (item != null) {
                            setText(item);
                            Film film = getTableView().getItems().get(getIndex());
                            Tooltip tooltip = new Tooltip(film.getResume());
                            setTooltip(tooltip);
                        } else {
                            setText(null);
                            setTooltip(null);
                        }
                    }
                };
            }
        });
    }

    @FXML
    public void effacer_clicked(ActionEvent event){
        if(nom_comedien_field == null){
            return;
        }
        nom_comedien_field.clear();
        table_films.getItems().clear();
    }

    @FXML
    public void quitter_clicked(ActionEvent event){
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        stage.close();
    }

    @FXML
    public void request_status(ActionEvent event) {
        table_films.getItems().clear();
        String nom_comedien = nom_comedien_field.getText();
        DataBase db = new DataBase();
        ResultSet resultat = db.rechercher_films_par_comedien(nom_comedien);
        int size = 0;
        try {
            while (resultat != null && resultat.next()) {
                size++;
                String filmTitle = resultat.getString("titre");
                int filmYear = resultat.getInt("anneesortie");
                String filmResume = resultat.getString("resume");
                table_films.getItems().add(new Film(filmTitle, filmYear, filmResume));
            }
        } catch (SQLException e) {
            statut_requete_text.setText("Error accessing database");
            e.printStackTrace();
            return;
        } finally {
            db.close();
        }
        String message;
        if (nom_comedien.length() <= 2) {
            table_films.getItems().clear();
            message = "Trop de comediens trouves, preciser le nom !";
        } else if (size == 0) {
            message = "Comedien inconnu";
        } else {
            message = "OK";
        }
        statut_requete_text.setText(message);
    }
}
