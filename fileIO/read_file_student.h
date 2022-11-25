#pragma once
#include"sort.h"
#include"Student.h"

/*
* Đọc 1 sinh viên
*/
void read_student_from_file(Student* self, FILE *stream) ;
/*
    Đọc số lượng sinh viên
*/
int amount_student(FILE* stream, int mode) ;
/*
    Đọc tất cả sinh viên
*/
Student* read_all_student_from_file(int *n, FILE* stream) ;


Student* new_student();


/*
    Phân công sinh viên theo id chẵn và lẻ
*/
void phan_cong_hoc_sinh(Student *arr, int n);

int array_char_to_int(char buffer[]);

/*
    Xóa sinh viên cũ và thay bằng sinh viên mới
*/
void delete_and_insert_line_by_id(FILE *src, FILE *temp, const int id);
