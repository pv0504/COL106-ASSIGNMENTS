#include "stack_c.h"
#include<iostream>
#include <stdexcept>
using namespace std;

Stack_C :: Stack_C(){
    try{
        stk = new List();
    }catch(const bad_alloc &ba){
        cout<< "Out of Memory" <<endl;
        return;
    }
    
}

Stack_C :: ~Stack_C(){
    delete stk;
}

void Stack_C :: push(int data){
    stk->insert(data);
}

int Stack_C :: pop(){
    int k;
    if(stk->get_size()==0){
        throw std::runtime_error("Empty Stack");
    }
    else{
         k = stk->delete_tail();     
    }  
    return k;
}


int Stack_C::get_element_from_top(int idx) {
    int Size = stk->get_size();
    int k = Size-idx -1;

    if (k < 0 || k >= Size) {
        throw std::runtime_error("Index out of range");
    }else
    {
    Node* temp = stk->get_head()->next;
    while (k > 0) {
        temp = temp->next;
        k--;
    }
    return temp->get_value();
    }    
}

int Stack_C::get_element_from_bottom(int idx) {
    int size = stk->get_size();
    if (idx < 0 || idx >= size) {
        throw std::runtime_error("Index out of range");
    }else{
        int k = idx;
        Node* temp = stk->get_head()->next;
        while (k > 0) {  
            temp = temp->next;
            k--;
        }
        return temp->get_value();
    }  
}


void Stack_C::print_stack(bool top_or_bottom) {
    int size = stk->get_size();
    if (size > 0) {
        if (top_or_bottom) { // Print from top
            Node* temp = stk->get_head();
            int k = size,m = size;
            while(m>0){
                temp = temp->next;
                m--;
            }
            while (k > 0) {
                cout << temp->get_value() << endl;
                temp = temp->prev;
                k--;
            }
        } else { // Print from bottom
            Node* temp = stk->get_head()->next;
            int k = size;
            while (k > 0) {
                cout << temp->get_value() << endl;
                temp = temp->next;
                k--;
            }
        }
    }else{
        cout<<endl;
    }
}

int Stack_C :: add(){
    int k = stk->get_size();
    
    if (k<=1) {
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = get_element_from_top(0);
    int b = get_element_from_top(1);
    pop();pop();
    push(a+b);
    return a+b;
}
int Stack_C ::subtract() {
    int k = stk->get_size();
    //Node *temp = stk->get_head()->next;
    if (k<=1) {
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = get_element_from_top(0);
    int b = get_element_from_top(1);
    pop();pop();
    push(b-a);
    return b-a;
}


int Stack_C :: multiply() {
   int k = stk->get_size();
    //Node *temp = stk->get_head()->next;
    if (k<=1) {
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = get_element_from_top(0);
    int b = get_element_from_top(1);
    pop();pop();
    push(a*b);
    return a*b;
}


int Stack_C :: divide() {
    int k = stk->get_size();
    //Node *temp = stk->get_head()->next;

    if (k<=1) {
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = get_element_from_top(0);
    int b = get_element_from_top(1);
    if(a==0){
        throw std::runtime_error("Divide by Zero Error");
    }
    pop();pop();
    if(b%a==0){
        push(b/a);
        return b/a;
    }else{
        if(b/a>0){
            push(b/a);
            return b/a;
        }else{
            push(b/a-1);
            return b/a-1;
        }
    }
    
}


List* Stack_C ::get_stack(){
    return stk;
}


int Stack_C :: get_size(){
    return stk->get_size();
}

