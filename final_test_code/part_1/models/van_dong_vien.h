#pragma once
#ifndef __VDV_H__
#define __VDV_H__
#include<iostream>
#include <tuple>
class VanDongVien{
private:
    std::string hoten;
    int tuoi;
    std::string monthidau;
    float cannang;
    float chieucao;
public:
    VanDongVien();
    VanDongVien(std::string hoten, int tuoi, std::string monthidau, float cannang, float chieucau);
    ~VanDongVien();
    friend std::ostream& operator<<(std::ostream& os, const VanDongVien& vdv);
    friend std::istream& operator>>(std::istream &is, VanDongVien & vdv) ;
    friend bool operator >(const VanDongVien& l, const VanDongVien& r);
};


#endif
