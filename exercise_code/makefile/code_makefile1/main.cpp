
#include <iostream>
#include <stdlib.h>     
#include <time.h>  
#include"sort.h"
#define MAX 999
using namespace std;

int main()
{
    srand (time(NULL));
    int n;
    cout<<"Nhap n: ";
    cin>>n;
    int arr[n];
    
    for(auto i=0; i<n; i++){
        arr[i] = rand() % 100 + 1;
    }
    
    for(auto i: arr){
        cout<<i<<" ";
    }
    quickSort(arr, 0, n-1);
    cout<<"\n=>sort"<<endl;
    for(auto i: arr){
        cout<<i<<" ";
    }
    return 0;
}