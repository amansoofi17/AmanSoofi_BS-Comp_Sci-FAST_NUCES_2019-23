#include<iostream>
#pragma once
#ifndef CHAINS_H
#define CHAINS_H
using namespace std;
class node
{
  public:
  int data;
  node *next; 
  node(int data)
  {
    next = 0;
    this->data = data;
  }
};
 void insert_sort_order(node **head,int value)
  {
     node *temp,*p = 0,*q = *head;
     temp = new node(value);
    if(*head == 0)
    {
     *head = temp;
    }
    else
    {
      while(q && q->data < value)
      {
        p = q;
        q = q->next;
      }
        if(q == *head)
        {
          temp->next = *head;
          *head = temp;
        }
        else
        {
          temp->next = p->next;
          p->next = temp;   
        }
    }
  }
   node *search(node *temp,int code)
  {
     while(temp != 0)
     {
         if(temp->data == code)
         {
             return temp;
         }
        temp = temp->next;
     }
    return NULL;
  }
  #endif