#include"string_ultis.h"

vector<int> split_string(string input, char del){
    vector<int> output;
    stringstream ss(input);
    string num;
    while (!ss.eof()) {
        getline(ss, num, del);
        int number = 0;
        int check = 1;
        for(auto i: num){
            if((int)i == 45){
               check = -1; 
            }
            
            int z = ((int)i)-48;
            if(z>=0 && z<=9){
                number = number*10+z;
            }
        }
        output.push_back(number*check);
    }
    return output;
}