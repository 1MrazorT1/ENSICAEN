package com.example.tp4_1;

import java.sql.*;

public class DataBase {
    private Connection Conn ;

    public DataBase() {
        try {
            Class.forName("org.sqlite.JDBC");
            Conn = DriverManager.getConnection("jdbc:sqlite:cinema.db");
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public void close() {
        if (Conn != null) {
            try {
                Conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public ResultSet rechercher_films_par_comedien(String nom) {
        ResultSet rs = null;
        String requete = "SELECT films.titre, films.anneesortie, films.resume FROM films " +
                "JOIN com_film ON films.numerofilm = com_film.numerofilm " +
                "WHERE numerocomedien = (SELECT numerocomedien FROM comediens WHERE nomcomedien LIKE ?)";
        try {
            PreparedStatement ps = Conn.prepareStatement(requete);
            ps.setString(1, nom + "%");
            rs = ps.executeQuery();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Failed to search for films", e);
        }
        return rs;
    }
}
