package com.example.unchat;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.Toast;

import com.example.unchat.messageAdapter.FragmentAdapter;
import com.google.android.material.tabs.TabLayout;

public class Messages extends AppCompatActivity {
    ViewPager view;
    TabLayout tab;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_messages);

        view = findViewById(R.id.message_viewPager);
        tab = findViewById(R.id.message_tablayout);
        view.setAdapter(new FragmentAdapter(getSupportFragmentManager()));
        tab.setupWithViewPager(view);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu,menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {

        switch (item.getItemId()) {
            case R.id.chat_group:
                Toast.makeText(this, "Group chat", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(Messages.this,GroupChatActivity.class);
                startActivity(intent);
                break;

            case R.id.log_out:
                Toast.makeText(this, "logout", Toast.LENGTH_SHORT).show();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onBackPressed() {
        Intent intent = new Intent(Messages.this,options_menu.class);
        startActivity(intent);
        super.onBackPressed();
    }
}