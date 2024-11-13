module com.example.tp4_1 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens com.example.tp4_1 to javafx.fxml;
    exports com.example.tp4_1;
}