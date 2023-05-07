package com.example.unchat;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class ConnectionFragment extends Fragment {

    RecyclerView recyclerView;
    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v =  inflater.inflate(R.layout.fragment_connection, container, false);
        recyclerView = v.findViewById(R.id.recyclerView);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(getContext()));

         // get the array which pass to adapter to set the data
//        ConnectionData[] connections  = new ConnectionData[options_menu.connections_array.size()];
//        options_menu.connections_array.toArray(connections);


        ConnectionData[] connections = new ConnectionData[]{
                new ConnectionData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new ConnectionData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new ConnectionData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new ConnectionData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new ConnectionData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24),
                new ConnectionData("Sonu Kumar",
                        "he is a nice Guy",R.drawable.ic_baseline_connect_without_contact_24)
        };

        ConnectionAdapter connectionAdapter = new ConnectionAdapter(connections,ConnectionFragment.this);
        recyclerView.setAdapter(connectionAdapter);
        return v;
    }
}
