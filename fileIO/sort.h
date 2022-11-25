#pragma once
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include"Student.h"

void swap(Student* a, Student* b);

int find(char* c, size_t n);

/* Lấy tên của sinh viên */
void getname(char *a, char *name);

/* So sánh theo tên sinh viên */
int compare_two_string_a_z(char *a, char *b, int iA, int iB);

int partition(Student* arr, int l, int r) ;

void quicksort(Student* arr, int l, int r) ;