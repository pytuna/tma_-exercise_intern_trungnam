#include<iostream>
#include"./models/van_dong_vien.h"
#include"./utils/sort.h"
#define MAX 3



int main(){
    int n;
    std::cout<<"Nhap n: ";
    std::cin>>n;

    VanDongVien *a = new VanDongVien[n];
    
    for(auto i = 0; i<n; i++){
        std::cin>>a[i];
    }

    for(auto i = 0; i<n; i++){
        std::cout<<"\n\tVận động viên thứ "<<i+1<<std::endl;
        std::cout<<a[i];
    }
    selectionSort<VanDongVien>(a, n);
    std::cout<<"\nSort Tang Dan\n\n";
    for(auto i = 0; i<n; i++){
        std::cout<<"\n\tVận động viên thứ "<<i+1<<std::endl;
        std::cout<<a[i];
    }
    return 0;
}