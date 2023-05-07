package com.example.unchat.messageFragment;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.unchat.R;
import com.example.unchat.UserData;
import com.example.unchat.messageAdapter.UsersChatAdapter;
import com.example.unchat.messageAdapter.usersChatData;
import com.example.unchat.options_menu;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class Chats extends Fragment {
    FirebaseDatabase database;
    ArrayList<UserData> list = new ArrayList<>();
    RecyclerView recyclerView;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view =  inflater.inflate(R.layout.fragment_chats, container, false);
        recyclerView = view.findViewById(R.id.chat_view);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(getContext()));
        database = FirebaseDatabase.getInstance();

//        usersChatData[] connections = new usersChatData[options_menu.connections_array.size()];
//        for(int i = 0;i<options_menu.connections_array.size();i++)
//        {
//            connections[i].setUsername(options_menu.connections_array.get(i).getUsername());
//            connections[i].setImage(options_menu.connections_array.get(i).getImage());
//            connections[i].setLastMessage("Okay Take Care");
//        }

        usersChatData[] connections = new usersChatData[]{
                new usersChatData("amansoofi17",
                        "Hello",R.drawable.ic_baseline_connect_without_contact_24),
                new usersChatData("sumit Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new usersChatData("viney Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new usersChatData("sonukumar123",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new usersChatData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new usersChatData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24)
        };
        UsersChatAdapter connectionAdapter = new UsersChatAdapter(connections,getContext());
        recyclerView.setAdapter(connectionAdapter);
         // now set the recycler view with users which i have a connection
//        database.getReference().child("Users").addValueEventListener(new ValueEventListener() {
//            @Override
//            public void onDataChange(@NonNull DataSnapshot snapshot) {
//                list.clear();
//            }
//
//            @Override
//            public void onCancelled(@NonNull DatabaseError error) {
//
//            }
//        });


        return view;
    }
}