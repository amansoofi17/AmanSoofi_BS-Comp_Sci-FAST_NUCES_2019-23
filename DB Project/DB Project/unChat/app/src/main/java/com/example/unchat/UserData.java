package com.example.unchat;

public class UserData {
    private String username, password, email, gender, photo, lastMessage;

    public UserData() {

    }

    public UserData(String username, String password, String lastMessage) { // this constructor is used for messages in firebase
        this.username = username;
        this.password = password;
        this.lastMessage = lastMessage;
    }

    public UserData(String username, String password) { // this constructor is used for messages in firebase
        this.username = username;
        this.password = password;
    }

    public UserData(String username, String password, String email, String gender, String photo) {
        this.username = username;
        this.password = password;
        this.email = email;
        this.gender = gender;
        this.photo = photo;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public String getPhoto() {
        return photo;
    }

    public void setPhoto(String photo) {
        this.photo = photo;
    }

    public String getLastMessage() {
        return lastMessage;
    }

    public void setLastMessage(String lastMessage) {
        this.lastMessage = lastMessage;
    }

}
