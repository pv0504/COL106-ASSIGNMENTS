#include "stack_a.h"
#include<iostream>
#include <stdexcept>
using namespace std;

Stack_A::Stack_A(){
    size = 0;
}

void Stack_A :: push(int data){
    if(size == 1024){
        throw std::runtime_error("Stack Full");
    }
    size+=1;
    stk[size-1] = data;
}

int Stack_A :: pop(){
    if(size<=0){
        throw std::runtime_error("Empty Stack");
    }
    int result = stk[size-1];
    size-=1;
    return result;
}

int Stack_A ::get_element_from_top(int idx){
    int real = size-1-idx;
        if (real < 0 || real > size-1) {
            throw std::runtime_error("Index out of range");
        }
        return stk[real];
}

int Stack_A ::get_element_from_bottom(int idx){
    if(idx<0 || idx>size-1){
            throw std::runtime_error("Index out of range");
        }
        return stk[idx];

}

void Stack_A ::print_stack(bool top_or_bottom){
    if(size>0){
            if(top_or_bottom==1){
            for(int i=size-1;i>=0;i--){
                cout<<stk[i]<<endl;
            }
        }else{
            for(int i=0;i<=size-1;i++){
                cout<<stk[i]<<endl;
            }
        }
    }else{
        cout<<endl;
    }
}

int Stack_A ::add(){
    if (size<2) {
        throw std::runtime_error("Not Enough Arguments");
    }
    
    int a = stk[size-1];
    size-=1;
    int b = stk[size-1];
    int result = a+b;
    stk[size-1] = a+b;
    return result;
}

int Stack_A ::subtract(){
    if (size < 2) {
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = stk[size-1];
    size-=1;
    int b = stk[size-1];
    int result = b - a;
    stk[size-1] = result;
    return result;
}

int Stack_A ::multiply(){
    if (size < 2) {
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = stk[size-1];
    size-=1;
    int b = stk[size-1];
    int result = a * b;
    stk[size-1] = result;
    return result;
}

int Stack_A :: divide(){
    if (size < 2 ) {
        throw std::runtime_error("Not Enough Arguments");
    }
    if(stk[size-1] == 0){
        throw std::runtime_error("Divide by Zero Error");
    }
    int a = stk[size-1];
    size-=1;
    int b = stk[size-1];
    if(b%a==0){
        stk[size-1] = b/a;
    }else{
        if(b/a>0){
            stk[size-1] = b/a;
        }else{
            stk[size-1] = b/a-1;
        }
    }
    return stk[size-1];
}

int* Stack_A :: get_stack(){
    return stk;
}

int Stack_A :: get_size(){
    return size;
}

