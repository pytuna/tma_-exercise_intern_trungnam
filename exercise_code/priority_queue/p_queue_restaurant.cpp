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

map<int, int> mp;
 
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
    public:

      Priority_Queue() {
         f = NULL;
      }
        
    // Dùng hàng đợi ưu tiên lồng nhau để thêm ưu tiên theo số lượng đơn đặt, khách VIP
      void add(int id, string food, string name="", int isVip=0) {
         Customer *t, *q;
         t = new Customer;
        // Dùng hash map để lưu thứ tự đặt món
        mp[id]++;
        t->order_num = mp[id];

        t->id = id;
        t->vip = isVip;
        t->name = name;
        t->food_name = food;
        
        // Set tên nếu Khách hàng được đặt tên
        if(!name.empty() &&  mp[id]>1 ){
            Customer *ptr;
            ptr = f;
            while(ptr != NULL) {
               if(ptr->id == t->id){
                   ptr->name = t->name;
               }
               ptr = ptr->l;
            }
        }
        
        // Thêm vào đầu Priority Queue nếu có số lượng đặt món ít nhất
        if (f == NULL || t->order_num < f->order_num) {
            
            t->l= f;
            f = t;
        } 
        else {
            // Nếu là khách vip thì thêm vào đầu Priority Queue
            if ( isVip > f->vip) {
                t->l= f;
                f = t;
                return;
            } 
            // Duyệt Priority Queue lần 1 đến vị trí đơn đặt hiện tại đến đơn đặt đầu tiên có thứ tự đặt bằng đơn đặt hiện tại
            q = f;
            while (q->l != NULL && q->l->order_num <  t->order_num){
                q = q->l; 
                
            }
            // Thêm vào đầu vị trí bắt đầu của số lượng đơn hàng hiện tại nếu là VIP
            if (q->l == NULL || (isVip > q->l->vip)){ 
                t->l = q->l;
                q->l = t;
                
            }else{
                // Duyệt Priority Queue lần 2 và Thêm vào hàng đợi các đơn đặt tiếp theo trong thứ tự đơn đặt tương ứng nếu là VIP thì đc ưu tiên
                Customer *q2 = q;
                 while (q2->l != NULL && q2->l->vip >= isVip && q2->l->order_num == t->order_num){
                    q2 = q2->l;
                }
                t->l = q2->l;
                q2->l = t;
            }
        }
      }

      void serve() {
         Customer *t;
         if(f == NULL) 
            cout<<"\tKhông còn khách phục vụ\n";
         else {
            t = f;
            
            if(t->name.empty()){
                cout<<"\tDon mon phục vụ khách "<<t->id<<" - Food: "<<t->food_name<<"\n\n";
            }else{cout<<"\tDon mon phục vụ khách "<<t->name<<" - Food: "<<t->food_name<<"\n\n";
            }
            
            
            f = f->l;
            free(t);
         }
      }
      void show() {
         Customer *ptr;
         ptr = f;
         if (f == NULL)
            cout<<"\tKhông còn khách phục vụ\n";
         else {
            cout<<"\tKhách hàng đang đợi\n";
            while(ptr != NULL) {
               cout<<"\tVIP: "<<ptr->vip<<" - ID:"<<ptr->id<<" - Order num: "<<ptr->order_num<<" - Name: "<<ptr->name<<" - Food: "<<ptr->food_name<<endl;
               ptr = ptr->l;
            }
         }
      }
};

template<class T>
vector<T> split_string(string input, char del){
    vector<T> output;
    stringstream ss(input);
    string e;
    while (!ss.eof()) {
        getline(ss, e, del);
        output.push_back(e);
    }
    return output;
}

int main() {
    int c, i, p;

    Priority_Queue pq;
    
    // pq.add(1, "a", "", 0);
    // pq.add(1, "b", "", 0);
    // pq.add(1, "c", "", 0);
    // pq.add(50, "a", "", 0);
    // pq.add(50, "h", "", 0);  
    // pq.add(3, "f", "", 1);
    // pq.add(3, "b", "", 1);
    // pq.add(7, "h", "", 1);
    // pq.add(4, "a", "", 1);
    // pq.add(14, "b", "", 1);
    // pq.add(17, "b", "", 0);
    // pq.add(17, "b", "", 0);
    // pq.add(17, "b", "", 0);
    // pq.add(17, "b", "", 0);
    string input;
    while(1){
        cout<<">> ";
        getline(cin, input);

        vector<string> a = split_string<string>(input, ' ');
        string choice = a[0];
        
        
        
        if(choice == "add"){
            a.push_back("");
            a.push_back("");
            int size_a = a.size();
            int id, isVip = 0;
            string name="", food= "";

            char *c_id = new char[a[1].length() + 1];
            strcpy(c_id, a[1].c_str());
            sscanf( c_id, "%d", &id);
            
            food = a[2];
            if (size_a >= 4) name = a[3];

            if(size_a >= 5){
                char *c_vip = new char[a[4].length() + 1];
                strcpy(c_vip, a[4].c_str());
                sscanf( c_vip, "%d", &isVip);
            }
            
            pq.add(id, food, name, isVip);

        }else if(choice == "serve"){
             pq.serve();
        }else if(choice == "show"){
            pq.show();
        }else if(choice == "exit"){
            break;
        }else{
            cout<<"Nhập sai!!!\n";
        }
        a.clear();
    }
    

    return 0;
}

