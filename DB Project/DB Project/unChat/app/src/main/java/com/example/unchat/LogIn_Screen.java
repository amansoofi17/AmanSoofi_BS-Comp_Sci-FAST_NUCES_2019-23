package com.example.unchat;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.material.textfield.TextInputEditText;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class LogIn_Screen extends AppCompatActivity {
    TextInputEditText username, password;
    Button login;
    public static String str_username = "Sonu", str_password;
    UserData userData;
    public static ArrayList<UserData> userDataArrayList = new ArrayList<>();
    ProgressDialog dialog;

    private static String url = "https://wallflowernetwork.000webhostapp.com/";
    public static final String login_url = url + "login.php";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_log_in_screen);
        dialog = new ProgressDialog(LogIn_Screen.this);
        username = findViewById(R.id.username);
        password = findViewById(R.id.password);
        login = findViewById(R.id.login_button);
        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                dialog.setTitle("Please Wait...");
                if (username.getText().toString().equals("")) {

                }
                if (password.getText().toString().equals("")) {

                } else {
                    str_username = username.getText().toString().trim();
                    str_password = password.getText().toString().trim();
                    new Login_BackGroundThread().execute();

                    // Login();
                }
            }
        });
    }

    void Login() {
        StringRequest request;
        request = new StringRequest(Request.Method.POST,
                login_url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                userDataArrayList.clear();
                try {

                    JSONObject jsonObject = new JSONObject(response);
                    String sucess = jsonObject.getString("success");
                    JSONArray jsonArray = jsonObject.getJSONArray("data");

                    if (sucess.equals("1")) {
                        Toast.makeText(LogIn_Screen.this, "Successfully Logged in", Toast.LENGTH_SHORT).show();
                        for (int i = 0; i < jsonArray.length(); i++) {

                            JSONObject object = jsonArray.getJSONObject(i);
                            String name = object.getString("username");
                            String pass = object.getString("password");
                            String email = object.getString("email");
                            String gender= object.getString("gender");
                            String photo = object.getString("photo");

                            userData = new UserData(name,pass,email, gender, photo);
                            userDataArrayList.add(userData);
                        }
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                dialog.dismiss();
                Toast.makeText(LogIn_Screen.this, error.getMessage().toString(), Toast.LENGTH_SHORT).show();
            }
        }
        ) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                //Toast.makeText(signup.this, "Successfully edited", Toast.LENGTH_SHORT).show();
                params.put("username", str_username);
                params.put("password", str_password);
                return params;
            }
        };

        RequestQueue requestQueue = Volley.newRequestQueue(LogIn_Screen.this);
        requestQueue.add(request);
    }


    public class Login_BackGroundThread extends AsyncTask<String, Integer, String> {
        @Override
        protected void onPreExecute() {
//            Dialog progressDialog = new Dialog(this);
//            progressDialog.setContentView(R.layout.loading_dialog);
//            progressDialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
//            progressDialog.setCancelable(false);
//            progressDialog.show();
            username.setText("");
            password.setText("");
            super.onPreExecute();
        }

        @Override
        protected String doInBackground(String[] values) {
            Login();
            return "Done";
        }

        @Override
        protected void onPostExecute(String s) {
            Intent intent = new Intent(LogIn_Screen.this,options_menu.class);
            startActivity(intent);
            super.onPostExecute(s);
            // progressDialog.dismiss();
//            Intent intent = new Intent(signup.this, Interests.class);
//            startActivity(intent);
        }
    }


    public void Register_Account(View view) {
        Intent intent = new Intent(LogIn_Screen.this, Signup_Screen.class);
        startActivity(intent);
    }

}