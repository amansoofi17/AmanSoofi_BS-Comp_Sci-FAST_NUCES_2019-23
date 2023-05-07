package com.example.unchat;
import androidx.appcompat.app.AppCompatActivity;
import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.google.android.material.textfield.TextInputEditText;
import com.google.firebase.database.FirebaseDatabase;

import java.util.Calendar;
public class Signup_Screen extends AppCompatActivity {
    Button button,back;
    private RadioGroup gender;
    DatePickerDialog datePickerDialog;
    public static String str_first_name, str_last_name, str_email, str_password, str_username, str_birthdate;
    public static Character Gender = 'n';
    ProgressDialog dialog;
    public static TextInputEditText first_name, last_name, email, password, confrim_pass, username, birthDate;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup_screen);
        Intent intent = getIntent();
        dialog = new ProgressDialog(this);
        first_name = findViewById(R.id.firstName);
        last_name = findViewById(R.id.last_name);
        username = findViewById(R.id.username);
        email = findViewById(R.id.email);
        password = findViewById(R.id.password);
        confrim_pass = findViewById(R.id.confirmPassword);
        birthDate = findViewById(R.id.Birthday);
        back = findViewById(R.id.back);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        initDatePicker();

        // radio button for taking the input of the gender
        gender = findViewById(R.id.Gender);
        gender.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int i) {
                if(i == R.id.male){
                    Toast.makeText(Signup_Screen.this, "Male", Toast.LENGTH_SHORT).show();
                    Gender = 'M';
                }
                else if(i == R.id.female){
                    Toast.makeText(Signup_Screen.this, "Male", Toast.LENGTH_SHORT).show();
                    Gender = 'F';
                }
                else if(i == R.id.unknown){
                    Toast.makeText(Signup_Screen.this, "Male", Toast.LENGTH_SHORT).show();
                    Gender = 'U';
                }
            }
        });

        button = findViewById(R.id.next);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

//                Intent intent2 = new Intent(Signup_Screen.this,options_menu.class);
//                startActivity(intent2);

                if (first_name.getText().toString().equals("")) {
                }if (last_name.getText().toString().equals("")) {
                } if (email.getText().toString().equals("")) {
                } if (password.getText().toString().equals("")) {
                } if (username.getText().toString().equals("")) {
                } if (confrim_pass.getText().toString().equals("")) {
                } if (Gender != 'n') {
                } if (birthDate.getText().toString().equals("")) {
                } else {
                    if (password.getText().toString().equals(confrim_pass.getText().toString())) {
                        str_first_name = first_name.getText().toString().trim();
                        str_last_name = last_name.getText().toString().trim();
                        str_email = email.getText().toString().trim();
                        str_password = password.getText().toString().trim();
                        str_username = username.getText().toString().trim();
                        str_birthdate = birthDate.getText().toString().trim();


                        first_name.setText("");
                        last_name.setText("");
                        username.setText("");
                        birthDate.setText("");
                        email.setText("");
                        password.setText("");
                        confrim_pass.setText("");

                        Intent intent1 = new Intent(Signup_Screen.this,AvatarSelection_Screen.class);
                        startActivity(intent1);
                        //  new Signup_BackGroundThread().execute();
                        Toast.makeText(Signup_Screen.this, "Successfully updated", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(Signup_Screen.this, "Password incorrect", Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });

    }

    private void initDatePicker()
    {
        DatePickerDialog.OnDateSetListener dateSetListener = new DatePickerDialog.OnDateSetListener() {
            @Override
            public void onDateSet(DatePicker datePicker, int year, int month, int day) {
                month = month + 1;
                String date = makeDateString(year,month,day);
                birthDate.setText(date);
            }
        };
        Calendar cal  = Calendar.getInstance();
        int year = cal.get(Calendar.YEAR);
        int month = cal.get(Calendar.MONTH);
        int day = cal.get(Calendar.DAY_OF_MONTH);

        int style = AlertDialog.THEME_HOLO_LIGHT;
        datePickerDialog = new DatePickerDialog(this,style,dateSetListener,year,month,day);

    }

    private String makeDateString(int year, int month, int day) {
        return (day + "/" + month + "/" + year);
    }

    public void openDatePicker(View view)
    {
        datePickerDialog.show();

    }

}