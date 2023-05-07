#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
#include<conio.h>
#include"words_into_hashtable.h"
#include"small_case.h"
#include"tokinze.h"
#include"phone_aspects.h"
#include<fstream>
using namespace std;
void Fetch_reviews(string FileName,queue<string> &q1)
{
ifstream fetch;
string Reviews;
fetch.open(FileName.c_str());
if(!fetch)
{
cout<<"Reviews File Not found"<<endl;
exit(0);
}
while(!fetch.eof())
{
getline(fetch,Reviews);
Reviews = make_small_case(Reviews);
q1.push(Reviews);
if(fetch.eof())
break;
}
fetch.close();
}
int main()
{
   system("cls");
    ifstream infile;
    int p_count = 0 ,n_count = 0;
    words_into_hashtable positive_hash;
    positive_hash.positive_words(); //storing positive words into the hashtable

    words_into_hashtable negative_hash; 
    negative_hash.negative_words(); //storing negative words into the hashtable

    words_into_hashtable s_words; // s_words = stop_words
    s_words.stop_words(); //storing stop words into the hashtable

    mobile_aspects mobile;
    mobile.insert_aspect(); //storing phone aspects into the linked list

    queue<string> reviews;
    stack<char*> stack_words;
     while(!reviews.empty())
      { reviews.pop();}
    cout<<endl;
   cout<<"\t\t*********** TEXT CLASSIFIER FOR MOBILE PHONE REVIEWS ***********"<<endl; 
   cout<<endl<<endl;
   while(1){
   cout<<"\t\tENTER YOUR CHOICE: "<<endl;
   char *ch = new char;
   cout<<" \t\t1: SAMSUNG "<<endl<<" \t\t2: MOTOROLA "<<endl<<" \t\t3: HUAWEI "<<endl<<" \t\t4: APPLE "<<endl<<" \t\t5: EXIT "<<endl;
   *ch = getch();
   fflush(stdin);
   system("cls");
   if(*ch == 49)
   {
      p_count = 0;
      n_count = 0;
      mobile.insert_initial_value(0);
      Fetch_reviews("samsung phone reviews.txt",reviews);
   }
   else if(*ch == 50)
   {
      p_count = 0;
      n_count = 0;
      mobile.insert_initial_value(0);
      Fetch_reviews("motorolla phone reviews.txt",reviews);
   }
   else if(*ch == 51)
   {
      p_count = 0;
      n_count = 0;
      mobile.insert_initial_value(0);
      Fetch_reviews("huwaei phone reviews.txt",reviews);
   }
   else if(*ch == 52)
   {
      p_count = 0;
      n_count = 0;
      mobile.insert_initial_value(0);
      Fetch_reviews("apple phone reviews.txt",reviews); 
   }
   else if(*ch == 53)
   {
      exit(0);
   }
   else
   {
       cout<<"INCORRECT CHOICE "<<endl<<endl;
       continue;
   }
      string temp = reviews.front();
      while(!reviews.empty())
      {
      cout<<endl<<temp<<endl;
      reviews.pop();
      char *temp_array = new char[count_length(temp)];
      strcpy(temp_array,temp.c_str());
      char* sent_ptr = toknize(temp_array,".");
      char* word_ptr;
        word_ptr = toknize(sent_ptr,", ");
        check = false;
        while(1)
        {
          char *temp_stop_array = s_words.search_words(word_ptr);        
          if(temp_stop_array == 0)
          {
             stack_words.push(word_ptr);
          }
          if(check)
          { 
           check = false;
           string temp(stack_words.top());
           stack_words.pop();
           char* t_array = new char[temp.length()];
           strcpy(t_array,temp.c_str());
           t_array[temp.length()-1] = '\0';
           stack_words.push(t_array);
           if(t_array != 0)
           delete t_array;
           break;
          }
         word_ptr = toknize(NULL,", "); 
        }
    bool *aspect_check = new bool; 
    *aspect_check = false;
    bool *check_positive = new bool;
    *check_positive = false;
    bool *check_negative = new bool;
     *check_negative = false;
     cout<<endl<<endl;
    while(!stack_words.empty())
    {
      aspects_node *aspect = mobile.search(stack_words.top());
      if(aspect!=NULL)
      {
        stack_words.pop();
        if(*check_positive)
        {
          aspect->value = (aspect->value)+1;
          continue;
        }
        else if(*check_negative)
        {
          aspect->value = (aspect->value)-1;
          continue;
        }
        else
        *aspect_check = true;
      }
       char* temp_search_hashtable = positive_hash.search_words(stack_words.top());
       if(temp_search_hashtable != 0)
      {
       p_count++;
       *check_positive = true;
       *check_negative = false;
       if(*aspect_check)
       {
         *aspect_check = false;
          aspect->value = (aspect->value)+1;
          *check_positive = false;
       }
      }
       else
       {
          temp_search_hashtable = negative_hash.search_words(stack_words.top());
           if(temp_search_hashtable != 0)
          {
             n_count++;
             *check_negative = true;
             *check_positive = false;
             if(*aspect_check)
                {
                 *aspect_check = false;
                  aspect->value = (aspect->value)-1;
                  *check_negative = false;
                }
          }
          else
          {
            *check_positive = false;
            *check_negative  = false;
          }
        }
       stack_words.pop();
    }
     if(check_positive != 0)
    delete check_positive;
     if(check_negative != 0)
    delete check_negative;
     if(aspect_check != 0)
    delete aspect_check;

     if(p_count<n_count)
     cout<<"BAD REVIEW "<<endl<<endl;
     else if(p_count>n_count)
     cout<<"GOOD REVIEW "<<endl<<endl;
     else
     {
         cout<<"AVERAGE REVIEW "<<endl<<endl;
     }
     p_count = 0;
     n_count = 0;
     if(!reviews.empty())
     temp = reviews.front();
   } 
   mobile.print_aspects();
  }
    return 0;
}