#include"van_dong_vien.h"

VanDongVien::VanDongVien(){
    
}
VanDongVien::VanDongVien(std::string hoten, int tuoi, std::string monthidau, float cannang, float chieucao)
:hoten(hoten), tuoi(tuoi), monthidau(monthidau), chieucao(chieucao) ,cannang(cannang)
{
   
}

VanDongVien::~VanDongVien(){
        
}

std::ostream& operator<< (std::ostream& os, const VanDongVien& vdv)
{   
    os << "Họ tên: "<<vdv.hoten<<std::endl;
    os << "Tuổi: "<<vdv.tuoi<<std::endl;
    os << "Môn thi đấu: "<<vdv.monthidau<<std::endl;
    os << "Cân nặng: "<<vdv.cannang<<std::endl;
    os << "Chiều cao: "<<vdv.chieucao<<std::endl;

    return os;
}
std::istream& operator >> (std::istream &is, VanDongVien & vdv) {
    std::cout<<"Nhập họ tên: ";
    is >> vdv.hoten;
    std::cout<<"Nhập tuổi: ";
    is >> vdv.tuoi;
    std::cout<<"Nhập môn thi đấu: ";
    is >> vdv.monthidau;
    std::cout<<"Nhập cân nặng: ";
    is >> vdv.cannang;
    std::cout<<"Nhập chiều cao: ";
    is >> vdv.chieucao;
    return is;    
}

bool operator > (const VanDongVien& l, const VanDongVien& r){
    return std::tie(l.chieucao, l.cannang) > std::tie(r.chieucao, r.cannang);
}