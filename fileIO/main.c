#include<string.h>
#include <stdio.h>
#include <stdlib.h>

FILE *stream, *stream2;

typedef struct Student Student;
struct Student {
    char name[99];
    int yearOfBirth;
    char address[99];
    int dutyDay;
    int id;
};

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

void swap(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int find(char* c, size_t n) {
    for (int i = (int)(n - 1); i >= 0; i--) {
        if (c[i] == ' ') {
            return (int)i+1;
        }
    }
    return -1;
}

int partition(Student* arr, int l, int r) {
    Student pivot = arr[r];
    int i = (l- 1); 
   
    for (int j = l; j <= r - 1; j++) {
        char c_pivot = pivot.name[find((pivot.name), strlen(pivot.name))];
        char c = arr[j].name[find((arr[j].name), strlen(arr[j].name))];
       
        if ((int)c < (int)c_pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[r]);
    return (i + 1);
}

void quicksort(Student* arr, int l, int r) {
    if (l < r) {
        int p = partition(arr, l, r);
        quicksort(arr, l, p - 1);  
        quicksort(arr, p + 1, r);
    }
}

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

void deleteLineByID(FILE *src, FILE *temp, const int id){
   char buffer[999];
   char arr_id[10];
   int idx;
   while ((fgets(buffer, 999, src)) != NULL){
        int count2 = 0;
        for(int j=0; j<999; j++){
            if(buffer[j]=='-'){
                count2++;
            }
            if(count2 == 3){
                j++;
                int k = 0;
                while (buffer[j]!='-')
                {
                   arr_id[k++] = buffer[j++];
                }
                arr_id[k]='\0';
                break;
            }
        }
    idx =  array_char_to_int(arr_id);
      if (idx != id){
        fputs(buffer, temp);}
    //   }else if(line == count){
    //     fputs("   \n", temp);
    //   }
   }
    printf("Thay sinh viên id = %d đã xóa bằng Nguyen Van Thanh Tai 2001 Tien Giang 7 4\n", id);
    fputs("\nNguyen Van Thanh Tai-2001-Tien Giang-7-4", temp);
}

void main(){

    char buffer[999];
    int  i=0, ch=0;

    if( (stream  = fopen( "file.txt", "r+" )) == NULL ){
       return;
    }

    int n = 0;
    Student* z;
    z = read_all_student_from_file( &n, stream);
    quicksort(z, 0, n - 1);
    printf("=== a) Xuat danh sach hoc sinh sap xep A-Z ===\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s\n", z[i].name);
    }

    printf("===b) Phan cong hoc sinh===\n");
    phan_cong_hoc_sinh(z, n);    

    stream2 = fopen("delete.tmp", "w");
    int line;
    
    printf("===c) Xoa va them sinh vien moi===\n");

    printf("Nhap id sinh vien can xoa: ");
    scanf("%d", &line);

    rewind(stream);
    deleteLineByID(stream, stream2, line);
    
    fclose( stream );
    fclose( stream2 );

    remove("file.txt");
    rename("delete.tmp", "file.txt");

    // if( (stream  = fopen( "file.txt", "r+" )) == NULL ){
    //    return;
    // }

   

    free(z);
}