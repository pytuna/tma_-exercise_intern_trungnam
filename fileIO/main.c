#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include"sort.h"
#include"Student.h"
#include"read_file_student.h"

// định dạng file txt
// Họ tên-Năm sinh-Quê quán-ID-Ngày trực

FILE *stream, *stream2;
void main(){
    char buffer[999];
    int  i=0, ch=0;

    if( (stream  = fopen( "file.txt", "r+" )) == NULL ){
       return;
    }

    int n = 0;
    Student* arr_student;
    arr_student = read_all_student_from_file( &n, stream);
    quicksort(arr_student, 0, n - 1);

    printf("=== a) Xuat danh sach hoc sinh sap xep A-Z ===\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s\n", arr_student[i].name);
    }

    printf("===b) Phan cong hoc sinh===\n");
    phan_cong_hoc_sinh(arr_student, n);    

    stream2 = fopen("delete.tmp", "w");
    int id_sv;
    
    printf("===c) Xoa va them sinh vien moi===\n");

    printf("\t\tNhap id sinh vien can xoa: ");
    scanf("%d", &id_sv);

    delete_and_insert_line_by_id(stream, stream2, id_sv);
    
    fclose( stream );
    fclose( stream2 );

    remove("file.txt");
    rename("delete.tmp", "file.txt");
    free(arr_student);
}
