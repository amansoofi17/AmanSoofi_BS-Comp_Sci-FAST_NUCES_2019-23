#pragma once
#ifndef TOKENIZE_H
#define TOKENIZE_H
#include<iostream>
#include<cstring>
using namespace std;

string* str_Tokon(string s,int *totalwords)    //initially size is sent = 0 ; used to return size of string 
{
    char *a;
    a = new char[15];
    *totalwords = 0;
    for (int i = 0 ; s[i] != '\0' ; i++)
    {
        if((s[i] >= 97 && s[i] <= 122 || s[i] >= 65 && s[i] <= 90) && (s[i+1] == ' ' || s[i+1] == '\0' || s[i+1] == 9)) //A-Z,a-z,9 = tab or null character
            (*totalwords)++;
    }
    string *str;
    str = new string[*totalwords];
    for (int i = 0,j=0,k=0;s[i]!='\0' ; i++)
    {
         if((s[i]>=97 && s[i]<=122) || (s[i]>=65 && s[i]<=90) )
         {
             a[j] = tolower(s[i]);
             j++;
        }

        if((s[i]>=97 && s[i]<=122 || s[i]>=65 && s[i]<=90) && (s[i+1] ==' ' || s[i+1] == '\0'|| s[i+1] == 9))
        {
           a[j] = '\0'; //to store null character in string
            string temp(a);
            str[k] = temp;
            
            k++;
            j = 0;
            delete a;
            a = new char[15];

        }
    }

    
    return str;
}
#endif