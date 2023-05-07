#include <iostream>
#include <cstring>
#pragma once
#ifndef TOKENIZE_H
#define TOKENIZE_H
using namespace std;
bool check = false;
char* toknize(char* str,char* delim)
{
   static char* temp_array = 0;
   if(str != 0)
   {
       temp_array = str;
   } 
   if(temp_array == NULL)
   {
       return NULL;
   }
   int i = 0;
   char space = 0,comma = 0,fullstop = 0;
   for(i = 0;i<strlen(delim);i++)
   {
       if(delim[i] == ' ')
       space = delim[i];
       else if(delim[i] == '.')
       fullstop = delim[i];
       else if(delim[i] == ',')
       comma = delim[i];

       if(strlen(delim) == 1)
       break;
   }
  char* final_array = new char[strlen(temp_array)+1];
  for(i = 0;temp_array[i] != '\0';i++)
   {  
      if(temp_array[i] != fullstop && temp_array[i] != comma && temp_array[i] != space && temp_array[i+1] != '\0')
      {
          final_array[i] = temp_array[i];
      }
      else if(temp_array[i+1] == '\0')
      {
          check = true;
          final_array[i] = temp_array[i];
          final_array[i+1] = '\0';
          temp_array = temp_array + i + 1;
          return final_array;
      }
      else
      {  
        final_array[i] = '\0';
        temp_array = temp_array + i + 1;
        return final_array;
      }
   }
   delete [] final_array;
} 
#endif