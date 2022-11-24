#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <map>
#include <iterator>
#include<sstream>
#include <vector>
#include<memory>
using namespace std;

struct Customer  {
   int vip;
   int id;
   int order_num;
   string food_name;
   string name;
   struct Customer *l;
};

class Priority_Queue {
    private:
        Customer *f;
        
        map<int, int> mp;
    public:
        Customer *last_customer_pop;
        Priority_Queue();
        void add(int id, string food, string name="", int isVip=0) ;
        void serve();
        void show();
};
