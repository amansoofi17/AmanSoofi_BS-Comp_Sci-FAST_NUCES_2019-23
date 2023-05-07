package com.example.unchat.model;

public class messageModel {
    String u_id,message,messageId;
    Long timestamp;


     // empty constructor for the database
    public messageModel(){

    }

    public messageModel(String u_id, String message, String messageId, Long timestamp) {
        this.u_id = u_id;
        this.message = message;
        this.messageId = messageId;
        this.timestamp = timestamp;
    }
    public messageModel(String u_id, String message)
    {
        this.u_id = u_id;
        this.message = message;
    }

    public String getU_id() {
        return u_id;
    }

    public void setU_id(String u_id) {
        this.u_id = u_id;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public String getMessageId() {
        return messageId;
    }

    public void setMessageId(String messageId) {
        this.messageId = messageId;
    }

    public Long getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(Long timestamp) {
        this.timestamp = timestamp;
    }
}
