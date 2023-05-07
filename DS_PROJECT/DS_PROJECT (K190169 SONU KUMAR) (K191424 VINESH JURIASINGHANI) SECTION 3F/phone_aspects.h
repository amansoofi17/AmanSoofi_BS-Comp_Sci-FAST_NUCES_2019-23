#include<iostream>
#include<fstream>
#include <cstring>
#include"small_case.h"
#pragma once
#ifndef ASPECTS_H
#define ASPECTS_H
using namespace std;
class aspects_node
{
    public:
    string data;
    int value;
    aspects_node *next;
    aspects_node(int value,string data)
    {
        this->data= data;
        this->value = value;
        next = 0;
    }
};
class mobile_aspects
{
    aspects_node *head,*tail;
    public:
    mobile_aspects()
    {
        head = 0;
    }
  void insert_aspect()
   {
      ifstream infile;
      string temp_data;
      infile.open("mobile phone features.txt");
      if(!infile)
        {
          cout<<"mobile phone features not opened";
          exit(0);
        }
        while(!infile.eof())
        {
         infile>>temp_data;
         aspects_node *temp = new aspects_node(0,temp_data);
         if(head == 0)
         {
            head = temp;
            tail = temp;
         }
         else
            {
             tail->next = temp;
             tail = tail->next;
            }  
        }
       infile.close();
    }
void insert_initial_value(int i)
{
  aspects_node *temp = head;
   while(temp)
   {
      temp->value = i;
      temp = temp->next;
   }
   if(temp != 0)
   delete temp;
}
aspects_node* search(char *search_data)
  {
      string temp_string(search_data);
      aspects_node *temp = head;
     while(temp != 0)
     {
         if(temp->data == temp_string)
         {
             return temp;
         }
        temp = temp->next;
     }
     return NULL; 
  }
  void print_aspects()
  {
     aspects_node *temp = head;
     while(temp)
     {
       if(temp->value!= 0)
       {
          if(temp->value > 0 && temp->value < 4)
          {
            cout<<"OVERALL GOOD "<<make_upper_case(temp->data)<<endl<<endl;
          }  
          else if(temp->value > 3)
          {
            cout<<"OVERALL BEST "<<make_upper_case(temp->data)<<endl<<endl;
          }  
          else if(temp->value < 0 && temp->value > -4)
          {
            cout<<"OVERALL BAD "<<make_upper_case(temp->data)<<endl<<endl;
          }  
          else if(temp->value > -5)
          {
            cout<<"OVERALL WORST "<<make_upper_case(temp->data)<<endl<<endl;
          }  
       }
       temp = temp->next;
     }
     if(temp != 0)
     delete temp;
  }
  ~mobile_aspects()
  {
      if(head != 0)
      {
      delete head;
      head = 0;
      }
      if(tail != 0)
      {
      delete tail;
      tail = 0;
      }
  }
};
#endif