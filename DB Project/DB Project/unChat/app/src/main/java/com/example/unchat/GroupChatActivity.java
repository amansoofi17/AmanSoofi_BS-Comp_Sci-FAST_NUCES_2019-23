package com.example.unchat;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import com.example.unchat.messageAdapter.chatAdapter;
import com.example.unchat.model.messageModel;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.Date;

import de.hdodenhof.circleimageview.CircleImageView;

public class GroupChatActivity extends AppCompatActivity {
    TextView groupname;
    CircleImageView profileImage;
    Toolbar chattingToolbar;
    ImageButton back, send;
    RecyclerView recyclerView;
    EditText message_edit_text;
    FirebaseDatabase database;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_group_chat);

        groupname = findViewById(R.id.groupchat_name);
        profileImage = findViewById(R.id.groupchat_profile_pic);
        chattingToolbar = findViewById(R.id.groupchatting_toolbar);
        setSupportActionBar(chattingToolbar);
        back = findViewById(R.id.groupchatback_button);
        send = findViewById(R.id.groupchatsend);
        recyclerView = findViewById(R.id.groupchat_recyclerView);
        message_edit_text = findViewById(R.id.groupchat_enter_message);
        database = FirebaseDatabase.getInstance();


        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(GroupChatActivity.this, Messages.class);
                startActivity(intent);
            }
        });

        final String sender_username = LogIn_Screen.str_username; // this is login username means you are sender
        groupname.setText("unChat lovers");

        final ArrayList<messageModel> messagemodels = new ArrayList<messageModel>();
        final chatAdapter chatadapter = new chatAdapter(messagemodels, GroupChatActivity.this);
        recyclerView.setAdapter(chatadapter);
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(GroupChatActivity.this);
        recyclerView.setLayoutManager(linearLayoutManager);

        database.getReference().child("Group Chat").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                messagemodels.clear();
                for(DataSnapshot snapshot1 : snapshot.getChildren())
                {
                    messageModel model =  snapshot1.getValue(messageModel.class);
//                    assert model != null;
//                    model.setMessageId(snapshot1.getKey());
                    messagemodels.add(model);
                }
                chatadapter.notifyDataSetChanged();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });


        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message = message_edit_text.getText().toString();
                final messageModel m_model = new messageModel(sender_username, message);
                m_model.setTimestamp(new Date().getTime());
                message_edit_text.setText("");

                database.getReference().child("Group Chat")
                        .push().setValue(m_model).addOnSuccessListener(new OnSuccessListener<Void>() {
                    @Override
                    public void onSuccess(Void unused) {
                        Toast.makeText(GroupChatActivity.this, "Done", Toast.LENGTH_SHORT).show();
                    }
                });

//.addOnSuccessListener(new OnSuccessListener<Void>() {
//                    @Override
//                    public void onSuccess(Void unused) {
//                        database.getReference().child("chats").child(receiverRoom)
//                                .push().setValue(m_model).addOnSuccessListener(new OnSuccessListener<Void>() {
//                              @Override
//                            public void onSuccess(Void unused) {
//                                Toast.makeText(ChatDetailActivity.this, "inserted", Toast.LENGTH_SHORT).show();
//                            }
//                        });
//                    }
//                });
                // after that we have to store the sender id and message into the database;
            }
        });

    }

}