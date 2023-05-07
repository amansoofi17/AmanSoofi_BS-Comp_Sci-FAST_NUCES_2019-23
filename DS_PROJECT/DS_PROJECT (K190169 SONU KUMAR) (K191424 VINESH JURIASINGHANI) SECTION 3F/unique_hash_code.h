#include<iostream>
#include<cstring>
#pragma once
#ifndef UNIQUE_CODE_H
#define UNIQUE_CODE_H
using namespace std;
int generate_hash_code(string s)
{
    int hash = 2147483647;
    int g = 41; // value of g must be a prime value so take care 
    for(int i=0;i<s.length();i++)
    {
        hash = hash*g+s[i];
    }
    return hash;  // integer maximum value
}
#endif

