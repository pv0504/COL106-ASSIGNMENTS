/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
int factor(SymNode* node){
    int l,r;
    if(node->left){
        l = node->left->height;
    }else{
        l = -1;
    }
    if(node->right){
        r = node->right->height;
    }else{
        r = -1;
    }
    return (l-r);
}

SymbolTable::SymbolTable(){
    size = 0;
    root = NULL;
}
// i think i have to consider the case of insertion...

SymNode* avl_insert(SymNode *root,string k,int &ok){
    
    if(root == NULL){
        ok++;
        return new SymNode(k);
    }
    if(root->key < k){
        SymNode *temp = root;
        root->right = avl_insert(root->right,k,ok);
        root->right->par = temp;
    }else if(root->key > k){
        SymNode *temp = root;
        root->left = avl_insert(root->left,k,ok);
        root->left->par = temp;
    }else{
        return root;
    }
    //avl_rotations
    SymNode *x = root;
    while(x!=NULL){
        int l,r;
        if(x->left){
            l = x->left->height;
        }else{
            l = -1;
        }
        if(x->right){
            r = x->right->height;
        }else{
            r = -1;
        }
        int a = x->height;
        int k = max(l,r) + 1;
        if(a!=k){
            x->height = max(l,r) + 1;
            x = x->par;
        }else{
            break;
        }
    }
    if(factor(root) > 1){
        if(factor(root->left)>=0){
            root = root->RightRightRotation();
        }else{
            root = root->LeftRightRotation();
        }
    }else if(factor(root)< -1){
        if(factor(root->right) <= 0){
            root = root->LeftLeftRotation();
        }else{
            root = root->RightLeftRotation();
        }
    }
    return root;
}
// i didnt take care about the address and reassigning the node 
void SymbolTable::insert(string k){
   root = avl_insert(root,k,size);
    return;
}

SymNode *avl_remove(string k,SymNode *root,int &size){
    if(root == NULL){
        return NULL;
    }
    if(root->key < k){
        root->right = avl_remove(k,root->right,size);
    }else if(root->key > k){
        root->left = avl_remove(k,root->left,size);
    }else{
        if(root->left == NULL){
            SymNode* temp = root->right;
            SymNode* pare = root->par;
            delete root;
            size--;
            if(temp==NULL){
                return NULL;
            }else{
                temp->par = pare;
                return temp;
            }
        }else if(root->right == NULL){
            SymNode *temp = root->left;
            SymNode *pare = root->par;
            delete root;
            size--;
            temp->par = pare;
            return temp;
        }else{
            //find the succesor
            SymNode *temp = root->right;
            while(temp->left){
                temp = temp->left;
            }
            root->key = temp->key;
            root->right = avl_remove(temp->key,root->right,size); 
        }
    }
    SymNode *x = root;
    while(x!=NULL){
        int l,r;
        if(x->left){
            l = x->left->height;
        }else{
            l = -1;
        }

        if(x->right){
            r = x->right->height;
        }else{
            r = -1;
        }
        int a = x->height;
        int k = max(l,r) + 1;
        if(a!=k){
            x->height = max(l,r) + 1;
            x = x->par;
        }else{
            break;
        }
    }
    if(factor(root) > 1){
        if(factor(root->left)>=0){
            root = root->RightRightRotation();
        }else{
            root = root->LeftRightRotation();
        }
    }else if(factor(root)< -1){
        if(factor(root->right) <= 0){
            root = root->LeftLeftRotation();
        }else{
            root = root->RightLeftRotation();
        }
    }
    return root;
}

void SymbolTable::remove(string k){
    root = avl_remove(k,root,size);
    return;
}

int SymbolTable::search(string k){
    SymNode *curr = root;
    while(curr!=NULL){
        if(curr -> key > k){
            curr = curr->left;
        }else if(curr->key < k){
            curr = curr->right;
        }else if(curr->key == k){
            return curr->address;
        }
    }
    return -2; //once i have to see this
}

void SymbolTable::assign_address(string k,int idx){
    SymNode *curr = root;
    while(curr!=NULL){
        if(curr -> key > k){
            curr = curr->left;
        }else if(curr->key < k){
            curr = curr->right;
        }else if(curr->key == k){
            curr->address = idx;
            return;
        }
    }
    // bool ok = true;
    // root = avl_insert(root,k,ok);
    // root->address = idx;
    // if(ok){
    //     size++;
    // }
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}
//in destructor class of symtabel  we remove 
void delete_tree(SymNode *node){
    if(node == NULL){
        return;
    }
    if(node->left){
        delete_tree(node->left);
    }
    if(node->right){
        delete_tree(node->right);
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
SymbolTable::~SymbolTable(){
    delete_tree(root);
    root = NULL;
}
