#include "Chaining.h"
using namespace std;

    void merge(vector<int>& arr, int l, int m, int r) {
    int a = m - l + 1;
    int b = r - m;
    vector<int> left(a), right(b);
    for (int i = 0; i < a; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < b; i++) {
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < a && j < b) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < a) {
        arr[k++] = left[i++];
    }
    while (j < b) {
        arr[k++] = right[j++];
    }
}

void mergesort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void Chaining::createAccount(std::string id, int count) {
       
    Account account;
    account.id = id;
    account.balance =count;
    int index = hash(id);
    double temp=0;
    size++;
    temp = (double)size/bucket;
        
    if( temp > load_factor || size==bucket ){
        Rehash();
        index = hash(id);
    }
    bankStorage2d[index].push_back(account); 
}

void Chaining::Rehash(){
    bucket = bucket*2;
    vector<vector<Account>>newbankStorage2d(bucket,emptyRow);
    for(int i = 0;i<bucket/2;i++){
        for(auto &account : bankStorage2d[i]){
            int newindex = hash(account.id);
            newbankStorage2d[newindex].push_back(account);
        }
    }
    bankStorage2d = newbankStorage2d;
}

std::vector<int> Chaining::getTopK(int k) {
    vector<int>temp;
    for(int i =0;i<bucket;i++){
        for(auto &j: bankStorage2d[i]){
            temp.push_back(j.balance);
        }
    }
    int n = temp.size();
    mergesort(temp,0,n-1);
    int m = min(k,n);
    vector<int> Topk(m);
    for (int i = 0; i < k && i < n; i++) {
        Topk[i] = temp[n-1-i];
    }
    return Topk;
}

int Chaining::getBalance(std::string id) {
    int ind = hash(id);
    for(auto i = bankStorage2d[ind].begin();i!=bankStorage2d[ind].end();i++){
        if(i->id == id){
            return i->balance;
        }
    }
    return -1; 
}

void Chaining::addTransaction(std::string id, int count) {
    int ind = hash(id);
    for(auto i = bankStorage2d[ind].begin();i!=bankStorage2d[ind].end();i++){
        if(i->id == id){
             i->balance+=count;
             return;
        }
    }
    createAccount(id,count);
}

bool Chaining::doesExist(std::string id) {
    int ind = hash(id);
    for(auto i = bankStorage2d[ind].begin();i!=bankStorage2d[ind].end();i++){
        if(i->id == id){
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    int ind = hash(id);
    if(doesExist(id)){
        std::vector<Account>New;
            for(auto i = bankStorage2d[ind].begin();i!=bankStorage2d[ind].end();i++){
                if(i->id != id){
                    New.push_back(*i);
                }
            }
        bankStorage2d[ind] = New;
        size--;
        return true;
    }
    return false; // Placeholder return value
}

int Chaining::databaseSize() {
    return size;
}
int Chaining::hash(std::string id) {
    int h = 0;
    for (auto c : id) {
        int val;
        if (c >= '0' && c <= '9') {
            val = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            val = c - 'A' + 10;
        } else if (c == '_') {
            val = 36;
        } else if (c >= 'a' && c <= 'z') {
            val = c - 'a' + 37;
        } else {
            val = c;
        }
        h = ((h * base) % p + val) % p;
    }
    int index = h % bucket;
    if (index < 0) {
        index += bucket;
    }

    return index;
}

