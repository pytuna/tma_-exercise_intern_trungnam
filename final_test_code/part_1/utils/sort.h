#pragma once
#ifndef __SORT__
#define __SORT__
#include<iostream>

template <class T>
void swap(T *xp, T *yp)
{
    T temp = *xp;
    *xp = *yp;
    *yp = temp;
}

template <class T>
void selectionSort(T arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n-1; i++)
    {
        
        min_idx = i;
        for (j = i+1; j < n; j++)
        if (arr[j] > arr[min_idx]){
            continue;
        }else{
             min_idx = j;
        }
           
        if(min_idx!=i)
            swap<T>(&arr[min_idx], &arr[i]);
    }
}


#endif