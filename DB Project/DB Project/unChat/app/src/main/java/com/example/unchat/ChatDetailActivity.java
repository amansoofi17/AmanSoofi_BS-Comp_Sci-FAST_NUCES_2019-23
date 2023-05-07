package com.example.unchat;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.annotation.SuppressLint;
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

public class ChatDetailActivity extends AppCompatActivity {
    TextView username;
    CircleImageView profileImage;
    Toolbar chattingToolbar;
    ImageButton back, send;
    RecyclerView recyclerView;
    EditText message_edit_text;
    FirebaseDatabase database;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_detail);
        username = findViewById(R.id.chat_username);
        profileImage = findViewById(R.id.chat_profile_pic);
        chattingToolbar = findViewById(R.id.chatting_toolbar);
        setSupportActionBar(chattingToolbar);
        back = findViewById(R.id.back_chat_button);
        database = FirebaseDatabase.getInstance();


        final String sender_username = LogIn_Screen.str_username; // this is login username means you are sender

        String recieved_userName = getIntent().getStringExtra("username");
        Integer recived_image = getIntent().getIntExtra("profilePic", 0);

        username.setText(recieved_userName);
        profileImage.setImageResource(recived_image);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(ChatDetailActivity.this, Messages.class);
                startActivity(intent);
//                finish();
            }
        });
        final ArrayList<messageModel> messagemodels = new ArrayList<messageModel>();
        final chatAdapter chatadapter = new chatAdapter(messagemodels, ChatDetailActivity.this);
        recyclerView = findViewById(R.id.chat_recyclerView);
        recyclerView.setAdapter(chatadapter);
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(ChatDetailActivity.this);
        recyclerView.setLayoutManager(linearLayoutManager);

        final String senderRoom = sender_username + recieved_userName;
        final String receiverRoom = recieved_userName + sender_username;

        database.getReference().child("chats")
                .child(senderRoom).addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                messagemodels.clear();
               for(DataSnapshot snapshot1 : snapshot.getChildren())
            {
                   messageModel model =  snapshot1.getValue(messageModel.class);
//                    assert model != null;
//                    model.setMessageId(snapshot1.getKey());
                    messagemodels.add(model);
//
            }
               chatadapter.notifyDataSetChanged();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        send = findViewById(R.id.send);
        message_edit_text = findViewById(R.id.enter_message);
        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message = message_edit_text.getText().toString();
                final messageModel m_model = new messageModel(sender_username, message);
                m_model.setTimestamp(new Date().getTime());
                message_edit_text.setText("");

                database.getReference().child("chats").child(senderRoom)
                        .push().setValue(m_model);
                database.getReference().child("chats").child(receiverRoom)
                        .push().setValue(m_model);

                Toast.makeText(ChatDetailActivity.this, "Done", Toast.LENGTH_SHORT).show();
//.addOnSuccessListener(new OnSuccessListener<Void>() {
//                    @Override
//                    public void onSuccess(Void unused) {
//                        database.getReference().child("chats").child(receiverRoom)
//                                .push().setValue(m_model).addOnSuccessListener(new OnSuccessListener<Void>() {
//                            @Override
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
