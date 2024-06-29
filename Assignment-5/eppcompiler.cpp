/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//Write your code below this line

EPPCompiler::EPPCompiler(){
    targ.expr_trees = vector<ExprTreeNode*>();
    memory_size = 0;
    output_file = "";
    for(int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    targ.expr_trees = vector<ExprTreeNode*>();
    memory_size = mem_limit;
    output_file = out_file;
    for(int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}
void EPPCompiler::write_to_file(vector<string> commands){
    std::ofstream outfile;
    outfile.open(output_file,ios::app);
    for(const auto& command : commands){
        outfile << command << "\n";
    }
    outfile.close();
}


void EPPCompiler::compile(vector<vector<string>> code){
    int n =code.size();
    ofstream outfile;
    outfile.open(output_file);
    outfile.close();
    for(int i=0;i<n;i++){    
       vector<string>a;
        targ.parse(code[i]);
        string ID = targ.expr_trees.back()->left->id;
        if(targ.expr_trees.back()->left->type == "VAR" && ((targ.symtable->search(ID) == (-1)) || (targ.symtable->search(ID) == (-2)))){
            int min_avail = least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->assign_address(targ.expr_trees.back()->left->id,min_avail);
           // cout<<"Add of :"<<targ.expr_trees.back()->left->id<<" "<<targ.symtable->search(targ.expr_trees.back()->left->id)<<endl;
        }
        if(targ.expr_trees.back()->left->type == "DEL"){//it will be semaintically correct
            //string target = targ.expr_trees.back()->right->id;
            //int del_add = targ.symtable->search(target);//if you delete in symtable
            int del_add = targ.last_deleted;
            least_mem_loc.push_heap(del_add);
           // targ.symtable->remove(target);
        }
        a = generate_targ_commands();
        write_to_file(a);
    }
}
void solve_right(ExprTreeNode *node,vector<string>&res,SymbolTable *sym){

    if(node == NULL){
        return;
    }
    if(node->type == "VAR"){
        res.push_back("PUSH mem[" + std::to_string(sym->search(node->id)) + "]");
    }else if(node->type == "VAL"){
        res.push_back("PUSH "+ std::to_string(node->num));
    }else if(node->type == "ADD"){
        res.push_back("ADD");
    }else if(node->type == "SUB"){
        res.push_back("SUB");
    }else if(node->type == "MUL"){
        res.push_back("MUL");
    }else if(node->type == "DIV"){
        res.push_back("DIV");
    }
    solve_right(node->left,res,sym);
    solve_right(node->right,res,sym);
}
vector<string> EPPCompiler::generate_targ_commands(){
    vector<string>result ={};
    ExprTreeNode *node_left = targ.expr_trees.back()->left;
    ExprTreeNode *node_right = targ.expr_trees.back()->right;
    if(node_left->type == "VAR"){
        result.push_back("mem[" + to_string(targ.symtable->search(node_left->id))+"] = POP");
    }else if(node_left->type == "RET" ){
        result.push_back("RET = POP");
    }
    if(node_left->type == "DEL"){
        result.push_back("DEL = mem[" + to_string(targ.last_deleted) +"]");
    }
    else{
        solve_right(node_right,result,targ.symtable);
    }
    int commands_size = result.size();
    vector<string>final(commands_size);
    for(int i=0;i<commands_size;i++){
        final[i] = result[commands_size-1-i];
    }
    return final;
}

EPPCompiler::~EPPCompiler(){}
