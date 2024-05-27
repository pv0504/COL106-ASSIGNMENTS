#include "stack_b.h"
#include <iostream>
#include <stdexcept>
using namespace std;

    Stack_B::Stack_B() {
        try{
            stk = new int[1024];
        }
        catch(const bad_alloc & ba){
            cout<< "Out of Memory" <<endl;
        }
        size = 0;
        capacity = 1024;
    }


    Stack_B :: ~Stack_B() {
        delete[] stk;size = 0;capacity = 0;
    }

    void Stack_B ::push(int val) {
        if (size== capacity) {
            capacity*=2;
            int *temp;
        try{
            temp = new int[capacity];
        }
        catch(const bad_alloc & ba){
            cout<< "Out of Memory" <<endl;
        }
        for (int i = 0; i <= size-1; i++) {
            temp[i] = stk[i];
        }
            size+=1;
            delete[] stk;
            stk = temp;
            stk[size-1] = val;          
        }else{
            size+=1;
            stk[size-1] = val;
        }       
    }

    int Stack_B :: pop() {

        if (size <=0) {
            throw std::runtime_error("Empty Stack");
        }else{
            int result = stk[size-1];
            if(size-1 <= capacity/4 && capacity > 1024){//once check into this
                capacity/=2;
                size-=1;
                int* temp;
                try{
                    temp = new int[capacity];
                }
                catch(const bad_alloc & ba){
                    cout<< "Out of Memory" <<endl;
                }
                for(int i=0;i<=size-1;i++){
                    temp[i] = stk[i];
                }
                delete[] stk;
                stk = temp;
                return result;
            }else{
                size-=1;
                return result;    
            }
            
        }
    }

    int Stack_B ::get_element_from_top(int idx) {
        int real = size-1-idx;
        if (real < 0 || real > size-1) {
            throw std::runtime_error("Index out of range");
        }
        return stk[real];
    }

    int Stack_B ::get_element_from_bottom(int idx) {
        if(idx<0 || idx>size-1){
            throw std::runtime_error("Index out of range");
        }
        return stk[idx];
    }

    void Stack_B ::print_stack(bool top_or_bottom){
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
        }else if(size==0){
            cout<<endl;
        }
        
    }


    int Stack_B ::add() {
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

    int Stack_B ::subtract() {
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

int Stack_B :: multiply() {
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

int Stack_B :: divide() {
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

int* Stack_B ::get_stack(){
    return stk;
}

int Stack_B :: get_size(){
    return size;
}


