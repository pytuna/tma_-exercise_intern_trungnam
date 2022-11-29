#include"read_file_student.h"

/*
* Đọc 1 sinh viên
*/
void read_student_from_file(Student* self, FILE *stream) {
    char ch;
    int i = 0, pos = 0;
    char buffer[5][99];
    do {
        ch = fgetc(stream);
        buffer[pos][i] = (char)ch;

        if (feof(stream) || buffer[pos][i] == '\n') {
            break;
        }

        if (buffer[pos][i] == '-') {
            buffer[pos][i] = '\0';
            i = 0;
            pos++;
            continue;
        }
        
        i++;
        
    } while (1);

    strcpy(self->name, buffer[0]);
    if (sscanf(buffer[1], "%d", &self->yearOfBirth)) {} // disable Warning C6031
    strcpy(self->address, buffer[2]);
    if (sscanf(buffer[3], "%d", &self->id)) {}
    if (sscanf(buffer[4], "%d", &self->dutyDay)){}

}
/*
    Đọc số lượng sinh viên
*/
int amount_student(FILE* stream, int mode) {
    fpos_t pos;
    char buffer_n[99];
    int pos_n = 0;
    int i = 0;

    fseek(stream, 0L, SEEK_SET);
    do {
        buffer_n[i] = fgetc(stream);
        if (buffer_n[i] == '\n') {
            buffer_n[i] = '\0';
            break;
        }
        pos_n = pos_n * 10 + (int)(buffer_n[i] - 48);
        i++;
    } while (1);

    /*fgetpos(stream, &pos);
    pos += 1;
    fsetpos(stream, &pos);*/
    fseek(stream, 0L, mode);
    return pos_n;
}

/*
    Đọc tất cả sinh viên
*/
Student* read_all_student_from_file(int *n, FILE* stream) {
    *n = amount_student(stream, SEEK_CUR);
    
    Student *students = (Student*)calloc(*n, sizeof(Student));
    
    for (int i = 0; i < *n; i++) {
        read_student_from_file(&students[i], stream);
    }
    fseek(stream, 0L, SEEK_END);
    return students;
}


Student* new_student() {
    return (Student*)malloc(sizeof(Student));
}



/*
    Phân công sinh viên theo id chẵn và lẻ
*/
void phan_cong_hoc_sinh(Student *arr, int n) {
    Student arr_le[99], arr_chan[99];
    int index1 = 0, index2 = 0;
    int count_check_index1 = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].id % 2 == 0) {
            // cach1
            arr[i].dutyDay = 2 + (2 * index1) - 6 * count_check_index1;
            if (arr[i].dutyDay > 7) {
                arr[i].dutyDay += 6 * count_check_index1;
                count_check_index1++;
                arr[i].dutyDay -= 6 * count_check_index1;
            }
            arr_chan[index1++] = arr[i];
        }
        else {
            // cach 2
            arr[i].dutyDay = (3 + (2 * index2%6));
            arr_le[index2++] = arr[i];
        }
       
    }
    printf("=== Xuat danh sach hoc sinh phan cong 2 4 6===\n");
    for (int i = 0; i < index1; i++) {

        printf("Name: %s - %d\n", arr_chan[i].name, arr_chan[i].dutyDay);
    }
    printf("=== Xuat danh sach hoc sinh phan cong 3 5 7===\n");
    for (int i = 0; i < index2; i++) {

        printf("Name: %s - %d\n", arr_le[i].name, arr_le[i].dutyDay);
    }

}

int array_char_to_int(char buffer[]){
    int result=0;
    int i = 0;
    while(buffer[i]!='\0'){
        int temp = (int) buffer[i++]-48;
        result = result*10+temp;
    }
    return result;
} 

/*
    Xóa sinh viên cũ và thay bằng sinh viên mới
*/
void delete_and_insert_line_by_id(FILE *src, FILE *temp, const int id){
    rewind(src);
    int n = 0;
    Student* z;
    z = read_all_student_from_file( &n, src);
    int pos = -1;
    for(int i =0; i<n; i++){
        if(id == z[i].id){
            pos = i;
            break;
        }
    }

    printf("\nXóa sinh viên id = %d Tên: %s", id, z[pos].name);

    strcpy( z[pos].name, "Tran Nguyen Minh Thu");
    if (sscanf("1995", "%d", &z[pos].yearOfBirth)) {} // disable Warning C6031
    strcpy( z[pos].address,"Vung Tau");

    printf("\nThay sinh viên đã xóa bằng: %s\n", z[pos].name);

    // Ghi vào file
    fprintf( temp, "%d%c", n, '\n' );
    for(int i=0; i<n;i++){
        char out[999];
        fprintf(temp, "%s-%d-%s-%d-%d\n", z[i].name, z[i].yearOfBirth, z[i].address, z[i].id, z[i].dutyDay);
    }
}
