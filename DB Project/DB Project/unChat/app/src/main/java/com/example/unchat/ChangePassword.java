package com.example.unchat;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class ChangePassword extends AppCompatActivity {

    public EditText oldPass,newPass,confirmPass;
    ImageButton back,check;
    Toolbar accounts_toolbar;

    private static String url = "https://wallflowernetwork.000webhostapp.com/";
    public static final String updatePass_url = url + "update_pass.php";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_password);
        oldPass = findViewById(R.id.oldpassword);
        newPass = findViewById(R.id.newpassword);
        confirmPass = findViewById(R.id.confirmpassword);
        accounts_toolbar = findViewById(R.id.accounts_toolbar);
        //setSupportActionBar(accounts_toolbar);
        back = findViewById(R.id.accounts_toolbar_back);
        check = findViewById(R.id.accounts_toolbar_check);

        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
               finish();
            }
        });

        check.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (newPass.getText().toString().equals(confirmPass.getText().toString()))
                {
                    // check if same
                    UpdatePassword();
                }
                else
                {
                    Toast.makeText(ChangePassword.this, "Not Correct", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    void UpdatePassword() {
        StringRequest request;
        request = new StringRequest(Request.Method.POST,
                updatePass_url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                if(response.equalsIgnoreCase("updated"))
                {
                    Toast.makeText(ChangePassword.this, "UPDATED!!", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    Toast.makeText(ChangePassword.this, "Old password is incorrect", Toast.LENGTH_SHORT).show();
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(ChangePassword.this, error.getMessage().toString(), Toast.LENGTH_SHORT).show();
            }
        }
        ) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                //Toast.makeText(signup.this, "Successfully edited", Toast.LENGTH_SHORT).show();
                params.put("username", LogIn_Screen.str_username);
                params.put("password", oldPass.getText().toString());
                params.put("password2",newPass.getText().toString());
                return params;
            }
        };

        RequestQueue requestQueue = Volley.newRequestQueue(ChangePassword.this);
        requestQueue.add(request);
    }
}