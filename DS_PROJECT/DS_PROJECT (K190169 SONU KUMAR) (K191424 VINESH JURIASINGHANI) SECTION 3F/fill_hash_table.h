#include<iostream>
#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include"chains.h"
#include"unique_hash_code.h"
using namespace std;
int hash_func(int key)
{
    int temp = key%100;
    if(temp<0)
    {
       temp = temp * (-1);
    }
    return temp;
}
void insert(node *hash_table[],int key)
{
    int index = hash_func(key);
    insert_sort_order(&hash_table[index],key);
}
#endif