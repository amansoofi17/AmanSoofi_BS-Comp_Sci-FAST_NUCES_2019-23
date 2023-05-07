package com.example.unchat.messageAdapter;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.unchat.ChatDetailActivity;
import com.example.unchat.LogIn_Screen;
import com.example.unchat.R;
import com.example.unchat.messageAdapter.usersChatData;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class UsersChatAdapter extends RecyclerView.Adapter<UsersChatAdapter.ViewHolder> {

    usersChatData[] connections;
    Context context;

    public UsersChatAdapter(usersChatData[] connectionData, Context activity) {
        this.connections = connectionData;
        this.context = activity;
    }

    @NonNull
    @Override
    public UsersChatAdapter.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View view = layoutInflater.inflate(R.layout.sample_user,parent,false);
        ViewHolder viewHolder = new ViewHolder(view);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull UsersChatAdapter.ViewHolder holder, int position) {
        final usersChatData connectionDatalist = connections[position];
        holder.textView_username.setText(connectionDatalist.getUsername());
        holder.textView_desc.setText(connectionDatalist.getLastMessage());
        holder.connection_image.setImageResource(connectionDatalist.getImage());
        // get last messsage
        FirebaseDatabase.getInstance().getReference().child("chats").child(LogIn_Screen.str_username + connectionDatalist.getUsername()).
                orderByChild("timestamp").limitToLast(1).addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(snapshot.hasChildren())
                {
                    for(DataSnapshot snapshot1: snapshot.getChildren())
                    {
                        holder.textView_desc.setText(snapshot1.child("message").getValue().toString());
                    }
                }
            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });



        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(context, ChatDetailActivity.class);
                intent.putExtra("username",connectionDatalist.getUsername());
                intent.putExtra("profilePic",connectionDatalist.getImage());
                context.startActivity(intent);
            }
        });
    }

    @Override
    public int getItemCount() {
        return connections.length;
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        ImageView connection_image;
        TextView textView_username;
        TextView textView_desc;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            connection_image = itemView.findViewById(R.id.profile_image);
            textView_username = itemView.findViewById(R.id.name);
            textView_desc = itemView.findViewById(R.id.last_message);
        }
    }
}
