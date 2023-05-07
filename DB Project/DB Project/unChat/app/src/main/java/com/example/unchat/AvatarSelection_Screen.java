package com.example.unchat;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;
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

public class AvatarSelection_Screen extends AppCompatActivity {
    public static Integer image_index;
    ListView listview;
    Integer[] arr;
    String encooded_image;
    Button avtar_next;

    ProgressDialog dialog;
    private static String url = "https://wallflowernetwork.000webhostapp.com/";
    public static final String sign_up = url + "signup.php";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_avatar_selection_screen);
        dialog = new ProgressDialog(AvatarSelection_Screen.this);
        arr = new Integer[]{R.drawable.avatar, R.drawable.avatar1, R.drawable.avatar2, R.drawable.avatar3, R.drawable.avatar4};
        listview = findViewById(R.id.listview1);
        AvatarSelection_Adapter ad = new AvatarSelection_Adapter(AvatarSelection_Screen.this, R.layout.avatarselection_adapter, arr);
        listview.setAdapter(ad);

        avtar_next = (Button)findViewById(R.id.avtar_next);
        avtar_next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                for(int j = 0;j<Interests_Screen.userslist.size();j++)
                {
                    Toast.makeText(AvatarSelection_Screen.this, Interests_Screen.userslist.get(j) + "'s count = " + String.valueOf(Interests_Screen.interestsCount.get(j)), Toast.LENGTH_SHORT).show();
                }
//                Integer temp = image_index;
//                 encooded_image = String.valueOf(arr[temp]);
//                 SignUp();
            }
        });
        // new Signup_BackGroundThread().execute();
    }

    void SignUp() {
        dialog.setTitle("Please Wait....");
        StringRequest request;
        dialog.show();
        request = new StringRequest(Request.Method.POST,
                sign_up, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                if (response.equalsIgnoreCase("registered successfully")) {
                    Toast.makeText(AvatarSelection_Screen.this, "Done", Toast.LENGTH_SHORT).show();
                    dialog.dismiss();
                    Intent intent  = new Intent(AvatarSelection_Screen.this,Interests_Screen.class);
                    startActivity(intent);
                }
                Toast.makeText(AvatarSelection_Screen.this, response, Toast.LENGTH_SHORT).show();

            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(AvatarSelection_Screen.this, error.getMessage().toString(), Toast.LENGTH_SHORT).show();
            }
        }
        ) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username", Signup_Screen.str_username);
                params.put("first_name", Signup_Screen.str_first_name);
                params.put("last_name", Signup_Screen.str_last_name);
                params.put("password",Signup_Screen.str_password);
                params.put("email", Signup_Screen.str_email);
                params.put("gender", String.valueOf(Signup_Screen.Gender));
                params.put("birthdate", Signup_Screen.str_birthdate);
                params.put("photo",encooded_image);
                return params;
            }
        };

        RequestQueue requestQueue = Volley.newRequestQueue(AvatarSelection_Screen.this);
        requestQueue.add(request);
    }




//    public class Signup_BackGroundThread extends AsyncTask<String, Integer, String> {
//        @Override
//        protected void onPreExecute() {
////            Dialog progressDialog = new Dialog(this);
////            progressDialog.setContentView(R.layout.loading_dialog);
////            progressDialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
////            progressDialog.setCancelable(false);
////            progressDialog.show();
//            super.onPreExecute();
//        }
//
//        @Override
//        protected String doInBackground(String[] values) {
//            SignUp();
//            return "Done";
//        }
//
//        @Override
//        protected void onPostExecute(String s) {
//            super.onPostExecute(s);
//            // progressDialog.dismiss();
////            Intent intent = new Intent(AvatarSelection_Screen.this, Interests_Screen.class);
////            startActivity(intent);
//        }
//    }

}