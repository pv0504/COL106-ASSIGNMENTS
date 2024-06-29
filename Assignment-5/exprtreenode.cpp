/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    type = "";
    id = "";
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){  
    type =t;
    num = v;
    left = NULL;
    right = NULL;
    id = "";
}

ExprTreeNode::~ExprTreeNode(){
    
}

