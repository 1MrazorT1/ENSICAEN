module com.example.tp4 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens com.example.tp4 to javafx.fxml;
    exports com.example.tp4;
}