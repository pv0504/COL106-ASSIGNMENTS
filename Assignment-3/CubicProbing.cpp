#include "CubicProbing.h"
using namespace std;
void merge3(vector<int>& arr, int l, int m, int r) {
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

void merge3sort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge3sort(arr, l, m);
        merge3sort(arr, m + 1, r);
        merge3(arr, l, m, r);
    }
}
void CubicProbing::createAccount(std::string id, int count) {
     
    int index = hash(id);
    Account account;
    account.id = id;
    account.balance = count;
    int k = 0;
    while(bankStorage1d[index].id!="" && bankStorage1d[index].balance!=-1){
        k++;
        index = (index+k*k*k)%capacity;
    }
    bankStorage1d[index] = account;
    size++;
}
std::vector<int> CubicProbing::getTopK(int k) {
     std::vector<int> balances;
    for (int i = 0; i < capacity; i++) {
        if (bankStorage1d[i].id!="" && bankStorage1d[i].balance!=-1) {
            balances.push_back(bankStorage1d[i].balance);
        }
    }
    int n = balances.size();
    merge3sort(balances,0,n-1);
    int m = min(k,n);
    vector<int> Topk(m);
    for (int i = 0; i < k && i < n; i++) {
        Topk[i] = balances[n-1-i];
    }
    return Topk;   
}

int CubicProbing::getBalance(std::string id) {
    int index = hash(id);
    int ind = index;
    int k = 0;
    while (bankStorage1d[index].id!="") {
        if (bankStorage1d[index].id == id) {
            return bankStorage1d[index].balance;
        }
        k++;
        index = (index + k*k*k) % capacity;
        if(ind == index){
            return -1;
        }
    }
    return -1;
}

void CubicProbing::addTransaction(std::string id, int count) {
    int index = hash(id);
    int k =0;
    while(bankStorage1d[index].id!=""){
        if(bankStorage1d[index].id==id && bankStorage1d[index].balance!=-1){
            bankStorage1d[index].balance+=count;
            return;
        }
        if (bankStorage1d[index].id == id && bankStorage1d[index].balance == -1) {
            bankStorage1d[index].balance = count;
            size++;
            return;
        }
        k++;
        index = (index + k*k*k) % capacity;
    }
    createAccount(id,count);
}

bool CubicProbing::doesExist(std::string id) {
    int k = 0;
    int index = hash(id);
    int ind = index;
    while (bankStorage1d[index].id!="") {
        if (bankStorage1d[index].id == id && bankStorage1d[index].balance!=-1) {
            return true;
        }
        if(bankStorage1d[index].id == id && bankStorage1d[index].balance == -1){
            return false;
        }
        k++;
        index = (index + k*k*k) % capacity;
        if(ind == index){
            return false;
        }
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id) {
    int index = hash(id);
    int ind = index;
    int k =0;
    while(bankStorage1d[index].id!=""){
        if(bankStorage1d[index].id == id && bankStorage1d[index].balance!=-1){
            bankStorage1d[index].balance = -1;
            size--;
            return true;
        }else if(bankStorage1d[index].id==id && bankStorage1d[index].balance==-1){
            return false;
        }
        k++;
        index = (index + k*k*k)%capacity;
        if(ind == index){
            return false;
        }
    }
    return false;
    
}
int CubicProbing::databaseSize() {
    
   return size;
}

int CubicProbing::hash(std::string id) {
    int h = 0;
    for (auto c : id) {
        int val;
        if (c >= '0' && c <= '9') {
            val = c - '0';
        }else if (c >= 'A' && c <= 'Z') {
            val = c - 'A' + 10;
        }else if (c == '_') {
            val = 36;
        }else if (c >= 'a' && c <= 'z') {
            val = c - 'a' + 37;
        }else {
            val = c;
        }
        h = ((h * base) % p + val) % p;
    }
    int index = h % capacity;
    if (index < 0) {
        index += capacity;
    }

    return index;
}
