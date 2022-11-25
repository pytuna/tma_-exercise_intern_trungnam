#pragma once
#include<string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Student Student;
struct Student {
    char name[99];
    int yearOfBirth;
    char address[99];
    int dutyDay;
    int id;
};