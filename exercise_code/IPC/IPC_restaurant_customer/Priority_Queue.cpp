#include"Priority_Queue.h"


Priority_Queue::Priority_Queue() {
    f = NULL;
    last_customer_pop = NULL;
}
        
// Dùng hàng đợi ưu tiên lồng nhau để thêm ưu tiên theo số lượng đơn đặt, khách VIP
void Priority_Queue::add(int id, string food, string name, int isVip) {
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

void Priority_Queue::serve() {
    Customer *t;
    if(f == NULL) 
    cout<<"\tKhông còn khách phục vụ\n";
    
    else {
    t = f;
    
    if(t->name.empty()){
        cout<<"\tDon mon phục vụ khách "<<t->id<<" - Food: "<<t->food_name<<"\n\n";
    }else{
        cout<<"\tDon mon phục vụ khách "<<t->name<<" - Food: "<<t->food_name<<"\n\n";
    }
    free(last_customer_pop);
    last_customer_pop = t;
    f = f->l;
    }
}
void Priority_Queue::show() {
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

