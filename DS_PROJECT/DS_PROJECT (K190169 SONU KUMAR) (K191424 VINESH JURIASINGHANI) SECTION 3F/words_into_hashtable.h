#include<iostream>
#include<cstring>
#pragma once
#ifndef WORDS_H
#define WORDS_H
#include"fill_hash_table.h"
#include"small_case.h"
#include<fstream>
using namespace std;
class words_into_hashtable
{
  node *hash_table[100];
  public:
  words_into_hashtable()
  {
     for(int i = 0;i<100;i++)
     hash_table[i] = 0;
  } 
  void positive_words()
  {
    string *p_words = new string;
    node *p;
    
    ifstream fetchP;
    fetchP.open("positive words.txt");
    if(!fetchP)  
    {
      cout<<"Missing possitive words file"<<endl;
      exit(0); 
    }
    while(!fetchP.eof())
    {
     fetchP>>*p_words;  
     *p_words = make_small_case(*p_words);
     int key = generate_hash_code(*p_words);
     insert(hash_table,key);
    }
     fetchP.close();
     delete p_words;
   }
   void negative_words()
  {
    string *p_words = new string;
    node *p;
    
    ifstream fetchP;
    fetchP.open("negative Words.txt");
    if(!fetchP)  
    {
      cout<<"Missing negative words file"<<endl;
      exit(0); 
    }
    while(!fetchP.eof())
    {
     fetchP>>*p_words;  
     *p_words = make_small_case(*p_words);
     int key = generate_hash_code(*p_words);
     insert(hash_table,key);
    }
     fetchP.close();
     delete p_words;
  }
   void stop_words()
  {
    string *p_words = new string;
    node *p;
    
    ifstream fetchP;
    fetchP.open("stop words.txt");
    if(!fetchP)  
    {
      cout<<"Missing stop words file"<<endl;
      exit(0); 
    }
    while(!fetchP.eof())
    {
     fetchP>>*p_words;  
     *p_words = make_small_case(*p_words);
     int key = generate_hash_code(*p_words);
     insert(hash_table,key);
    }
     fetchP.close();
     delete p_words;
  }
  char* search_words(char* words)
 {
   string temp(words);
   int key = generate_hash_code(temp);
     node* p = search(hash_table[hash_func(key)],key);
      if(p == 0)
      {
          return NULL;
      }
      else 
      return words;
  }  
};
#endif