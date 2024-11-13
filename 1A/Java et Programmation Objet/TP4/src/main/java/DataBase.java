import java.sql.*;

public class DataBase {
    private Connection Conn ;

    public DataBase() {
        try {
            Class.forName("org.sqlite.JDBC");
            Conn = DriverManager.getConnection(" jdbc :sqlite :cinema.db");
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    public ResultSet rechercher_films_par_comedien(String nom){
        ResultSet rs = null;
        String requete = " SELECT titre, anneesortie FROM films WHERE nomcomedien = "+nom;
        try{
            PreparedStatement ps = Conn.prepareStatement(requete);
            ps.setString(1, nom);
            rs = ps.executeQuery();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return rs;
    }
}
