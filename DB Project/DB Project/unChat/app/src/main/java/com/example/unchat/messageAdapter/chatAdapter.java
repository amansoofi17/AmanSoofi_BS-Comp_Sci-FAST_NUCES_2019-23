package com.example.unchat.messageAdapter;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.unchat.LogIn_Screen;
import com.example.unchat.R;
import com.example.unchat.model.messageModel;
import com.google.firebase.database.FirebaseDatabase;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class chatAdapter extends RecyclerView.Adapter{

    ArrayList<messageModel> messageModels;
    Context context;
    int SENDER_VIEW_TYPE = 1;
    int RECIVER_VIEW_TYPE = 2;
    String reciver_userName;

    public chatAdapter(ArrayList<messageModel> messageModels, Context context) {
        this.messageModels = messageModels;
        this.context = context;
    }

    public chatAdapter(ArrayList<messageModel> messageModels, Context context, String reciver_userName) {
        this.messageModels = messageModels;
        this.context = context;
        this.reciver_userName = reciver_userName;
    }

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        if(viewType == SENDER_VIEW_TYPE)
        {
            View view = LayoutInflater.from(context).inflate(R.layout.samplesender,parent,false);
            return new SenderViewHolder(view);
        }
        else
        {
            View view = LayoutInflater.from(context).inflate(R.layout.samplereciver,parent,false);
            return new RecieverViewHolder(view);
        }
    }

    @Override
    public int getItemViewType(int position) {
        if(messageModels.get(position).getU_id().equals(LogIn_Screen.str_username)) //compare with the logged username if it is equal then it is a sender
        {
            return SENDER_VIEW_TYPE;
        }
        else
            return RECIVER_VIEW_TYPE;
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        messageModel m_model = messageModels.get(position);

//        holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
//            @Override
//            public boolean onLongClick(View view) {
//                new AlertDialog.Builder(context).setTitle("Delete")
//                        .setMessage("Are you sure you want to delete the message?")
//                        .setPositiveButton("yes", new DialogInterface.OnClickListener() {
//                            @Override
//                            public void onClick(DialogInterface dialogInterface, int i) {
//                                FirebaseDatabase database = FirebaseDatabase.getInstance();
//                                String senderRoom = LogIn_Screen.str_username + reciver_userName;
//                                database.getReference().child("chats").child(senderRoom)
//                                        .child(m_model.getMessageId()).setValue(null);
//                            }
//                        }).setNegativeButton("No", new DialogInterface.OnClickListener() {
//                    @Override
//                    public void onClick(DialogInterface dialogInterface, int i) {
//                        dialogInterface.dismiss();
//                    }
//                }).show();
//
//                return false;
//            }
//        });

        if(holder.getClass() == SenderViewHolder.class)
        {
//            Toast.makeText(context, "in chatAdapter", Toast.LENGTH_SHORT).show();
            ((SenderViewHolder) holder).senderMsg.setText(m_model.getMessage());


//            Date date = new Date(m_model.getTimestamp());
//            SimpleDateFormat simpleDateFormat = new SimpleDateFormat("h:mm a");
//
//            String strDate = simpleDateFormat.format(date);
//            ((SenderViewHolder) holder).senderTime.setText(strDate.toString());
        }
        else
            ((RecieverViewHolder) holder).reciverMsg.setText(m_model.getMessage());

//        Date date = new Date(m_model.getTimestamp());
//        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("h:mm a");
//
//        String strDate = simpleDateFormat.format(date);
//        ((RecieverViewHolder) holder).reciverTime.setText(strDate.toString());
    }

    @Override
    public int getItemCount() {
        return messageModels.size();
    }

    public class RecieverViewHolder extends RecyclerView.ViewHolder{

        TextView reciverMsg,reciverTime;

        public RecieverViewHolder(@NonNull View itemView) {
            super(itemView);

            reciverMsg = itemView.findViewById(R.id.reciverText);
            reciverTime = itemView.findViewById(R.id.reciverTime);
        }
    }
    public class SenderViewHolder extends RecyclerView.ViewHolder{

        TextView senderMsg,senderTime;
        public SenderViewHolder(@NonNull View itemView) {
            super(itemView);

            senderMsg = itemView.findViewById(R.id.senderText);
            senderTime = itemView.findViewById(R.id.senderTime);
        }
    }

}

