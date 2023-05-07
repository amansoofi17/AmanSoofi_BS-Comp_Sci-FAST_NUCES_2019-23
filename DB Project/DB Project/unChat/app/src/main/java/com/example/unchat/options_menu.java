package com.example.unchat;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.view.menu.MenuView;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageButton;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.material.navigation.NavigationView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class options_menu extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {
    private DrawerLayout drawer;
    public static ArrayList<ConnectionData> connections_array = new ArrayList<>();
    ConnectionData connection;
    private static String url = "https://wallflowernetwork.000webhostapp.com/";
    public static final String connections_url = url + "fetch_connections.php";
    public static final String suggestions_url = url + "suggestions.php";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_options_menu);
//        Interests_Screen interests = new Interests_Screen();
        for (int i = 0; i < Interests_Screen.userslist.size(); i++) {
            suggestions(Interests_Screen.userslist.get(i));
        }

        Toolbar toolbar = findViewById(R.id.options_menu_toolbar);
//       // setSupportActionBar(toolbar);

        drawer = findViewById(R.id.drawer_layout);
        NavigationView navigationView = findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(options_menu.this);


        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawer, toolbar,
                R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                    new HomeFragment()).commit();
            navigationView.setCheckedItem(R.id.nav_home);
          //  setConnectionData(); // set the connections data
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.chat, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        Toast.makeText(options_menu.this, "in options", Toast.LENGTH_SHORT).show();
        if (item.getItemId() == R.id.item_chat) {
            Toast.makeText(options_menu.this, "Message Clicked", Toast.LENGTH_SHORT).show();
        }
        return false;
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {

        if (item.getItemId() == R.id.nav_home) {
            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                    new HomeFragment()).commit();
        } else if (item.getItemId() == R.id.nav_connections) {
          //  setConnectionData();
            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                    new ConnectionFragment()).commit();
        } else if (item.getItemId() == R.id.nav_messages) {
            Intent intent = new Intent(options_menu.this, Messages.class);
            startActivity(intent);
        } else if (item.getItemId() == R.id.nav_Settings) {
            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                    new SettingFragment()).commit();
        } else if (item.getItemId() == R.id.Logout) {
            Toast.makeText(this, "logout", Toast.LENGTH_SHORT).show();
            Intent intent;
            intent = new Intent(this, LogIn_Screen.class);
            startActivity(intent);
        }
        if (item.getItemId() == R.id.item_chat) {
            Toast.makeText(options_menu.this, "Message Clicked", Toast.LENGTH_SHORT).show();
        }

        drawer.closeDrawer(GravityCompat.START);
        return true;
    }


    @Override
    public void onBackPressed() {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else
            super.onBackPressed();
    }

    //    @Override
//    public boolean onCreateOptionsMenu(Menu menu) {
//        MenuInflater inflater = getMenuInflater();
//        inflater.inflate(R.menu.drawer_menu,menu);
//        return true;
//    }
    void setConnectionData() {
        StringRequest request = new StringRequest(Request.Method.POST, connections_url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        connections_array.clear();
                        try {
                            // getting object
                            //  Toast.makeText(Interests_Screen.this, "in function", Toast.LENGTH_SHORT).show();
                            JSONObject jsonObject = new JSONObject(response);
                            String success = jsonObject.getString("success");
                            JSONArray jsonArray = jsonObject.getJSONArray("data");
                            if (success.equals("1")) {
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    JSONObject object = jsonArray.getJSONObject(i);
                                    connection.setUsername(object.getString("username"));
                                    connection.setDesc(object.getString("email"));
                                    Integer img_src = Integer.parseInt(object.getString("photo"));
                                    connection.setImage(img_src);

                                    connections_array.add(connection);
                                }
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(options_menu.this, error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username", LogIn_Screen.str_username);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(request);
    }

    void suggestions(String username) {
        StringRequest request = new StringRequest(Request.Method.POST, suggestions_url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        if(response.equalsIgnoreCase("registered successfully"))
                            Toast.makeText(options_menu.this, "Suggestions Inserted", Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(options_menu.this, error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username1",Signup_Screen.str_username);
                params.put("username2", username);
                params.put("match_count",String.valueOf(Interests_Screen.interestsCount.get(Interests_Screen.user_count)));
                Interests_Screen.user_count = Interests_Screen.user_count + 1;
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(request);
    }

}