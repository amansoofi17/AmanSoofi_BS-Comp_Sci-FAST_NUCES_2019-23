#include<iostream>
using namespace std;
#pragma once
#ifndef SMALL_CASE_H
#define SMALL_CASE_H
string make_small_case(string str)
{
    int i = 0;
    while(i<str.length())
    {  
      if(str[i] >= 65 && str[i] < 91)
      {
          str[i] = str[i] + 32;
      }  
      i++;
    }
    return str;
}
string make_upper_case(string str)
{
      int i = 0;
    while(i<str.length())
    {  
      if(str[i] >= 97 && str[i] < 123)
      {
          str[i] = str[i] - 32;
      }  
      i++;
    }
    return str;
}
int count_length(string str)
{
  int i = 0;
  while(str[i] != 0)
  {
    i++;
  }
  return i+1;
}
#endif
