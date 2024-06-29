/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
// #include<iostream>
//Write your code below this line
int calculate(SymNode *node){
    if(node){
        return node->height;
    }else{
        return -1;
    }
}

SymNode::SymNode(){
    key = "";
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* temp = this->right;
    this->right = temp->left;
    if(temp->left != NULL){
        temp->left->par = this;
    }
    temp->par = this->par;
    this->par = temp;
    temp->left = this;
    this->height = max(calculate(this->left),calculate(this->right)) + 1;
    temp->height = max(calculate(temp->left),calculate(temp->right)) + 1;
    return temp;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* temp = this->left;
    this->left = temp->right;
    if(temp->right!=NULL){
        temp->right->par = this;
    }
    temp->par  = this->par;
    this->par = temp;
    temp->right = this;
    this->height = max(calculate(this->left),calculate(this->right)) + 1;
    temp->height = max(calculate(temp->left),calculate(temp->right)) + 1;
    return temp;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode *temp = this->left;
    this->left = temp->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode* SymNode::RightLeftRotation(){
    SymNode *temp = this->right;
    this->right = temp->RightRightRotation();
    return this->LeftLeftRotation();

}

SymNode::~SymNode(){
    //address = -1;
    // if(left){
    //     delete left;
    // }
    // if(right){
    //     delete right;
    // }
}
