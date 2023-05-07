#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<iostream>
#include"Tokenize.h"
#include<fstream>
#include<ctime>
using namespace std;
class Node {
    string data;
    int total_synonyms;
    Node *nextword;
    Node *nextsynonym;
    public:
    Node(string d,int total_synonyms)
    {
        data = d;
        this->total_synonyms = total_synonyms;
        nextword = NULL;
        nextsynonym = NULL;
    }
    friend class LinkedList;
    friend class Hash_table;
};
class LinkedList {
    Node *head;
    public:
    LinkedList()
    {
        head = NULL;
    }
    Node* insert(string d,Node *synonym,int numberofsynonyms)
    {
        if(head == NULL) {
            head = new Node(d,numberofsynonyms);
            head->nextsynonym = synonym;
            return head;
        }
        else {
        Node *temp = head;
        while (temp->nextword!=NULL)
         {   temp = temp->nextword;  }
         Node *temp2 = temp;
         temp = temp->nextword;
         temp = new Node(d,numberofsynonyms);
         temp2->nextword = temp;
         temp->nextsynonym = synonym;
         return temp;
        }
        
    }
    void print()
    {
        Node *temp = head;
       // temp = temp->nextword;
        Node *temp2;
         while (temp!=NULL)
        {

            temp2 = temp;
            do
            {
                //cout<<"a";
                cout<<temp2->data<<"->";
                //cout<<"b";
                temp2 = temp2->nextsynonym;
               // cout<<"h";
            }while (temp2!=temp);
            
            
            cout<<endl;
            temp = temp->nextword;
        }
        
    }
    
    void print(int x)
    {
        Node *temp = head;
        while (temp!=NULL)
        {
            cout<<temp->data<<"->";
            temp = temp->nextword;
        }
        
        
    }
    friend class Hash_table;
};

class Hash_table {
    int number_of_index;
    LinkedList *list;
    public:
    Hash_table(int v) {
        number_of_index = v;
        list = new LinkedList[number_of_index];
        words_synonyms();
    }
    int Hash_Function(string key);       //returns sum of all ascii value mod total index (e.g 0-4 = mod 5)
    void insert(string *d,int synonyms);
    void print();
    
    void words_synonyms();
    string Find_Synonym(string s);
    
    
        
    
};

int Hash_table:: Hash_Function(string key)       //returns sum of all ascii value mod total index (e.g 0-4 = mod 5)
    {
        int size = key.size();
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += key[i];
        }
        return sum % number_of_index;
    }


void Hash_table:: insert(string *d,int synonyms) {
        Node *temp = NULL;
        for (int i = synonyms-1; i >= 0; i--)
        {
        int index = Hash_Function(d[i]);
        temp = list[index].insert(d[i],temp,synonyms);
        
        }
        Node *temp2 = temp;
        while (temp2->nextsynonym!=NULL)
        {
            temp2 = temp2->nextsynonym;
        }
        temp2->nextsynonym = temp;
    }


void Hash_table:: print()
    {
        
        for (int i = 0; i < number_of_index; i++)
        {
           list[i].print();
           cout<<"\n";
        }
        
    }


void Hash_table:: words_synonyms() {                       //bring words from file and stores then in hashtable
        ifstream infile;
        infile.open("synonyms.txt");
        if(!infile) {
            cout<<"Synonym File not found";
            exit(0);
        }
        string synonym_words;                       //synonym_words = all the words that are synonyms of eachother   
        int totalwords=0;                          //total words in string synonm_words
        string *str;                             //string array of size total words and all words on different index
        while (!infile.eof())
        {
            getline(infile,synonym_words);
            str = str_Tokon(synonym_words,&totalwords);
            insert(str,totalwords);
        }
        
    }


string Hash_table:: Find_Synonym(string s)
    {
        int index = Hash_Function(s);
        Node *temp = list[index].head;
        while(temp) {
            if(s == temp->data)
            {
                srand((unsigned)time(0));
                int randonnumber = rand()%temp->total_synonyms;
                if(randonnumber == 0)
                    randonnumber++;
                for (int i = 0; i < randonnumber; i++)
                {
                    temp = temp->nextsynonym;
                }
                s = temp->data;
                break;
            }
            temp = temp->nextword;
        }


        return s;
    }








#endif