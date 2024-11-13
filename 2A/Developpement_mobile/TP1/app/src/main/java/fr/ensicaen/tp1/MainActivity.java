package fr.ensicaen.tp1;

import android.os.Bundle;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    private TextView resultTextView;
    private double firstNumber = 0;
    private double secondNumber = 0;
    private String operator = "";

    private void setOperator(){

    }
    private void calculateResult(){
        secondNumber = Double.parseDouble(resultTextView.getText().toString());
        double result = 0;
        switch(operator){
            case "+":
                result = firstNumber + secondNumber;
            case "-":
                result = firstNumber - secondNumber;
            case "*":
                result = firstNumber * secondNumber;
            case "/":
                result = firstNumber / secondNumber;
        }
        resultTextView.setText(String.valueOf(result));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }
}