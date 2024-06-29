/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    expr_trees = vector<ExprTreeNode*>();
    symtable = new SymbolTable();
    last_deleted = -1;
}
int convert(string s){
    int n = s.length();
    int ans = 0;
    for(int i=0;i<n;i++){
        ans = ans*10 + (s[i]-'0');
    }
    return ans;
}
ExprTreeNode* solve(vector<string>code,SymbolTable *sym){
    vector<ExprTreeNode*>temp;
    int n = code.size();
    for(int i=0;i<n;i++){
        if((code[i][0]>='0' && code[i][0]<='9')){
            ExprTreeNode *tree_node = new ExprTreeNode("VAL", convert(code[i]));
            temp.push_back(tree_node);
        }
        else if(code[i].size()>1 && code[i][0] == '-' && code[i][1]>='0' && code[i][1]<='9'){
            ExprTreeNode *tree_node = new ExprTreeNode("VAL", -1*convert(code[i].substr(1)));
            temp.push_back(tree_node);
        }
        else if(code[i] == "+"){
            ExprTreeNode *value = new ExprTreeNode();
            value->type = "ADD";
            temp.push_back(value);
        }
        else if(code[i]=="-"){
             ExprTreeNode *value = new ExprTreeNode();
            value->type = "SUB";
            temp.push_back(value);
        }
        else if(code[i] == "*"){
             ExprTreeNode *value = new ExprTreeNode();
            value->type = "MUL";
            temp.push_back(value);
        }
        else if(code[i] == "/"){
             ExprTreeNode *value = new ExprTreeNode();
            value->type = "DIV";
            temp.push_back(value);
        }
        else if(code[i] == ")"){
            ExprTreeNode *right_node = temp.back();
            temp.pop_back();
            ExprTreeNode *actual = temp.back();
            temp.pop_back();
            actual->right = right_node;
            ExprTreeNode *left_node = temp.back();
            temp.pop_back();
            actual->left = left_node;
            temp.push_back(actual);
        }else if(code[i].size()==3 and code[i][0]=='d' and code[i][1] == 'e' and code[i][2] == 'l'){
            ExprTreeNode *value = new ExprTreeNode();
            value->type = "DEL";
            temp.push_back(value);
            //now i have to delete the variable from the symtable
        }else if(code[i].size() == 3 and code[i][0]=='r' and code[i][1] == 'e' and code[i][2] == 't'){
            ExprTreeNode *value = new ExprTreeNode();
            value->type = "RET";
            temp.push_back(value);
        }
        else if(code[i]!="("){ 
            ExprTreeNode *tree_node = new ExprTreeNode();
            tree_node -> type = "VAR";
            tree_node -> id = code[i];
            sym->insert(code[i]);
            temp.push_back(tree_node);
        }
        
    }
    return temp.back();
}

void delete_parser(ExprTreeNode *node){
    if (node == NULL)
        return;
    if(node->left){
        delete_parser(node->left);
    }
    if(node->right){
        delete_parser(node->right);
    }
    delete node;
}
void Parser::parse(vector<string>code){
    int i=0;
    vector<string>left_code,right_code;
    int n = code.size();
    while(i<n && code[i]!=":=")
    {
        left_code.push_back(code[i]);
        i++;
    }
    for(int j=i+1;j<n;j++){
        right_code.push_back(code[j]);
    }
    ExprTreeNode *root = new ExprTreeNode();
    root->left = solve(left_code,symtable);
    root->right = solve(right_code,symtable);
    if(root->left->type == "DEL"){
        last_deleted = symtable->search(root->right->id);
        string target = (root->right->id);
        symtable->remove(target);
    }
    expr_trees.push_back(root);
    return;
}


Parser::~Parser(){
    delete symtable;
    symtable = NULL;
    int n = expr_trees.size();
    for(int i=0;i<n;i++){
        delete_parser(expr_trees[i]);
        expr_trees[i] = NULL;
    }
}
