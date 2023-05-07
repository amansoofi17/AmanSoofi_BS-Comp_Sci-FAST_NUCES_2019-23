package com.example.unchat;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.AsyncCache;
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

import java.lang.reflect.Array;
import java.security.PublicKey;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Interests_Screen extends AppCompatActivity {
    //    public ArrayList<String>  Category_names = new ArrayList<>();
    public static List<String> usersInterests = new ArrayList<String>();
    TextView interest_textview;
    public static String[] Category_names;
    public static String[] subCategory_names;
    public static String[] Users_Selected_interests;
    ProgressDialog dialog;
    public static String Selected_Category = "";

    public static List<String> list = new ArrayList<String>();
    public static List<String> userslist = new ArrayList<String>();
    public static List<Integer> interestsCount = new ArrayList<Integer>();

    public static int count = 0;
    public static Integer user_count = 0;
    public static String check_user = "deepak000";

    private static String url = "https://wallflowernetwork.000webhostapp.com/";
    // public static final String interests_url = url + "Interests.php";
    public static final String getCategory_url = url + "retrive_categoryName.php";
    public static final String getSubCategory_url = url + "retriveSubcategories.php";
    public static final String insert_user_interests = url + "user_interests.php";
    public static final String fetch_usernames = url + "Fetch_usernames.php";
    public static final String fetch_interests = url + "Fetch_userInterests.php";



    Button next;
    RecyclerView recyclerView_horizontal, recyclerView_vert;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_interests_screen);
        dialog = new ProgressDialog(Interests_Screen.this);
        // loading category names and by clicking parent category it will show sub category
        retrieveCategoryName();

        // now fetching the different users for suggestions
       fetchUsernames();

        next = findViewById(R.id.intrest_next);
        next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                    for (int i = 0; i < usersInterests.size(); i++) {
                        insertUserInterests(usersInterests.get(i));
                    }
              for (int j = 0; j < userslist.size(); j++) {
                    fetchInterests(userslist.get(j));
                }

                dialog.setTitle("fetching Interests");
                dialog.show();
               // (new Handler()).postDelayed(5000);
//                for(int i = 0;i<userslist.size();i++)
//                {
//                    suggestions(userslist.get(i));
//                }

                         Intent intent = new Intent(Interests_Screen.this, options_menu.class);
                                 startActivity(intent);
            }
        });
        //Toast.makeText(Interests_Screen.this, "Suggestions", Toast.LENGTH_SHORT).show();
    }

    void setCategoryRecyclerView() {
        Category_names = new String[list.size()];
        list.toArray(Category_names);

        recyclerView_horizontal = findViewById(R.id.recycler_view_horizontal);
        recyclerView_horizontal.setHasFixedSize(true);
        GridLayoutManager gridLayoutManager = new GridLayoutManager(Interests_Screen.this, 1, GridLayoutManager.HORIZONTAL, false);
        recyclerView_horizontal.setLayoutManager(gridLayoutManager);
        Interest_Adapter categories = new Interest_Adapter(Category_names, Interests_Screen.this);
        recyclerView_horizontal.setAdapter(categories);
    }

    void setSubCategoryRecyclerView() {
        subCategory_names = new String[list.size()];
        list.toArray(subCategory_names);

        recyclerView_vert = findViewById(R.id.recycler_view_vertical);
        recyclerView_vert.setHasFixedSize(true);
        recyclerView_vert.setLayoutManager(new GridLayoutManager(this, 2));
        Interest_Adapter sub_categories = new Interest_Adapter(subCategory_names, this);
        recyclerView_vert.setAdapter(sub_categories);
    }

    void retrieveCategoryName() {
        StringRequest request = new StringRequest(Request.Method.POST, getCategory_url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        list.clear();
                        try {
                            // getting object
                            //  Toast.makeText(Interests_Screen.this, "in function", Toast.LENGTH_SHORT).show();
                            JSONObject jsonObject = new JSONObject(response);
                            String success = jsonObject.getString("success");
                            JSONArray jsonArray = jsonObject.getJSONArray("data");
                            if (success.equals("1")) {
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    JSONObject object = jsonArray.getJSONObject(i);
                                    list.add(object.getString("CATEGORY_NAME"));
                                }
                                setCategoryRecyclerView();
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Toast.makeText(Interests_Screen.this, "Category updated", Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(Interests_Screen.this, error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        });
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(request);
    }

    public void retrieveSubCategoryName() {
        StringRequest request = new StringRequest(Request.Method.POST, getSubCategory_url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        try {
                            // getting object
                            list.clear();
                            JSONObject jsonObject = new JSONObject(response);
                            String success = jsonObject.getString("success");
                            JSONArray jsonArray = jsonObject.getJSONArray("data");

                            if (success.equals("1")) {
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    JSONObject object = jsonArray.getJSONObject(i);
                                    list.add(object.getString("CATEGORY_NAME"));
                                }
                                if (Selected_Category.equals("")) {
                                    Toast.makeText(Interests_Screen.this, "Select Category", Toast.LENGTH_SHORT).show();
                                } else
                                    setSubCategoryRecyclerView();
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Toast.makeText(Interests_Screen.this, "SubCategory updated", Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(Interests_Screen.this, error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("CATEGORY_NAME", Selected_Category);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(request);
    }

    void insertUserInterests(String category) {
        dialog.setTitle("Saving Interests");
        StringRequest request;
        dialog.show();
        request = new StringRequest(Request.Method.POST, insert_user_interests,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        if (response.equalsIgnoreCase("inserted successfully")){
                            Toast.makeText(Interests_Screen.this, "Category Inserted", Toast.LENGTH_SHORT).show();
                            dialog.dismiss();
                        }
                        else {
                            Toast.makeText(Interests_Screen.this, "Not inserted", Toast.LENGTH_SHORT).show();
                        }
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(Interests_Screen.this, error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username", check_user);
                params.put("category", category);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(request);
    }

    void fetchUsernames() {
        StringRequest request = new StringRequest(Request.Method.POST, fetch_usernames,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        try {
                            // getting object
                            userslist.clear(); // in this we ftech usernames to compare the interests
                            JSONObject jsonObject = new JSONObject(response);
                            String success = jsonObject.getString("success");
                            JSONArray jsonArray = jsonObject.getJSONArray("data");

                            if (success.equals("1")) {
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    JSONObject object = jsonArray.getJSONObject(i);
                                    userslist.add(object.getString("username"));
                                    Toast.makeText(Interests_Screen.this, object.getString("username"), Toast.LENGTH_SHORT).show();
                                }
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Toast.makeText(Interests_Screen.this, "username fetched", Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(Interests_Screen.this, error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        });
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(request);
    }



    void fetchInterests(String username) {
        StringRequest request = new StringRequest(Request.Method.POST, fetch_interests,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        try {
                            // getting object
                            list.clear(); // in this we ftech usernames to compare the interests
                            JSONObject jsonObject = new JSONObject(response);
                            String success = jsonObject.getString("success");
                            JSONArray jsonArray = jsonObject.getJSONArray("data");

                            if (success.equals("1")) {
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    JSONObject object = jsonArray.getJSONObject(i);
                                    list.add(object.getString("CATEGORY_NAME"));
                                }
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Toast.makeText(Interests_Screen.this, "in interests", Toast.LENGTH_SHORT).show();
                        check_interests();
                        Toast.makeText(Interests_Screen.this, "Interests fetched", Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(Interests_Screen.this, error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username", username);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(request);
    }

    void check_interests() {
        count = 0;
        for (int j = 0; j < usersInterests.size(); j++) {
            if (list.contains(usersInterests.get(j))) {
                Toast.makeText(Interests_Screen.this, usersInterests.get(j), Toast.LENGTH_SHORT).show();
                count = count + 1;
            }
        }
        interestsCount.add(count);
    }



}