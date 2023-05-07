package com.example.unchat;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.text.method.KeyListener;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

public class profileActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        ImageButton check,back;
        ImageView profilePic,edit_name,edit_username,edit_desc,edit_interest;
        EditText name,username,desc;
        RecyclerView recyclerView;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        check = findViewById(R.id.profile_activity_check);
        back = findViewById(R.id.profile_activity_back);
        profilePic = findViewById(R.id.profile_activity_pic);
        edit_name = findViewById(R.id.profile_activity_edit_name);
        edit_username = findViewById(R.id.profile_activity_edit_username);
        edit_desc = findViewById(R.id.profile_activity_edit_Bio);
        edit_interest = findViewById(R.id.profile_activity_edit_Interests);
        name = findViewById(R.id.profile_activity_name);
        username = findViewById(R.id.profile_activity_username);
        desc = findViewById(R.id.profile_activity_Bio);


        check.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                // store updated data in the database

                Toast.makeText(profileActivity.this, "Updated", Toast.LENGTH_SHORT).show();
            }
        });


        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(profileActivity.this, "Back Button", Toast.LENGTH_SHORT).show();
                // make intent from where  this was called
                finish();
            }
        });

        profilePic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(profileActivity.this, "Profile Clicked", Toast.LENGTH_SHORT).show();
                // change profile image (from database)
            }
        });




        edit_name.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                KeyListener temp;
                temp = name.getKeyListener();
                name.setKeyListener(temp);
            }
        });

        edit_username.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                KeyListener temp;
                temp = username.getKeyListener();
                username.setKeyListener(temp);
            }
        });

        edit_desc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                KeyListener temp;
                temp = desc.getKeyListener();
                desc.setKeyListener(temp);
            }
        });

        edit_interest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // edit in recycler view
            }
        });


    }
}