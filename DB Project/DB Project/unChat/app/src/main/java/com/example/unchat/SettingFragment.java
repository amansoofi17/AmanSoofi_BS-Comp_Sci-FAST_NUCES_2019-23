package com.example.unchat;
import android.app.Activity;
import android.content.Intent;
import android.media.Image;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

public class SettingFragment extends Fragment {

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view =  inflater.inflate(R.layout.fragment_setting, container, false);

        // For Notifications button
        Button not_button = view.findViewById(R.id.notification_buttton);
        not_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open_notifications();
            }
        });
        ImageButton not_image= view.findViewById(R.id.notification_Imagebuttton);
        not_image.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open_notifications();
            }
        });

        // For personalInformation button
        Button p_info_button = view.findViewById(R.id.personalInfoButton);
        p_info_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open_personalInfo();
            }
        });
        ImageButton p_info_Imagebutton= view.findViewById(R.id.personalInfoImageButton);
        p_info_Imagebutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open_personalInfo();
            }
        });

        // For ChangePassword button
        Button change_pass_button = view.findViewById(R.id.changePassButton);
        change_pass_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open_changePassword();
            }
        });
        ImageButton change_pass_Imagebutton= view.findViewById(R.id.changePasImageButton);
        change_pass_Imagebutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open_changePassword();
            }
        });
    return view;
    }
    public void open_notifications()
    {
        Intent notification_tab = new Intent(getActivity(),Notifications.class);
        startActivity(notification_tab);
       // ((Activity) getActivity()).overridePendingTransition(0, 0);

    }

    public void open_personalInfo()
    {
        Intent notification_tab = new Intent(getActivity(),PersonalInformation.class);
        startActivity(notification_tab);
    }

    public void open_changePassword()
    {
        Intent notification_tab = new Intent(getActivity(),ChangePassword.class);
        startActivity(notification_tab);
    }
}
