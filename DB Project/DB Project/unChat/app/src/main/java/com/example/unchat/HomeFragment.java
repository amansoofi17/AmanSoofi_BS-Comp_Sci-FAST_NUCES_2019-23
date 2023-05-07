package com.example.unchat;
import android.media.Image;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

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

import java.io.Console;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class HomeFragment extends Fragment {

    private String suggested_user;
    private static String url = "https://wallflowernetwork.000webhostapp.com/";
    public static final String show_suggestions_url = url + "show_suggestions.php";
    public static final String fetch_interests = url + "Fetch_userInterests.php";
    public static final String connections_url = url + "insert_into_connections.php";
    public static final String delete_suggestions_url = url + "delete_suggestion.php";



    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_home, container, false);
       // ImageButton see_more = v.findViewById(R.id.imageButton_seemore);
        Button accept = v.findViewById(R.id.button_accept);
        Button reject = v.findViewById(R.id.button_reject);
        ImageView image= v.findViewById(R.id.imageView_avatar);
        image.setImageResource(R.drawable.avatar1);
//        Interests_Screen.usersInterests.add("Blockchain");
//        Interests_Screen.usersInterests.add("Sindhi");
//        Interests_Screen.usersInterests.add("English");
//        Interests_Screen.usersInterests.add("Virtual Reality");

    //    showSuggestions(v);

        //On click image button see_more
//        see_more.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                //see_more code
//
//            }
//        });                     //see_more onClick code end

        //On click button accept
        accept.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                add_into_connections(v);
            }
        });                     //accept onClick code end

        //On click button reject
        reject.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //reject code
                StringRequest request = new StringRequest(Request.Method.POST,delete_suggestions_url,
                        new Response.Listener<String>() {
                            @Override
                            public void onResponse(String response) {
                                Toast.makeText(getActivity(), response, Toast.LENGTH_SHORT).show();
                                if(response.equalsIgnoreCase("deleted")) {
                                    Toast.makeText(getActivity(), "Suggestion Successfully deleted", Toast.LENGTH_SHORT).show();
                                    showSuggestions(v);
                                }
                                 // by deleting it should update it by next suggestions
                            }
                        }, new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        Toast.makeText(getActivity(), error.getMessage(), Toast.LENGTH_SHORT).show();
                    }
                }) {
                    @Nullable
                    @Override
                    protected Map<String, String> getParams() throws AuthFailureError {
                        Map<String, String> params = new HashMap<String, String>();
                        params.put("username1", Interests_Screen.check_user);
                        params.put("username2", suggested_user);
                        return params;
                    }
                };
                RequestQueue requestQueue = Volley.newRequestQueue(getActivity());
                requestQueue.add(request);
            }
        });                     //reject onClick code end

        return v;
    }                           //method onCreate end

//    protected void change_view(Integer avatar_address, String username, String[] intrests, String bio){
//        ImageView imageview_avatar = findViewById(R.id.imageView_avatar);
//        imageview_avatar.setImageResource(avatar_address);
//        TextView textview_username = findViewById(R.id.textView_username);
//        textview_username.setText(username);
//        TextView textview_Bio = findViewById(R.id.textView_bio);
//        textview_Bio.setText(bio);
//
//    }

    void showSuggestions(View v) {
        ImageView image = v.findViewById(R.id.imageView_avatar);
        TextView suggested_username = v.findViewById(R.id.textView_username);
        StringRequest request = new StringRequest(Request.Method.POST, show_suggestions_url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        try {
                            // getting object
                            //  Toast.makeText(Interests_Screen.this, "in function", Toast.LENGTH_SHORT).show();
                            JSONObject jsonObject = new JSONObject(response);
                            String success = jsonObject.getString("success");
                            JSONArray jsonArray = jsonObject.getJSONArray("data");
                            if (success.equals("1")) {
                                    JSONObject object = jsonArray.getJSONObject(0);
                                    suggested_username.setText(object.getString("username"));
                                    String image_resource = object.getString("image");
                                    image.setImageResource(Integer.parseInt(image_resource));
                                    suggested_user = object.getString("username");
                            }
                            fetchInterests(v);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Toast.makeText(getActivity(), "suggestions updated", Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(getActivity(), error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username",LogIn_Screen.str_username);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(getActivity());
        requestQueue.add(request);
    }

    void fetchInterests(View v) {
        StringRequest request = new StringRequest(Request.Method.POST,fetch_interests,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        try {
                            // getting object
                            Toast.makeText(getActivity(), "in responce", Toast.LENGTH_SHORT).show();
                            Interests_Screen.list.clear(); // in this we ftech usernames to compare the interests
                            JSONObject jsonObject = new JSONObject(response);
                            String success = jsonObject.getString("success");
                            JSONArray jsonArray = jsonObject.getJSONArray("data");

                            if (success.equals("1")) {
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    JSONObject object = jsonArray.getJSONObject(i);
                                    Interests_Screen.list.add(object.getString("CATEGORY_NAME"));
                                }
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Toast.makeText(getActivity(), "in interests", Toast.LENGTH_SHORT).show();
                       check_interests(v);
                        Toast.makeText(getActivity(), "Interests fetched", Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(getActivity(), error.getMessage(), Toast.LENGTH_SHORT).show();
                TextView interest1 = v.findViewById(R.id.interest1);
                interest1.setText(error.getMessage());
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username", suggested_user);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(getActivity());
        requestQueue.add(request);
    }

    void check_interests(View view) {
        List<String> temp = new ArrayList<String>();
        for (int j = 0; j < Interests_Screen.usersInterests.size(); j++) {
            if (Interests_Screen.list.contains(Interests_Screen.usersInterests.get(j))) {
                temp.add(Interests_Screen.usersInterests.get(j));
            }
        }

        TextView interest_category = view.findViewById(R.id.interest_category);
        TextView interest1 = view.findViewById(R.id.interest1);
        TextView interest2 = view.findViewById(R.id.interest2);
        TextView interest3 = view.findViewById(R.id.interest3);

        interest_category.setText("Interests: ");

        if(temp.get(0).equals("")){}
        else
        interest1.setText(temp.get(0));

        if(temp.get(1).equals("")){}
        else
            interest2.setText(temp.get(1));

        if(temp.get(2).equals("")){}
        else
            interest3.setText(temp.get(2));

    }

    void add_into_connections(View v) {
        StringRequest request = new StringRequest(Request.Method.POST,connections_url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Toast.makeText(getActivity(), response, Toast.LENGTH_SHORT).show();
                        if(response.equalsIgnoreCase("success")) {
                            Toast.makeText(getActivity(), "Connection Inserted", Toast.LENGTH_SHORT).show();
                            showSuggestions(v);
                        }

                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(getActivity(), error.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }) {
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("username1", LogIn_Screen.str_username);
                params.put("username2", suggested_user);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(getActivity());
        requestQueue.add(request);
    }
}                               //class MainActivity end