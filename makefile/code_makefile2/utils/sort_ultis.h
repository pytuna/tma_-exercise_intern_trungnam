#pragma once
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

void swap(int* a, int* b);

int partition(vector<int> &arr, int low, int high);

void quickSort(vector<int> &arr, int low, int high);