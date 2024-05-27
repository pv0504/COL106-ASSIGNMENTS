#include "list.h"
#include<iostream>
#include<stdexcept>
using namespace std;
List::List() {
    size = 0;
    try{
        sentinel_head = new Node();
    }catch(const bad_alloc &ba){
        cout<< "Out of Memory" <<endl;
        return;
    }
    try{
        sentinel_tail = new Node();
    }catch(const bad_alloc &ba){
        cout<< "Out of Memory" <<endl;
        return;
    }
    
    
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
}

List:: ~List() {
    while (sentinel_head->next != sentinel_tail) {
            Node* temp = sentinel_head->next;
            sentinel_head->next = temp->next;
            temp->next->prev = sentinel_head;
            delete temp;
        }
        delete sentinel_head;
        delete sentinel_tail;
}

void List::insert(int v) {
    Node* a = sentinel_tail->prev;
    Node* temp;
    try{
    temp = new Node(v,sentinel_tail,sentinel_tail->prev);
        }
    catch(const bad_alloc &ba){
        cout<< "Out of Memory" <<endl;
        return;
    }
    sentinel_tail->prev = temp;
    a->next = temp;
    size+=1;
    return;
}

int List::delete_tail() {
    int value;
    if(sentinel_head->next!=sentinel_tail){
    Node* temp = sentinel_tail->prev;
    sentinel_tail->prev = temp->prev;
    temp->prev->next = sentinel_tail;
     value = temp->get_value();
    delete temp;
    size-=1;
    }
     return value;
    
}

int List::get_size() {
    return size;
}

Node* List::get_head() {
    return sentinel_head;
}

