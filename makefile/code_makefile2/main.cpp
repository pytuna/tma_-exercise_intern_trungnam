#include <iostream>
#include"./utils/sort_ultis.h"
#include"./utils/string_ultis.h"
using namespace std;


int main()
{
    string in;
    cout<<"Nhap: ";
    getline(cin, in);
    vector<int> arr = split_string(in);
    quickSort(arr, 0, arr.size()-1);
    for(auto i: arr){
        cout<<i<<endl;
    }
    return 0;
}


