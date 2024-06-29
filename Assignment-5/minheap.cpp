
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
//Write your code below this line
MinHeap::MinHeap(){
    size = 0;
    root = NULL;
}
int bitl(int num) {
    int count = 0;
    while (num != 0) {
        num = num / 2;
        count++;
    }
    return count;
}
void heapify_up(HeapNode* node) {
    while (node->par != NULL && node->val < node->par->val) {
        int temp = node->val;
        node->val = node->par->val;
        node->par->val = temp;
        node = node->par;
    }
}
void heapify_down(HeapNode* node){
    while(node->left != NULL){
        HeapNode *temp = node->left;
        if(node->right!=NULL and node->left->val > node->right->val){
            temp = node->right;
        }
        if(temp->val >= node->val){
            break;
        }
        int x = node->val;
        node->val = temp->val;
        temp->val = x;
        node = temp;
    }
}
HeapNode* find(HeapNode* node,int size) {
    int depth = bitl(size+1);
    HeapNode* parent = node;
    if(depth>=3){
    for (int i = depth - 2; i >= 1; i--) {
        if (((size + 1) >> i) & 1) {
            parent = parent->right;
        } else {
            parent = parent->left;
        }
    }
    }
    return parent;
}

void MinHeap::push_heap(int num){
    HeapNode* node = new HeapNode(num);
    if(root == NULL){
        root = node;
        size++;
        return;
    }
    else{
    HeapNode *parent = find(root,size);
    if(parent->left == NULL){
        parent->left = node;
    }else{
        parent->right = node;
    }
    node->par = parent;
    heapify_up(node);
    }
    size++;
    return;
}
int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    if(root == NULL){
        return;
    }
    HeapNode *Parent = find(root,size-1);//once check this;
    if(size == 1){
        size--;
        delete root;
        root = NULL;
        return;
    }
    HeapNode *x = Parent->right;
    if(x == NULL){
        x = Parent->left;
    }
    if(x->par){
        if(x == x->par->left){
            x->par->left =NULL;
        }else{
            x->par->right = NULL;
        }
    }
    x->par = NULL;
    root->val = x->val;
    delete x;
    x = NULL;
    size--;
    heapify_down(root);
}

void delete_heap(HeapNode *node){
    if(node == NULL){
        return;
    }
    if(node->left){
        delete_heap(node->left);
    }
    if(node->right){
        delete_heap(node->right);
    }
    if(node->par){ 
        if(node->par->right == node){
        node->par->right = NULL;
        }else{
        node->par->left = NULL;
        }
        node->par = NULL;
    }
    delete node;
}
MinHeap::~MinHeap(){
    delete_heap(root);
    root = NULL;
}