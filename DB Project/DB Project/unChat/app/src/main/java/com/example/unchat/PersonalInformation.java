package com.example.unchat;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.RadioGroup;
import android.widget.Toast;
import androidx.appcompat.widget.Toolbar;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.util.HashMap;
import java.util.Map;

public class PersonalInformation extends AppCompatActivity {
    EditText email,birthDate;
    RadioGroup gender;
    ImageButton check,back;
    Toolbar personal_toolbar;
    private static String url = "https://wallflowernetwork.000webhostapp.com/";
    public static final String update_personalInfo = url + "update_personal_info.php";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_personal_information);

        email = findViewById(R.id.info_email);
        birthDate = findViewById(R.id.info_birthday);
        gender = findViewById(R.id.Gender);

        gender.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int i) {
                if(i == R.id.male){
                    Toast.makeText(PersonalInformation.this, "Male", Toast.LENGTH_SHORT).show();
                    Signup_Screen.Gender = 'M';
                }
                else if(i == R.id.female){
                    Toast.makeText(PersonalInformation.this, "Male", Toast.LENGTH_SHORT).show();
                    Signup_Screen.Gender = 'F';
                }
                else if(i == R.id.unknown){
                    Toast.makeText(PersonalInformation.this, "Male", Toast.LENGTH_SHORT).show();
                    Signup_Screen.Gender = 'U';
                }
            }
        });

        email.setText(Signup_Screen.str_email);
        birthDate.setText(Signup_Screen.str_birthdate);

        check = findViewById(R.id.personal_info_imageButton);
        back = findViewById(R.id.personal_info_back);
        personal_toolbar = findViewById(R.id.personal_info_toolbar);
       // setSupportActionBar(personal_toolbar);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        check.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                UpdatePersonalInfo();
            }
        });

    }
    void UpdatePersonalInfo() {
        StringRequest request;
        request = new StringRequest(Request.Method.POST,
                update_personalInfo, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                if(response.equalsIgnoreCase("updated"))
                {
                    Toast.makeText(PersonalInformation.this, "UPDATED!!", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    Toast.makeText(PersonalInformation.this, "Not updated", Toast.LENGTH_SHORT).show();
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(PersonalInformation.this, error.getMessage().toString(), Toast.LENGTH_SHORT).show();
            }
        }
        ) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                //Toast.makeText(signup.this, "Successfully edited", Toast.LENGTH_SHORT).show();
                params.put("username", LogIn_Screen.str_username);
                params.put("email", email.getText().toString());
                params.put("birthdate",birthDate.getText().toString());
                params.put("gender",Signup_Screen.Gender.toString());
                return params;
            }
        };

        RequestQueue requestQueue = Volley.newRequestQueue(PersonalInformation.this);
        requestQueue.add(request);
    }
}