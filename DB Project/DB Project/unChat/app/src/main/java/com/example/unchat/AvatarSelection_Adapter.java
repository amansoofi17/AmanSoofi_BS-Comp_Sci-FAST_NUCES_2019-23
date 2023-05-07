package com.example.unchat;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class AvatarSelection_Adapter extends ArrayAdapter {
    private Integer[] avatar;
    Context context;

    public AvatarSelection_Adapter(@NonNull Context context, int resource, @NonNull Integer[] avatar) {
        super(context, resource, avatar);
        this.avatar = avatar;
        this.context = context;
    }


    @Nullable
    @Override
    public Integer getItem(int position) {
        return avatar[position];
    }


    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        convertView = LayoutInflater.from(getContext()).inflate(R.layout.avatarselection_adapter, parent, false);
        ImageView m1 = convertView.findViewById(R.id.imageView);
        m1.setImageResource(getItem(position));

        m1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AvatarSelection_Screen.image_index = position;
                Toast.makeText(getContext(), "Selected", Toast.LENGTH_SHORT).show();
            }
        });
        return convertView;
    }



}

