package com.example.unchat;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.media.Image;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import androidx.appcompat.widget.Toolbar;

public class Notifications extends AppCompatActivity {
    ImageButton back;
    Toolbar not_toolbar;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_notifications);
        not_toolbar = findViewById(R.id.notifications_toolbar);
      //  setSupportActionBar(not_toolbar);
        back = findViewById(R.id.notifications_back);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
               // onBackPressed();
                finish();;
            }
        });
    }
}