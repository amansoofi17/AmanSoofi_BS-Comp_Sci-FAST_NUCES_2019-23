#include<iostream>
#include<fstream>
#include"HashTable.h"
#include<cstring>
using namespace std;


int main()
{

    string s;
    Hash_table a(100);
    int totalwords = 0;
    string *str;
    ifstream infile;
    infile.open("testcases.txt");
    if(!infile) {
        cout<<"Test Casses file could not be opened";
        exit(1);
    }
    
    while (!infile.eof())
    {
        getline(infile,s);
        if(infile.eof())    //for extra loop during infile
            break;

        for (int i = 0; s[i]!='\0'; i++)
        {
            s[i] = tolower(s[i]);
        }
        
        str = str_Tokon(s,&totalwords);
        cout<<endl;
        cout<<"Original : \n"<<s<<"\nParaphrased : "<<endl;
        for (int i = 0; i < totalwords; i++)
        {
            str[i] = a.Find_Synonym(str[i]);    
            cout<<str[i]<<" ";
        }
        cout<<endl;
        

    }
    
   // for (int i = 0; i < totalwords; i++)
    //{
     //  str[i] = a.Find_Synonym(str[i]);
      // cout<<str[i]<<" ";
    //}
    
    return 0;
}