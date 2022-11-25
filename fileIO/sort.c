
#include"sort.h"

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
/* Lấy tên của sinh viên */
void getname(char *a, char *name){
    int iA = find(a, strlen(a));
    strncpy(name,&a[iA],strlen(a)-iA);
    name[strlen(a)-iA] = '\0';
}
/* So sánh theo tên sinh viên */
int compare_two_string_a_z(char *a, char *b, int iA, int iB){
    if(a[iA] == '\0' && b[iB]=='\0'){
        return 0;
    }
    if(a[iA] == '\0' && b[iB]!='\0'){
        return -1;
    }
    if(b[iA]=='\0' && a[iA] != '\0'){
        return 1;
    }
    if(a[iA]==b[iB]){
        return compare_two_string_a_z(a,b,iA+1, iB+1);
    }
    if( (int)a[iA] > (int)b[iB] ){
        return 1;
    }
    if( (int)a[iA] < (int)b[iB] ){
        return -1;
    }
    return 0;
}

int partition(Student* arr, int l, int r) {
    Student pivot = arr[r];
    int i = (l- 1); 
   
    for (int j = l; j <= r - 1; j++) {
        // lấy tên của sinh viên
        char name_pivot[99];
        getname(pivot.name, name_pivot);
        char name_curr[99];
        getname(arr[j].name, name_curr);

        // so sánh tên 
        int comp = compare_two_string_a_z(name_pivot, name_curr, 0,0);
       
        if (comp == 1) {
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