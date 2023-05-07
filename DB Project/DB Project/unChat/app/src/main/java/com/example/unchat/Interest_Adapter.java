package com.example.unchat;
import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Interest_Adapter extends RecyclerView.Adapter<Interest_Adapter.ViewHolder> {

    String[] interests;
    Context context;

    public Interest_Adapter(String[] interests, Context activity) {
        this.interests = interests;
        this.context = activity;
    }

    @NonNull
    @Override
    public Interest_Adapter.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View view = layoutInflater.inflate(R.layout.interest_adapter,parent,false);
        ViewHolder viewHolder = new ViewHolder(view);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull Interest_Adapter.ViewHolder holder, @SuppressLint("RecyclerView") int position) {
        holder.interest_textView.setText(interests[position]);
        holder.interest_textView.setOnClickListener(new View.OnClickListener() {
            @SuppressLint("ResourceAsColor")
            @Override
            public void onClick(View view) {
                if(Arrays.asList(Interests_Screen.Category_names).contains(interests[position]))
                    {
                       // Toast.makeText(context, "Parent", Toast.LENGTH_SHORT).show();
                        Interests_Screen.Selected_Category = interests[position];
                        Interests_Screen user_interests = (Interests_Screen) context;
                        user_interests.retrieveSubCategoryName();
                    }
                else
                {

                    if(Interests_Screen.usersInterests.contains(interests[position]))
                    {
                        Interests_Screen.usersInterests.remove(interests[position]);
                    }
                    else{
                    Interests_Screen.usersInterests.add(interests[position]);}
                }
                holder.interest_textView.setBackgroundColor(R.color.chat_background);
            }
        });

    }

    @Override
    public int getItemCount() {
        return interests.length;
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        public  TextView interest_textView;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            interest_textView = itemView.findViewById(R.id.intrest_textview);
        }
    }
}
